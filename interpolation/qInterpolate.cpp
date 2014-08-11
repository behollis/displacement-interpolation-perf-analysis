#include "timekeeper.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <sstream>

#define _USE_MATH_DEFINES

#include <cstdlib>
#include <cmath>

#define QUANTILE_Q 100
#define DIV 200
#define NUM_PTS 150

#ifdef __cplusplus // import copyrighted mvnun fortran subroutine
extern "C" {
    void mvnun_(int* d, int* n, double** lower, double** upper,
        double*** means, double*** covar, int* maxpts,
        double* abseps, double* releps, double* value, int* inform);
}
#endif

void error(const std::string& message);

struct Vector2 {
    double x, y;
};

//
// kernel density class (ported from scipy)
//

class DensityObject {
    std::vector<Vector2> dataset;
    unsigned n;
    double factor;
    double covariance[4];
    double inv_cov[4];

    Vector2 min, max;

    double norm_factor;

    void computeCovariance() {
        double xMean = 0.0;
        double yMean = 0.0;

        for (unsigned i = 0; i < n; ++i) {
            xMean += dataset[i].x;
            yMean += dataset[i].y;
        }

        xMean /= n;
        yMean /= n;

        covariance[0] = 0.0; covariance[1] = 0.0;
        covariance[2] = 0.0; covariance[3] = 0.0;

        for (unsigned i = 0; i < n; ++i) {
            double xDiff = dataset[i].x - xMean;
            double yDiff = dataset[i].y - yMean;

            covariance[0] += xDiff * xDiff;
            covariance[1] += xDiff * yDiff;
            //covariance[2] += yDiff * xDiff;
            covariance[3] += yDiff * yDiff;
        }

        covariance[0] *= factor * factor / (n-1);
        covariance[1] *= factor * factor / (n-1);
        covariance[2] = covariance[1];
        covariance[3] *= factor * factor / (n-1);
    }

    void computeInverseCov() {
        double determinant = covariance[0] * covariance[3] -
            covariance[1] * covariance[2];

        inv_cov[0] = covariance[3] / determinant;
        inv_cov[1] = -covariance[1] / determinant;
        inv_cov[2] = -covariance[2] / determinant;
        inv_cov[3] = covariance[0] / determinant;
    }

    void computeNormFactor() {
        double determinant = covariance[0] * covariance[3] -
            covariance[1] * covariance[2];

        norm_factor = sqrt(4.0 * M_PI * M_PI * determinant) * n; 
    }

    void findMinAndMax() {
        min.x = dataset[0].x; min.y = dataset[0].y;
        max.x = dataset[0].x; max.y = dataset[0].y;

        for (unsigned i = 1; i < n; ++i) {
            if (dataset[i].x < min.x) min.x = dataset[i].x;
            if (dataset[i].y < min.y) min.y = dataset[i].y;

            if (dataset[i].x > max.x) max.x = dataset[i].x;
            if (dataset[i].y > max.y) max.y = dataset[i].y;
        }
    }

public:
    DensityObject(const std::vector<Vector2>& samples) {
        n = samples.size();
        dataset = samples;
        factor = pow(n, -1.0 / 6.0);

        computeCovariance();
        computeInverseCov();
        computeNormFactor();

        findMinAndMax();
    }
/*
    void evaluate(const std::vector<Vector2>& points, std::vector<double>& results) {
        unsigned m = points.size();

        results.clear();
        results.resize(m, 0);

        if (m >= n) {
            for (unsigned i = 0; i < n; ++i) {
                double diffX, diffY;
                double tdiffX, tdiffY;
                double energy;

                for (unsigned j = 0; j < m; ++j) {
                    diffX = dataset[i].x - points[j].x;
                    diffY = dataset[i].y - points[j].y;

                    tdiffX = inv_cov[0] * diffX + inv_cov[1] * diffY;
                    tdiffY = inv_cov[2] * diffX + inv_cov[3] * diffY;

                    energy = diffX * tdiffX + diffY * tdiffY;
                    results[j] += exp(-energy / 2.0);
                }
            }
        } else {
            for (unsigned i = 0; i < m; ++i) {
                double diffX, diffY;
                double tdiffX, tdiffY;
                double energy;

                for (unsigned j = 0; j < n; ++j) {
                    diffX = dataset[j].x - points[i].x;
                    diffY = dataset[j].y - points[i].y;

                    tdiffX = inv_cov[0] * diffX + inv_cov[1] * diffY;
                    tdiffY = inv_cov[2] * diffX + inv_cov[3] * diffY;

                    energy = diffX * tdiffX + diffY * tdiffY;
                    results[i] += exp(-energy / 2.0);
                }
            }
        }

        for (unsigned i = 0; i < m; ++i) results[i] /= norm_factor;
    }
*/
    double evaluate(const Vector2& point) {
        double result = 0.0;

        double diffX, diffY;
        double tdiffX, tdiffY;
        double energy;

        for (unsigned i = 0; i < n; ++i) {
            diffX = dataset[i].x - point.x;
            diffY = dataset[i].y - point.y;

            tdiffX = inv_cov[0] * diffX + inv_cov[1] * diffY;
            tdiffY = inv_cov[2] * diffX + inv_cov[3] * diffY;

            energy = diffX * tdiffX + diffY * tdiffY;
            result += exp(-energy / 2.0);
        }

        return result / norm_factor;
    }

    double integrate_box(const Vector2& low_bounds, const Vector2& high_bounds) {
        int d = 2;
        int maxpts = d * 1000;
        double abseps = 1e-6;
        double releps = 1e-6;

        double value;
        int inform;

        mvnun_(&d, (int*)&(n), (double**)&low_bounds, (double**)&high_bounds,
            (double***)&dataset[0], (double***)covariance, &maxpts,
            &abseps, &releps, &value, &inform);

        if (inform) std::cerr << "warning: mvnun inform" << std::endl;

        return value;
    }

    unsigned getN() const {
        return n;
    }

    double getFactor() const {
        return factor;
    }

    const double* const getCovariance() const {
        return covariance;
    }

    const double* const getInverseCov() const {
        return inv_cov;
    }

    const Vector2& getMin() const {
        return min;
    }

    const Vector2& getMax() const {
        return max;
    }
};

//
// curve interpolation class (linear)
//

class CurveObject {
    std::vector<Vector2> positions;
    std::vector<double> distances;
    double totalDistance;

public:
    CurveObject() {
        totalDistance = 0;
    }

    void addPoint(const Vector2& position) {
        positions.push_back(position);

        if (positions.size() > 1) {
            Vector2 toRecentPoint;
            toRecentPoint.x = positions[positions.size() - 1].x -
                positions[positions.size() - 2].x;
            toRecentPoint.y = positions[positions.size() - 1].y -
                positions[positions.size() - 2].y;

            double recentDistance = sqrt(toRecentPoint.x * toRecentPoint.x +
                toRecentPoint.y * toRecentPoint.y);

            distances.push_back(recentDistance);
            totalDistance += recentDistance;
        }
    }

    void getPoints(unsigned pointCount, std::vector<Vector2>& points) {
        unsigned current = 0;
        double differentialDistance = totalDistance / pointCount;
        double currentDistance = 0;
        double pointDistances = 0;

        points.clear();
        if (positions.size() < 2) {
            std::cout << "unable to form a quantile curve" << std::endl;
            return;
        }

        points.resize(pointCount);

        for (unsigned i = 0; i < pointCount; ++i) {
            Vector2& currentPosition = positions[current];
            Vector2& nextPosition = positions[current + 1];

            double alpha = (currentDistance - pointDistances) / distances[current];
            points[i].x = currentPosition.x + alpha *
                (nextPosition.x - currentPosition.x);
            points[i].y = currentPosition.y + alpha *
                (nextPosition.y - currentPosition.y);

            currentDistance += differentialDistance;
            while (currentDistance - pointDistances > distances[current]) {
                pointDistances += distances[current];
                current += 1;
                if (current > positions.size() - 2) current = positions.size() - 2;
            }
        }
    }

    void clear() {
        positions.clear();
        distances.clear();
        totalDistance = 0;
    }
};

//
// misc functions
//

void error(const std::string& message) {
    std::cerr << "Error: " << message << std::endl;
    exit(1);
}

void split(const std::string& line, char delim,
        std::vector<std::string>& elems) {

    std::stringstream lineStream(line);
    std::string token;

    elems.clear();

    while (std::getline(lineStream, token, delim)) {
        if (token.length() > 0) elems.push_back(token);
    }    
}

void readSamplesFile(const std::string& filePath,
        std::vector<Vector2>& samplesVector) {

    std::ifstream samplesFile(filePath.c_str());
    if (!samplesFile.is_open()) error("Unable to open vector sample file");

    samplesVector.clear();
    std::string line;
    std::vector<std::string> tokens;

    while (std::getline(samplesFile, line)) {
        split(line, ' ', tokens);

        Vector2 v;
        v.x = atof(tokens[0].c_str());
        v.y = atof(tokens[1].c_str());

        samplesVector.push_back(v);
    }

    samplesFile.close();
}

void generateQuantiles(unsigned q, std::vector<double>& quantiles) {
    if (q < 2) {
        std::cerr << "quantile count too low" << std::endl;
        return;
    }

    quantiles.clear();
    quantiles.resize(q-1); // from Wikipedia: q-1 of the q-quantiles

    for (unsigned i = 1; i < q; ++i) {
        quantiles[i-1] = (double)i / q;
    }
}

void saveQuantileCurvesFile(const std::string& filename,
        std::vector<std::vector<Vector2> >& quantileCurves) {

    std::ofstream curvesFile(filename.c_str());
    for (unsigned i = 0; i < quantileCurves.size(); ++i) {
        for (unsigned j = 0; j < quantileCurves[i].size(); ++j) {
            if (j != 0) curvesFile << " ";
            curvesFile << quantileCurves[i][j].x << " " << quantileCurves[i][j].y;
        }
        if (i != quantileCurves.size() - 1) curvesFile << std::endl;
    }
    curvesFile.close();
}

void savePDFFile(const std::string& filename,
        const std::vector<std::vector<Vector2> >& qcurves,
        const std::vector<std::vector<double> >& ipdf, unsigned step) {

    std::ostringstream s;
    s << filename << step;

    std::ofstream outputFile(s.str().c_str());
    if (!outputFile.is_open()) error("unable to write output file");
 
    for (unsigned i = 0; i < qcurves.size(); ++i) {
        for (unsigned j = 0; j < qcurves[i].size(); ++j) {
            const Vector2& v = qcurves[i][j];
            double w = ipdf[i][j];
            outputFile << v.x << " " << v.y << " " << w;
            if (i != qcurves.size() - 1 || j != qcurves[i].size() - 1)
                outputFile << std::endl;
        }
    }
    outputFile.close();
}

//
// algorithms from paper
//

void calculateCDF(DensityObject& dobj,
        const std::vector<double>& quantiles,
        std::vector<std::list<Vector2> >& quantilePoints) {

    const double TOL = 0.5 / QUANTILE_Q;
    const double differentialU = (dobj.getMax().x - dobj.getMin().x) / (DIV - 1);
    const double differentialV = (dobj.getMax().y - dobj.getMin().y) / (DIV - 1);

    for (unsigned i = 0; i < DIV; ++i) {
        for (unsigned j = 0; j < DIV; ++j) {
            Vector2 uv_coord;
            uv_coord.x = dobj.getMin().x + i * differentialU;
            uv_coord.y = dobj.getMin().y + j * differentialV;

            double d = dobj.integrate_box(dobj.getMin(), uv_coord);

            for (unsigned k = 0; k < quantiles.size(); ++k) {
                double q = quantiles[k];

                if ((q - TOL < d) && (q + TOL > d)) {
                    quantilePoints[k].push_back(uv_coord);
                }
            }
        }
    }
}

void parameterizeQuantiles(const std::vector<std::list<Vector2> >& qpts,
        const std::vector<double>& quantiles,
        std::vector<std::vector<Vector2> >& qcurves) {

    qcurves.clear();
    qcurves.resize(quantiles.size());

    for (unsigned k = 0; k < quantiles.size(); ++k) {
        CurveObject cobj;
        qcurves[k] = std::vector<Vector2>();

        std::list<Vector2>::const_iterator iter;
        for (iter = qpts[k].begin(); iter != qpts[k].end(); ++iter) {
            const Vector2& v = *iter;

            cobj.addPoint(v);
        }

        cobj.getPoints(NUM_PTS, qcurves[k]);
        cobj.clear();
    }
}

void interpolateQuantiles(const std::vector<std::vector<Vector2> >& qcurvesA,
        const std::vector<std::vector<Vector2> >& qcurvesB, double alpha,
        std::vector<std::vector<Vector2> >& qcurvesOut) {

    qcurvesOut.clear();
    qcurvesOut.resize(qcurvesA.size());

    for (unsigned k = 0; k < qcurvesA.size(); ++k) {
        qcurvesOut[k] = std::vector<Vector2>();

        if (qcurvesA[k].size() == 0 || qcurvesB[k].size() == 0) continue;

        qcurvesOut[k].resize(qcurvesA[k].size());

        for (unsigned i = 0; i < qcurvesA[k].size(); ++i) {
            qcurvesOut[k][i].x = qcurvesA[k][i].x;
            qcurvesOut[k][i].y = qcurvesA[k][i].y;

            qcurvesOut[k][i].x += alpha * (qcurvesB[k][i].x - qcurvesA[k][i].x);
            qcurvesOut[k][i].y += alpha * (qcurvesB[k][i].y - qcurvesA[k][i].y);
        }
    }
}

void evaluatePDFValues(DensityObject& dobjA,
        const std::vector<std::vector<Vector2> >& qcurvesA,
        DensityObject& dobjB,
        const std::vector<std::vector<Vector2> >& qcurvesB,
        double alpha, std::vector<std::vector<double> >& ipdf) {

    ipdf.clear();
    ipdf.resize(qcurvesA.size());

    for (unsigned k = 0; k < qcurvesA.size(); ++k) {
        ipdf[k] = std::vector<double>();
        if (qcurvesA[k].size() == 0 || qcurvesB[k].size() == 0) continue;

        ipdf[k].resize(qcurvesA[k].size());

        for (unsigned i = 0; i < qcurvesA[k].size(); ++i) {
            const Vector2& vectorA = qcurvesA[k][i];
            const Vector2& vectorB = qcurvesB[k][i];

            double valueA = dobjA.evaluate(vectorA);
            double valueB = dobjB.evaluate(vectorB);

            ipdf[k][i] = valueA * valueB;
            ipdf[k][i] /= (1.0 - alpha) * valueB + alpha * valueA;
        }
    }
}

int main(int argc, char** argv) {
    timekeeper myTimer;

    if (argc < 3) error("please provide vector sample files");

    std::string outputFile = "interpolatedPDF";
    if (argc > 3) outputFile = argv[3];

    //
    // distribution A
    //

    std::vector<Vector2> vectorSamplesA;
    //PythonDensityObject kernelDensityA;
    std::vector<double> quantilesA;
    std::vector<std::list<Vector2> > quantilePointsA;
    std::vector<std::vector<Vector2> > quantileCurvesA;

    readSamplesFile(argv[1], vectorSamplesA);
    generateQuantiles(QUANTILE_Q, quantilesA);

    if (vectorSamplesA.size() == 0) error("no vector samples found");

    quantilePointsA.resize(quantilesA.size());
    for (unsigned i = 0; i < quantilePointsA.size(); ++i)
        quantilePointsA[i] = std::list<Vector2>();

    //setObjectData(kernelDensityA, vectorSamplesA);
    DensityObject kernelDensityA(vectorSamplesA);

    std::cout << "calculating CDF of distribution A..." << std::endl;
    myTimer.start();
    calculateCDF(kernelDensityA, quantilesA, quantilePointsA);
    myTimer.stop();
    std::cout << " -time: " << myTimer.getElapsedRealMS() << std::endl;
    std::cout << " -CPU clock: " << myTimer.getElapsedClockMS() << std::endl;
    myTimer.clear();

    std::cout << "parameterizing quantiles of distribution A..." << std::endl;
    myTimer.start();
    parameterizeQuantiles(quantilePointsA, quantilesA, quantileCurvesA);
    myTimer.stop();
    std::cout << " -time: " << myTimer.getElapsedRealMS() << std::endl;
    std::cout << " -CPU clock: " << myTimer.getElapsedClockMS() << std::endl;
    myTimer.clear();

    saveQuantileCurvesFile("curvesA", quantileCurvesA);

    //
    // distribution B
    //

    std::vector<Vector2> vectorSamplesB;
    //PythonDensityObject kernelDensityB;
    std::vector<double> quantilesB;
    std::vector<std::list<Vector2> > quantilePointsB;
    std::vector<std::vector<Vector2> > quantileCurvesB;

    readSamplesFile(argv[2], vectorSamplesB);
    generateQuantiles(QUANTILE_Q, quantilesB);

    if (vectorSamplesB.size() == 0) error("no vector samples found");

    quantilePointsB.resize(quantilesB.size());
    for (unsigned i = 0; i < quantilePointsB.size(); ++i)
        quantilePointsB[i] = std::list<Vector2>();

    //setObjectData(kernelDensityB, vectorSamplesB);
    DensityObject kernelDensityB(vectorSamplesB);

    std::cout << "calculating CDF of distribution B..." << std::endl;
    myTimer.start();
    calculateCDF(kernelDensityB, quantilesB, quantilePointsB);
    myTimer.stop();
    std::cout << " -time: " << myTimer.getElapsedRealMS() << std::endl;
    std::cout << " -CPU clock: " << myTimer.getElapsedClockMS() << std::endl;
    myTimer.clear();

    std::cout << "parameterizing quantiles of distribution B..." << std::endl;
    myTimer.start();
    parameterizeQuantiles(quantilePointsB, quantilesB, quantileCurvesB);
    myTimer.stop();
    std::cout << " -time: " << myTimer.getElapsedRealMS() << std::endl;
    std::cout << " -CPU clock: " << myTimer.getElapsedClockMS() << std::endl;
    myTimer.clear();

    saveQuantileCurvesFile("curvesB", quantileCurvesB);

    //
    // interpolated distribution (currently just from two distributions)
    //

    unsigned alphaSteps = 6;
    std::vector<std::vector<Vector2> > quantileCurvesOut;
    std::vector<std::vector<double> > interpolatedPDFValues;

    for (unsigned i = 0; i < alphaSteps; ++i) {
        double alpha = (double)i / (alphaSteps - 1);
        std::cout << "--- alpha = " << alpha << " ---" << std::endl;

        std::cout << "interpolating quantiles of both distributions..." << std::endl;
        myTimer.start();
        interpolateQuantiles(quantileCurvesA, quantileCurvesB, alpha, quantileCurvesOut);
        myTimer.stop();
        std::cout << " -time: " << myTimer.getElapsedRealMS() << std::endl;
        std::cout << " -CPU clock: " << myTimer.getElapsedClockMS() << std::endl;
        myTimer.clear();

        //saveQuantileCurvesFile("curvesOut", quantileCurvesOut);

        std::cout << "evaluating interpolant PDF values..." << std::endl;
        myTimer.start();
        evaluatePDFValues(kernelDensityA, quantileCurvesA, kernelDensityB,
            quantileCurvesB, alpha, interpolatedPDFValues);
        myTimer.stop();
        std::cout << " -time: " << myTimer.getElapsedRealMS() << std::endl;
        std::cout << " -CPU clock: " << myTimer.getElapsedClockMS() << std::endl;
        myTimer.clear();

        savePDFFile(outputFile, quantileCurvesOut, interpolatedPDFValues, i);
    }

    std::cout << "done." << std::endl;
    return 0;
}


#include "timekeeper.h"
#include "DensityObject.h"

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

void error(const std::string& message);

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
        const std::vector<std::vector<Vector2> >& qcurvesB,
        const std::vector<std::vector<Vector2> >& qcurvesC,
        const std::vector<std::vector<Vector2> >& qcurvesD,
        double alpha, double beta,
        std::vector<std::vector<Vector2> >& qcurvesOut) {

    qcurvesOut.clear();
    qcurvesOut.resize(qcurvesA.size());

    for (unsigned k = 0; k < qcurvesA.size(); ++k) {
        qcurvesOut[k] = std::vector<Vector2>();

        if (qcurvesA[k].size() == 0) continue;
        if (qcurvesB[k].size() == 0) continue;
        if (qcurvesC[k].size() == 0) continue;
        if (qcurvesD[k].size() == 0) continue;

        qcurvesOut[k].resize(qcurvesA[k].size());

        for (unsigned i = 0; i < qcurvesA[k].size(); ++i) {
            const Vector2& A = qcurvesA[k][i];
            const Vector2& B = qcurvesB[k][i];
            const Vector2& C = qcurvesC[k][i];
            const Vector2& D = qcurvesD[k][i];

            Vector2 AB;
            AB.x = A.x + alpha * (B.x - A.x);
            AB.y = A.y + alpha * (B.y - A.y);

            Vector2 CD;
            CD.x = C.x + alpha * (D.x - C.x);
            CD.y = C.y + alpha * (D.y - C.y);

            qcurvesOut[k][i].x = AB.x + beta * (CD.x - AB.x);
            qcurvesOut[k][i].y = AB.y + beta * (CD.y - AB.y);
        }
    }
}

void evaluatePDFValues(DensityObject& dobjA,
        const std::vector<std::vector<Vector2> >& qcurvesA,
        DensityObject& dobjB,
        const std::vector<std::vector<Vector2> >& qcurvesB,
        DensityObject& dobjC,
        const std::vector<std::vector<Vector2> >& qcurvesC,
        DensityObject& dobjD,
        const std::vector<std::vector<Vector2> >& qcurvesD,
        double alpha, double beta,
        std::vector<std::vector<double> >& ipdf) {

    ipdf.clear();
    ipdf.resize(qcurvesA.size());

    for (unsigned k = 0; k < qcurvesA.size(); ++k) {
        ipdf[k] = std::vector<double>();

        if (qcurvesA[k].size() == 0) continue;
        if (qcurvesB[k].size() == 0) continue;
        if (qcurvesC[k].size() == 0) continue;
        if (qcurvesD[k].size() == 0) continue;

        ipdf[k].resize(qcurvesA[k].size());

        for (unsigned i = 0; i < qcurvesA[k].size(); ++i) {
            const Vector2& vectorA = qcurvesA[k][i];
            const Vector2& vectorB = qcurvesB[k][i];
            const Vector2& vectorC = qcurvesC[k][i];
            const Vector2& vectorD = qcurvesD[k][i];

            double f0 = dobjA.evaluate(vectorA);
            double f1 = dobjB.evaluate(vectorB);
            double f2 = dobjC.evaluate(vectorC);
            double f3 = dobjD.evaluate(vectorD);

            double A = f0 * f2 * f3 - f1 * f2 * f3;
            double B = f0 * f1 * f3 - f1 * f2 * f3;
            double C = f1 * f2 * f3 - f0 * f2 * f3;
            C = C - f0 * f1 * f3 + f0 * f1 * f2;

            double denominator = f1 * f2 * f3 + alpha * A + beta * B;
            denominator += alpha * beta * C;

            ipdf[k][i] = f0 * f1 * f2 * f3;
            ipdf[k][i] /= denominator;
        }
    }
}

int main(int argc, char** argv) {
    timekeeper myTimer;

    if (argc < 5) error("please provide vector sample files");

    std::string outputFile = "interpolatedPDF";
    if (argc > 5) outputFile = argv[5];

    //
    // distribution A
    //

    std::vector<Vector2> vectorSamplesA;
    std::vector<double> quantilesA;
    std::vector<std::list<Vector2> > quantilePointsA;
    std::vector<std::vector<Vector2> > quantileCurvesA;

    readSamplesFile(argv[1], vectorSamplesA);
    generateQuantiles(QUANTILE_Q, quantilesA);

    if (vectorSamplesA.size() == 0) error("no vector samples found");

    quantilePointsA.resize(quantilesA.size());
    for (unsigned i = 0; i < quantilePointsA.size(); ++i)
        quantilePointsA[i] = std::list<Vector2>();

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
    std::vector<double> quantilesB;
    std::vector<std::list<Vector2> > quantilePointsB;
    std::vector<std::vector<Vector2> > quantileCurvesB;

    readSamplesFile(argv[2], vectorSamplesB);
    generateQuantiles(QUANTILE_Q, quantilesB);

    if (vectorSamplesB.size() == 0) error("no vector samples found");

    quantilePointsB.resize(quantilesB.size());
    for (unsigned i = 0; i < quantilePointsB.size(); ++i)
        quantilePointsB[i] = std::list<Vector2>();

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
    // distribution C
    //

    std::vector<Vector2> vectorSamplesC;
    std::vector<double> quantilesC;
    std::vector<std::list<Vector2> > quantilePointsC;
    std::vector<std::vector<Vector2> > quantileCurvesC;

    readSamplesFile(argv[3], vectorSamplesC);
    generateQuantiles(QUANTILE_Q, quantilesC);

    if (vectorSamplesC.size() == 0) error("no vector samples found");

    quantilePointsC.resize(quantilesC.size());
    for (unsigned i = 0; i < quantilePointsC.size(); ++i)
        quantilePointsC[i] = std::list<Vector2>();

    DensityObject kernelDensityC(vectorSamplesC);

    std::cout << "calculating CDF of distribution C..." << std::endl;
    myTimer.start();
    calculateCDF(kernelDensityC, quantilesC, quantilePointsC);
    myTimer.stop();
    std::cout << " -time: " << myTimer.getElapsedRealMS() << std::endl;
    std::cout << " -CPU clock: " << myTimer.getElapsedClockMS() << std::endl;
    myTimer.clear();

    std::cout << "parameterizing quantiles of distribution C..." << std::endl;
    myTimer.start();
    parameterizeQuantiles(quantilePointsC, quantilesC, quantileCurvesC);
    myTimer.stop();
    std::cout << " -time: " << myTimer.getElapsedRealMS() << std::endl;
    std::cout << " -CPU clock: " << myTimer.getElapsedClockMS() << std::endl;
    myTimer.clear();

    saveQuantileCurvesFile("curvesC", quantileCurvesC);

    //
    // distribution D
    //

    std::vector<Vector2> vectorSamplesD;
    std::vector<double> quantilesD;
    std::vector<std::list<Vector2> > quantilePointsD;
    std::vector<std::vector<Vector2> > quantileCurvesD;

    readSamplesFile(argv[4], vectorSamplesD);
    generateQuantiles(QUANTILE_Q, quantilesD);

    if (vectorSamplesD.size() == 0) error("no vector samples found");

    quantilePointsD.resize(quantilesD.size());
    for (unsigned i = 0; i < quantilePointsD.size(); ++i)
        quantilePointsD[i] = std::list<Vector2>();

    DensityObject kernelDensityD(vectorSamplesD);

    std::cout << "calculating CDF of distribution D..." << std::endl;
    myTimer.start();
    calculateCDF(kernelDensityD, quantilesD, quantilePointsD);
    myTimer.stop();
    std::cout << " -time: " << myTimer.getElapsedRealMS() << std::endl;
    std::cout << " -CPU clock: " << myTimer.getElapsedClockMS() << std::endl;
    myTimer.clear();

    std::cout << "parameterizing quantiles of distribution D..." << std::endl;
    myTimer.start();
    parameterizeQuantiles(quantilePointsD, quantilesD, quantileCurvesD);
    myTimer.stop();
    std::cout << " -time: " << myTimer.getElapsedRealMS() << std::endl;
    std::cout << " -CPU clock: " << myTimer.getElapsedClockMS() << std::endl;
    myTimer.clear();

    saveQuantileCurvesFile("curvesD", quantileCurvesD);

    //
    // interpolated distributions
    //

    unsigned edgeSteps = 10;
    unsigned totalInterpolationRealTime, totalInterpolationClockTime;
    unsigned totalEvaluationRealTime, totalEvaluationClockTime;
    double alpha, beta;
    std::vector<std::vector<Vector2> > quantileCurvesOut;
    std::vector<std::vector<double> > interpolatedPDFValues;

    // edge AB interpolation

    beta = 0.0;
    totalInterpolationRealTime = totalInterpolationClockTime = 0;
    totalEvaluationRealTime = totalEvaluationClockTime = 0;
    std::cout << "--- Edge AB ---" << std::endl;
    for (unsigned i = 0; i < edgeSteps; ++i) {
        alpha = (double)i / (edgeSteps - 1);

        std::cout << "--- alpha = " << alpha << ", beta = ";
        std::cout << beta << " ---" << std::endl;

        std::cout << "interpolating quantiles of distributions..." << std::endl;
        myTimer.start();
        interpolateQuantiles(quantileCurvesA, quantileCurvesB,
            quantileCurvesC, quantileCurvesD, alpha, beta,
            quantileCurvesOut);
        myTimer.stop();
        std::cout << " -time: " << myTimer.getElapsedRealMS() << std::endl;
        totalInterpolationRealTime += myTimer.getElapsedRealMS();
        std::cout << " -CPU clock: " << myTimer.getElapsedClockMS() << std::endl;
        totalInterpolationClockTime += myTimer.getElapsedClockMS();
        myTimer.clear();

        std::cout << "evaluating interpolant PDF values..." << std::endl;
        myTimer.start();
        evaluatePDFValues(kernelDensityA, quantileCurvesA, kernelDensityB,
            quantileCurvesB, kernelDensityC, quantileCurvesC,
            kernelDensityD, quantileCurvesD, alpha, beta,
            interpolatedPDFValues);
        myTimer.stop();
        std::cout << " -time: " << myTimer.getElapsedRealMS() << std::endl;
        totalEvaluationRealTime += myTimer.getElapsedRealMS();
        std::cout << " -CPU clock: " << myTimer.getElapsedClockMS() << std::endl;
        totalEvaluationClockTime += myTimer.getElapsedClockMS();
        myTimer.clear();

        savePDFFile(outputFile, quantileCurvesOut, interpolatedPDFValues, i + 0 * edgeSteps);
    }
    std::cout << "--- total times ---" << std::endl;
    std::cout << "total interpolation in real ms: " << totalInterpolationRealTime << std::endl;
    std::cout << "total interpolation in clock ms: " << totalInterpolationClockTime << std::endl;
    std::cout << "total evaluation in real ms: " << totalEvaluationRealTime << std::endl;
    std::cout << "total evaluation in clock ms: " << totalEvaluationClockTime << std::endl;

    // edge CD interpolation

    beta = 1.0;
    totalInterpolationRealTime = totalInterpolationClockTime = 0;
    totalEvaluationRealTime = totalEvaluationClockTime = 0;
    std::cout << "--- Edge CD ---" << std::endl;
    for (unsigned i = 0; i < edgeSteps; ++i) {
        alpha = (double)i / (edgeSteps - 1);

        std::cout << "--- alpha = " << alpha << ", beta = ";
        std::cout << beta << " ---" << std::endl;

        std::cout << "interpolating quantiles of distributions..." << std::endl;
        myTimer.start();
        interpolateQuantiles(quantileCurvesA, quantileCurvesB,
            quantileCurvesC, quantileCurvesD, alpha, beta,
            quantileCurvesOut);
        myTimer.stop();
        std::cout << " -time: " << myTimer.getElapsedRealMS() << std::endl;
        totalInterpolationRealTime += myTimer.getElapsedRealMS();
        std::cout << " -CPU clock: " << myTimer.getElapsedClockMS() << std::endl;
        totalInterpolationClockTime += myTimer.getElapsedClockMS();
        myTimer.clear();

        std::cout << "evaluating interpolant PDF values..." << std::endl;
        myTimer.start();
        evaluatePDFValues(kernelDensityA, quantileCurvesA, kernelDensityB,
            quantileCurvesB, kernelDensityC, quantileCurvesC,
            kernelDensityD, quantileCurvesD, alpha, beta,
            interpolatedPDFValues);
        myTimer.stop();
        std::cout << " -time: " << myTimer.getElapsedRealMS() << std::endl;
        totalEvaluationRealTime += myTimer.getElapsedRealMS();
        std::cout << " -CPU clock: " << myTimer.getElapsedClockMS() << std::endl;
        totalEvaluationClockTime += myTimer.getElapsedClockMS();
        myTimer.clear();

        savePDFFile(outputFile, quantileCurvesOut, interpolatedPDFValues, i + 1 * edgeSteps);
    }
    std::cout << "--- total times ---" << std::endl;
    std::cout << "total interpolation in real ms: " << totalInterpolationRealTime << std::endl;
    std::cout << "total interpolation in clock ms: " << totalInterpolationClockTime << std::endl;
    std::cout << "total evaluation in real ms: " << totalEvaluationRealTime << std::endl;
    std::cout << "total evaluation in clock ms: " << totalEvaluationClockTime << std::endl;

    // edge AC interpolation

    alpha = 0.0;
    totalInterpolationRealTime = totalInterpolationClockTime = 0;
    totalEvaluationRealTime = totalEvaluationClockTime = 0;
    std::cout << "--- Edge AC ---" << std::endl;
    for (unsigned i = 0; i < edgeSteps; ++i) {
        beta = (double)i / (edgeSteps - 1);

        std::cout << "--- alpha = " << alpha << ", beta = ";
        std::cout << beta << " ---" << std::endl;

        std::cout << "interpolating quantiles of distributions..." << std::endl;
        myTimer.start();
        interpolateQuantiles(quantileCurvesA, quantileCurvesB,
            quantileCurvesC, quantileCurvesD, alpha, beta,
            quantileCurvesOut);
        myTimer.stop();
        std::cout << " -time: " << myTimer.getElapsedRealMS() << std::endl;
        totalInterpolationRealTime += myTimer.getElapsedRealMS();
        std::cout << " -CPU clock: " << myTimer.getElapsedClockMS() << std::endl;
        totalInterpolationClockTime += myTimer.getElapsedClockMS();
        myTimer.clear();

        std::cout << "evaluating interpolant PDF values..." << std::endl;
        myTimer.start();
        evaluatePDFValues(kernelDensityA, quantileCurvesA, kernelDensityB,
            quantileCurvesB, kernelDensityC, quantileCurvesC,
            kernelDensityD, quantileCurvesD, alpha, beta,
            interpolatedPDFValues);
        myTimer.stop();
        std::cout << " -time: " << myTimer.getElapsedRealMS() << std::endl;
        totalEvaluationRealTime += myTimer.getElapsedRealMS();
        std::cout << " -CPU clock: " << myTimer.getElapsedClockMS() << std::endl;
        totalEvaluationClockTime += myTimer.getElapsedClockMS();
        myTimer.clear();

        savePDFFile(outputFile, quantileCurvesOut, interpolatedPDFValues, i + 2 * edgeSteps);
    }
    std::cout << "--- total times ---" << std::endl;
    std::cout << "total interpolation in real ms: " << totalInterpolationRealTime << std::endl;
    std::cout << "total interpolation in clock ms: " << totalInterpolationClockTime << std::endl;
    std::cout << "total evaluation in real ms: " << totalEvaluationRealTime << std::endl;
    std::cout << "total evaluation in clock ms: " << totalEvaluationClockTime << std::endl;

    // edge BD interpolation

    alpha = 1.0;
    totalInterpolationRealTime = totalInterpolationClockTime = 0;
    totalEvaluationRealTime = totalEvaluationClockTime = 0;
    std::cout << "--- Edge BD ---" << std::endl;
    for (unsigned i = 0; i < edgeSteps; ++i) {
        beta = (double)i / (edgeSteps - 1);

        std::cout << "--- alpha = " << alpha << ", beta = ";
        std::cout << beta << " ---" << std::endl;

        std::cout << "interpolating quantiles of distributions..." << std::endl;
        myTimer.start();
        interpolateQuantiles(quantileCurvesA, quantileCurvesB,
            quantileCurvesC, quantileCurvesD, alpha, beta,
            quantileCurvesOut);
        myTimer.stop();
        std::cout << " -time: " << myTimer.getElapsedRealMS() << std::endl;
        totalInterpolationRealTime += myTimer.getElapsedRealMS();
        std::cout << " -CPU clock: " << myTimer.getElapsedClockMS() << std::endl;
        totalInterpolationClockTime += myTimer.getElapsedClockMS();
        myTimer.clear();

        std::cout << "evaluating interpolant PDF values..." << std::endl;
        myTimer.start();
        evaluatePDFValues(kernelDensityA, quantileCurvesA, kernelDensityB,
            quantileCurvesB, kernelDensityC, quantileCurvesC,
            kernelDensityD, quantileCurvesD, alpha, beta,
            interpolatedPDFValues);
        myTimer.stop();
        std::cout << " -time: " << myTimer.getElapsedRealMS() << std::endl;
        totalEvaluationRealTime += myTimer.getElapsedRealMS();
        std::cout << " -CPU clock: " << myTimer.getElapsedClockMS() << std::endl;
        totalEvaluationClockTime += myTimer.getElapsedClockMS();
        myTimer.clear();

        savePDFFile(outputFile, quantileCurvesOut, interpolatedPDFValues, i + 3 * edgeSteps);
    }
    std::cout << "--- total times ---" << std::endl;
    std::cout << "total interpolation in real ms: " << totalInterpolationRealTime << std::endl;
    std::cout << "total interpolation in clock ms: " << totalInterpolationClockTime << std::endl;
    std::cout << "total evaluation in real ms: " << totalEvaluationRealTime << std::endl;
    std::cout << "total evaluation in clock ms: " << totalEvaluationClockTime << std::endl;

    // grid cell center interpolation

    alpha = 0.5;
    beta = 0.5;

    std::cout << "--- grid cell center ---" << std::endl;
    std::cout << "--- alpha = " << alpha << ", beta = ";
    std::cout << beta << " ---" << std::endl;

    std::cout << "interpolating quantiles of distributions..." << std::endl;
    myTimer.start();
    interpolateQuantiles(quantileCurvesA, quantileCurvesB,
        quantileCurvesC, quantileCurvesD, alpha, beta,
        quantileCurvesOut);
    myTimer.stop();
    std::cout << " -time: " << myTimer.getElapsedRealMS() << std::endl;
    std::cout << " -CPU clock: " << myTimer.getElapsedClockMS() << std::endl;
    myTimer.clear();

    std::cout << "evaluating interpolant PDF values..." << std::endl;
    myTimer.start();
    evaluatePDFValues(kernelDensityA, quantileCurvesA, kernelDensityB,
        quantileCurvesB, kernelDensityC, quantileCurvesC,
        kernelDensityD, quantileCurvesD, alpha, beta,
        interpolatedPDFValues);
    myTimer.stop();
    std::cout << " -time: " << myTimer.getElapsedRealMS() << std::endl;
    std::cout << " -CPU clock: " << myTimer.getElapsedClockMS() << std::endl;
    myTimer.clear();

    savePDFFile(outputFile, quantileCurvesOut, interpolatedPDFValues, 0 + 4 * edgeSteps);

    std::cout << "done." << std::endl;
    return 0;
}

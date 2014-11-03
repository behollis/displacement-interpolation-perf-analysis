#ifndef _DENSITYOBJECT_H
#define _DENSITYOBJECT_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdlib>

#include "Vector2.h"
#include "error.h"

#ifdef __cplusplus // import copyrighted mvnun fortran subroutine
extern "C" {
    void mvnun_(int* d, int* n, double** lower, double** upper,
        double*** means, double*** covar, int* maxpts,
        double* abseps, double* releps, double* value, int* inform);
}
#endif
/*
void error(const std::string& message) {
    std::cerr << "Error: " << message << std::endl;
    exit(1);
}
*/
void split(const std::string& line, char delim,
        std::vector<std::string>& elems) {

    std::stringstream lineStream(line);
    std::string token;

    elems.clear();

    while (std::getline(lineStream, token, delim)) {
        if (token.length() > 0) elems.push_back(token);
    }    
}

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

#endif

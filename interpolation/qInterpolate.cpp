#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION

#include "Python.h"
#include "numpy/arrayobject.h"
#include "timekeeper.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <sstream>

#include <cstdlib>

#define QUANTILE_Q 50
#define DIV 30
#define NUM_PTS 150

#define WEIRD_MACRO_AFTER_INITIALIZE_IN_MAIN import_array1(-1);

PyObject* getKernelDensityEstimateRef;
PyObject* calculateBoxIntegralRef;
PyObject* getDensitySurfaceValueRef;

void error(const std::string& message);

struct Vector2 {
    double x, y;
};

struct PythonDensityObject {
    PyObject* kernel;
    double minU, minV;
    double maxU, maxV;
};

//
// python stuff
//

PyObject* getFunctionRef(PyObject* module, const char* functionName) {
    PyObject* pFunc = PyObject_GetAttrString(module, functionName);

    if (pFunc == NULL) error("unable to load function");
    if (!PyCallable_Check(pFunc)) error("unable to load function");

    return pFunc;
}

PyObject* getKernelDensityEstimate(const std::vector<double>& X,
        const std::vector<double>& Y) {
    long dim[1];
    dim[0] = X.size();

    double* arrayX = new double[X.size()];
    std::copy(X.begin(), X.end(), arrayX);

    double* arrayY = new double[Y.size()];
    std::copy(Y.begin(), Y.end(), arrayY);

    PyObject* argX = PyArray_SimpleNewFromData(1, dim, NPY_DOUBLE, arrayX);
    PyObject* argY = PyArray_SimpleNewFromData(1, dim, NPY_DOUBLE, arrayY);

    PyObject* args = PyTuple_New(2);
    PyTuple_SetItem(args, 0, argX);
    PyTuple_SetItem(args, 1, argY);

    PyObject* value = PyObject_CallObject(getKernelDensityEstimateRef, args);

    //Py_CLEAR(argX);
    //Py_CLEAR(argY);
    //Py_CLEAR(args);

    return value;
}

double calculateBoxIntegral(PyObject* kernel, double minX, double minY,
        double maxX, double maxY) {

    PyObject* argMinX = PyFloat_FromDouble(minX);
    PyObject* argMinY = PyFloat_FromDouble(minY);
    PyObject* argMaxX = PyFloat_FromDouble(maxX);
    PyObject* argMaxY = PyFloat_FromDouble(maxY);

    PyObject* args = PyTuple_New(5);
    PyTuple_SetItem(args, 0, kernel);
    PyTuple_SetItem(args, 1, argMinX);
    PyTuple_SetItem(args, 2, argMinY);
    PyTuple_SetItem(args, 3, argMaxX);
    PyTuple_SetItem(args, 4, argMaxY);

    PyObject* value = PyObject_CallObject(calculateBoxIntegralRef, args);
    double output = PyFloat_AsDouble(value);

    //Py_CLEAR(argMinX);
    //Py_CLEAR(argMinY);
    //Py_CLEAR(argMaxX);
    //Py_CLEAR(argMaxY);
    //Py_CLEAR(args);
    //Py_CLEAR(value);

    return output;
}

double getDensitySurfaceValue(PyObject* kernel, double posX, double posY) {
    PyObject* argPosX = PyFloat_FromDouble(posX);
    PyObject* argPosY = PyFloat_FromDouble(posY);

    PyObject* args = PyTuple_New(3);
    PyTuple_SetItem(args, 0, kernel);
    PyTuple_SetItem(args, 1, argPosX);
    PyTuple_SetItem(args, 2, argPosY);

    PyObject* value = PyObject_CallObject(getDensitySurfaceValueRef, args);
    double output = PyFloat_AsDouble(value);

    //Py_CLEAR(argPosX);
    //Py_CLEAR(argPosY);
    //Py_CLEAR(args);
    //Py_CLEAR(value);

    return output;
}

void initialize(int argc, char** argv) {
    Py_Initialize();
    PySys_SetArgv(argc, argv);

    PyObject* name = PyString_FromString("kde");

    PyObject* module = PyImport_Import(name);
    if (module == NULL) error("unable to load module");

    getKernelDensityEstimateRef = getFunctionRef(module, "getKernelDensityEstimate");
    calculateBoxIntegralRef = getFunctionRef(module, "calculateBoxIntegral");
    getDensitySurfaceValueRef = getFunctionRef(module, "getDensitySurfaceValue");

    Py_CLEAR(name);
    Py_CLEAR(module);
}

void setObjectData(PythonDensityObject& dobj, std::vector<Vector2>& v) {
    std::vector<double> X(v.size());
    std::vector<double> Y(v.size());

    dobj.minU = dobj.maxU = v[0].x;
    dobj.minV = dobj.maxV = v[0].y;

    for (unsigned i = 0; i < v.size(); ++i) {
        X[i] = v[i].x;
        Y[i] = v[i].y;

        if (X[i] < dobj.minU) dobj.minU = X[i];
        if (X[i] > dobj.maxU) dobj.maxU = X[i];

        if (Y[i] < dobj.minV) dobj.minV = Y[i];
        if (Y[i] > dobj.maxV) dobj.maxV = Y[i];
    }

    dobj.kernel = getKernelDensityEstimate(X, Y);
}

double getObjectBoxIntegral(PythonDensityObject& dobj,
        double minU, double minV, double maxU, double maxV) {

    return calculateBoxIntegral(dobj.kernel, minU, minV, maxU, maxV);
}

double getObjectSurfaceValue(PythonDensityObject& dobj, const Vector2& pos) {
    return getDensitySurfaceValue(dobj.kernel, pos.x, pos.y);
}

void cleanup() {
    Py_CLEAR(getKernelDensityEstimateRef);
    Py_CLEAR(calculateBoxIntegralRef);
    Py_CLEAR(getDensitySurfaceValueRef);
    Py_Finalize();
}

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
            if (currentDistance - pointDistances > distances[current]) {
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

void calculateCDF(PythonDensityObject& dobj,
        const std::vector<double>& quantiles,
        std::vector<std::list<Vector2> >& quantilePoints) {

    const double TOL = 0.5 / QUANTILE_Q;
    const double differentialU = (dobj.maxU - dobj.minU) / (DIV - 1);
    const double differentialV = (dobj.maxV - dobj.minV) / (DIV - 1);

    for (unsigned i = 0; i < DIV; ++i) {
        for (unsigned j = 0; j < DIV; ++j) {
            double u = dobj.minU + i * differentialU;
            double v = dobj.minV + j * differentialV;

            double d = getObjectBoxIntegral(dobj, dobj.minU, dobj.minV, u, v);

            for (unsigned k = 0; k < quantiles.size(); ++k) {
                double q = quantiles[k];

                if ((q - TOL < d) && (q + TOL > d)) {
                    Vector2 point;
                    point.x = u;
                    point.y = v;

                    quantilePoints[k].push_back(point);
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

void evaluatePDFValues(PythonDensityObject& dobjA,
        const std::vector<std::vector<Vector2> >& qcurvesA,
        PythonDensityObject& dobjB,
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

            double valueA = getObjectSurfaceValue(dobjA, vectorA);
            double valueB = getObjectSurfaceValue(dobjB, vectorB);

            ipdf[k][i] = valueA * valueB;
            ipdf[k][i] /= (1.0 - alpha) * valueB + alpha * valueA;
        }
    }
}

int main(int argc, char** argv) {
    initialize(argc, argv);
WEIRD_MACRO_AFTER_INITIALIZE_IN_MAIN

    timekeeper myTimer;

    if (argc < 3) error("please provide vector sample files");

    std::string outputFile = "interpolatedPDF";
    if (argc > 3) outputFile = argv[3];

    //
    // distribution A
    //

    std::vector<Vector2> vectorSamplesA;
    PythonDensityObject kernelDensityA;
    std::vector<double> quantilesA;
    std::vector<std::list<Vector2> > quantilePointsA;
    std::vector<std::vector<Vector2> > quantileCurvesA;

    readSamplesFile(argv[1], vectorSamplesA);
    generateQuantiles(QUANTILE_Q, quantilesA);

    if (vectorSamplesA.size() == 0) error("no vector samples found");

    quantilePointsA.resize(quantilesA.size());
    for (unsigned i = 0; i < quantilePointsA.size(); ++i)
        quantilePointsA[i] = std::list<Vector2>();

    setObjectData(kernelDensityA, vectorSamplesA);

    std::cout << "calculating CDF of distribution A..." << std::endl;
    myTimer.start();
    calculateCDF(kernelDensityA, quantilesA, quantilePointsA);
    myTimer.stop();
    std::cout << " -time: " << myTimer.getElapsedRealMS() << std::endl;
    myTimer.clear();

    std::cout << "parameterizing quantiles of distribution A..." << std::endl;
    myTimer.start();
    parameterizeQuantiles(quantilePointsA, quantilesA, quantileCurvesA);
    myTimer.stop();
    std::cout << " -time: " << myTimer.getElapsedRealMS() << std::endl;
    myTimer.clear();

    saveQuantileCurvesFile("curvesA", quantileCurvesA);

    //
    // distribution B
    //

    std::vector<Vector2> vectorSamplesB;
    PythonDensityObject kernelDensityB;
    std::vector<double> quantilesB;
    std::vector<std::list<Vector2> > quantilePointsB;
    std::vector<std::vector<Vector2> > quantileCurvesB;

    readSamplesFile(argv[2], vectorSamplesB);
    generateQuantiles(QUANTILE_Q, quantilesB);

    if (vectorSamplesB.size() == 0) error("no vector samples found");

    quantilePointsB.resize(quantilesB.size());
    for (unsigned i = 0; i < quantilePointsB.size(); ++i)
        quantilePointsB[i] = std::list<Vector2>();

    setObjectData(kernelDensityB, vectorSamplesB);

    std::cout << "calculating CDF of distribution B..." << std::endl;
    myTimer.start();
    calculateCDF(kernelDensityB, quantilesB, quantilePointsB);
    myTimer.stop();
    std::cout << " -time: " << myTimer.getElapsedRealMS() << std::endl;
    myTimer.clear();

    std::cout << "parameterizing quantiles of distribution B..." << std::endl;
    myTimer.start();
    parameterizeQuantiles(quantilePointsB, quantilesB, quantileCurvesB);
    myTimer.stop();
    std::cout << " -time: " << myTimer.getElapsedRealMS() << std::endl;
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
        myTimer.clear();

        //saveQuantileCurvesFile("curvesOut", quantileCurvesOut);

        std::cout << "evaluating interpolant PDF values..." << std::endl;
        myTimer.start();
        evaluatePDFValues(kernelDensityA, quantileCurvesA, kernelDensityB,
            quantileCurvesB, alpha, interpolatedPDFValues);
        myTimer.stop();
        std::cout << " -time: " << myTimer.getElapsedRealMS() << std::endl;
        myTimer.clear();

        savePDFFile(outputFile, quantileCurvesOut, interpolatedPDFValues, i);
    }

    cleanup();

    std::cout << "done." << std::endl;
    return 0;
}


#include "Interpolator.h"
#include "timekeeper.h"
#include "DensityObject.h"

#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#ifndef max
#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })
#endif
/*
void error(const std::string& message) {
	std::cerr << "ERROR: " << message << std::endl;
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

void createSampleGrid1D(double minX, double maxX,
		unsigned density,
		std::vector<Vector<1,double> >& samplesPos) {

	unsigned total = density;
	samplesPos.resize(total);

	double dx = (maxX - minX) / (density - 1);

	for (unsigned i = 0; i < total; ++i) {
		samplesPos[i][0] = minX + i * dx;
	}
}
*/
void createSampleGrid2D(double minX, double maxX,
		double minY, double maxY,
		unsigned density,
		std::vector<Vector<2,double> >& samplesPos) {

	unsigned total = density * density;
	samplesPos.resize(total);

	double dx = (maxX - minX) / (density - 1);
	double dy = (maxY - minY) / (density - 1);

	for (unsigned i = 0; i < total; ++i) {
		unsigned iX = i / density;
		unsigned iY = i % density;

		samplesPos[i][0] = minX + iX * dx;
		samplesPos[i][1] = minY + iY * dy;
	}
}
/*
void readData1D(std::vector<Vector<1,double> >& samplesPos,
		std::vector<double>& values,
		std::ifstream& in_file) {
	std::string line;
	std::vector<std::string> tokens;

	getline(in_file, line);
	split(line, ' ', tokens);
	double minX = atof(tokens[0].c_str());
	double maxX = atof(tokens[1].c_str());

	std::vector<double> data;

	while(getline(in_file, line)) {
		data.push_back(atof(line.c_str()));
	}

	if (data.size() == 0)
		error("unable to extract data from file");

	createSampleGrid1D(minX, maxX, data.size(), samplesPos);

	unsigned total = data.size();
	values.resize(total);

	for (unsigned i = 0; i < total; ++i) {
		values[i] = data[i];
	}
}

void readData2D(std::vector<Vector<2,double> >& samplesPos,
		std::vector<double>& values,
		std::ifstream& in_file) {
	std::string line;
	std::vector<std::string> tokens;

	getline(in_file, line);
	split(line, ' ', tokens);
	double minX = atof(tokens[0].c_str());
	double maxX = atof(tokens[1].c_str());

	getline(in_file, line);
	split(line, ' ', tokens);
	double minY = atof(tokens[0].c_str());
	double maxY = atof(tokens[1].c_str());

	std::vector<std::vector<double> > data;

	while(getline(in_file, line)) {
		std::vector<double> temp;
		split(line, ' ', tokens);

		for (int i = 0; i < tokens.size(); ++i) {
			temp.push_back(atof(tokens[i].c_str()));
		}

		data.push_back(temp);
	}

	if (data.size() == 0)
		error("unable to extract data from file");

	if (data.size() != data[0].size())
		error("extracted data does not form square grid");

	createSampleGrid2D(minX, maxX, minY, maxY,
		data.size(), samplesPos);

	unsigned total = data.size() * data.size();
	values.resize(total);

	for (unsigned i = 0; i < total; ++i) {
		unsigned iX = i / data.size();
		unsigned iY = i % data.size();

		values[i] = data[iX][iY];
	}
}

void writeData1D(std::vector<double>& values,
		double minX, double maxX,
		const std::string& filename, int step) {
	std::ostringstream s;
	s << filename << step;

	std::ofstream out_file(s.str().c_str());

	out_file << "1" << std::endl;
	out_file << minX << " " << maxX << std::endl;

	for (unsigned i = 0; i < values.size(); ++i) {
		out_file << values[i] << std::endl;
	}

	out_file.close();
}
*/
void writeData2D(std::vector<double>& values,
		double minX, double maxX, double minY, double maxY,
		const std::string& filename, int step) {
	std::ostringstream s;
	s << filename << step;

	std::ofstream out_file(s.str().c_str());

	out_file << "2" << std::endl;
	out_file << minX << " " << maxX << std::endl;
	out_file << minY << " " << maxY << std::endl;

	unsigned N = (unsigned)sqrt( (double)values.size() );

	for (unsigned i = 0; i < N; i++) {
		for (unsigned j = 0; j < N; j++) {
			if (j != 0) out_file << " ";

			out_file << values[i*N + j];
		}
		if (i != N - 1) out_file << std::endl;
	}

	out_file.close();
}

int main(int argc, char** argv) {
	if (argc < 3)
		error("must provide two data files to interpolate");

	unsigned density = 50;
	unsigned alphaSteps = 6;

	timekeeper myTimer;
	unsigned pdfAConstructionRealTime, pdfBConstructionRealTime;
	unsigned pdfAConstructionClockTime, pdfBConstructionClockTime;
	unsigned precomputationRealTime, precomputationClockTime;
	unsigned sumOfInterpolationRealTimes = 0;
	unsigned sumOfInterpolationClockTimes = 0;

	std::string filename = "interpolated";
	if (argc > 3) filename = argv[3];

	Vector2 pos;

	std::vector<Vector2> vectorsA;
	std::vector<Vector<2,double> > samplesPosA;
	std::vector<double> valuesA;

	readSamplesFile(argv[1], vectorsA);
	DensityObject dobjA(vectorsA);
	createSampleGrid2D(dobjA.getMin().x, dobjA.getMax().x, dobjA.getMin().y,
		dobjA.getMax().y, density, samplesPosA);

	valuesA.resize(samplesPosA.size());
	myTimer.start();
	for (unsigned i = 0; i < samplesPosA.size(); ++i) {
		pos.x = samplesPosA[i][0];
		pos.y = samplesPosA[i][1];
		valuesA[i] = dobjA.evaluate(pos);
	}
	myTimer.stop();
	pdfAConstructionRealTime = myTimer.getElapsedRealMS();
	pdfAConstructionClockTime = myTimer.getElapsedClockMS();
	myTimer.clear();

	std::vector<Vector2> vectorsB;
	std::vector<Vector<2,double> > samplesPosB;
	std::vector<double> valuesB;

	readSamplesFile(argv[2], vectorsB);
	DensityObject dobjB(vectorsB);
	createSampleGrid2D(dobjB.getMin().x, dobjB.getMax().x, dobjB.getMin().y,
		dobjB.getMax().y, density, samplesPosB);

	valuesB.resize(samplesPosB.size());
	myTimer.start();
	for (unsigned i = 0; i < samplesPosB.size(); ++i) {
		pos.x = samplesPosB[i][0];
		pos.y = samplesPosB[i][1];
		valuesB[i] = dobjB.evaluate(pos);
	}
	myTimer.stop();
	pdfBConstructionRealTime = myTimer.getElapsedRealMS();
	pdfBConstructionClockTime = myTimer.getElapsedClockMS();
	myTimer.clear();
/*
	std::ifstream in_fileA(argv[1]);
	if (!in_fileA.is_open())
		error("unable to open first data file");

	std::ifstream in_fileB(argv[2]);
	if (!in_fileB.is_open())
		error("unable to open second data file");

	std::string firstLineA, firstLineB;

	getline(in_fileA, firstLineA);
	getline(in_fileB, firstLineB);

	int dimensionsA = atoi(firstLineA.c_str());
	int dimensionsB = atoi(firstLineB.c_str());

	if (dimensionsA != dimensionsB)
		error("unequal dimensions of two data sets");

	if (dimensionsA < 1)
		error("dimensions cannot be determined");

	if (dimensionsA > 2 || dimensionsA == 1)
		error("number of dimensions unsupported");

	std::vector<double> valuesA;
	std::vector<double> valuesB;
	std::vector<double> valuesOut;

	if (dimensionsA == 1) {
		std::vector<Vector<1,double> > samplesPosA;
		std::vector<Vector<1,double> > samplesPosB;
		std::vector<Vector<1,double> > samplesPosOut;

		readData1D(samplesPosA, valuesA, in_fileA);
		readData1D(samplesPosB, valuesB, in_fileB);

		Interpolator<1,double> interp(samplesPosA, valuesA,
			samplesPosB, valuesB, sqrDistLinear, rbfFuncLinear,
			interpolateBinsLinear, 2, 1);

		myTimer.start();
		interp.precompute();

		myTimer.stop();
		precomputationRealTime = myTimer.getElapsedRealMS();
		precomputationClockTime = myTimer.getElapsedClockMS();
		myTimer.clear();

		double minX = min(samplesPosA[0][0], samplesPosB[0][0]);
		double maxX = max(samplesPosA[samplesPosA.size() - 1][0],
			samplesPosB[samplesPosB.size() - 1][0]);

		createSampleGrid1D(minX, maxX, density, samplesPosOut);

		for (int i = 0; i < alphaSteps; ++i) {
			double alpha = (double)i / (alphaSteps - 1);

			myTimer.start();
			interp.interpolate(alpha, samplesPosOut, valuesOut);
			myTimer.stop();
			sumOfInterpolationRealTimes += myTimer.getElapsedRealMS();
			sumOfInterpolationClockTimes += myTimer.getElapsedClockMS();
			myTimer.clear();

			writeData1D(valuesOut, minX, maxX, filename, i);
		}
	}

	if (dimensionsA == 2) {
		std::vector<Vector<2,double> > samplesPosA;
		std::vector<Vector<2,double> > samplesPosB;
		std::vector<Vector<2,double> > samplesPosOut;

		readData2D(samplesPosA, valuesA, in_fileA);
		readData2D(samplesPosB, valuesB, in_fileB);
*/
		Interpolator<2,double> interp(samplesPosA, valuesA,
			samplesPosB, valuesB, sqrDistLinear, rbfFuncLinear,
			interpolateBinsLinear, 2, 1);

		myTimer.start();
		interp.precompute();

		myTimer.stop();
		precomputationRealTime = myTimer.getElapsedRealMS();
		precomputationClockTime = myTimer.getElapsedClockMS();
		myTimer.clear();

		double minX = min(samplesPosA[0][0], samplesPosB[0][0]);
		double maxX = max(samplesPosA[samplesPosA.size() - 1][0],
			samplesPosB[samplesPosB.size() - 1][0]);

		double minY = min(samplesPosA[0][1], samplesPosB[0][1]);
		double maxY = max(samplesPosA[samplesPosA.size() - 1][1],
			samplesPosB[samplesPosB.size() - 1][1]);

		std::vector<Vector<2,double> > samplesPosOut;
		std::vector<double> valuesOut;
		createSampleGrid2D(minX, maxX, minY, maxY,
			density, samplesPosOut);

		for (int i = 0; i < alphaSteps; ++i) {
			double alpha = (double)i / (alphaSteps - 1);

			myTimer.start();
			interp.interpolate(alpha, samplesPosOut, valuesOut);

			myTimer.stop();
			sumOfInterpolationRealTimes += myTimer.getElapsedRealMS();
			sumOfInterpolationClockTimes += myTimer.getElapsedClockMS();
			myTimer.clear();

			writeData2D(valuesOut, minX, maxX, minY, maxY,
				filename, i);
		}
	/*}

	in_fileA.close();
	in_fileB.close();
*/
	FILE* timingRecord = fopen("timing", "a");
	fprintf(timingRecord, "entry start\n");
	fprintf(timingRecord, "PDF A construction (ms): %u\n", pdfAConstructionRealTime);
	fprintf(timingRecord, "PDF A construction (clock ms): %u\n", pdfAConstructionClockTime);
	fprintf(timingRecord, "PDF B construction (ms): %u\n", pdfBConstructionRealTime);
	fprintf(timingRecord, "PDF B construction (clock ms): %u\n", pdfBConstructionClockTime);
	fprintf(timingRecord, "precomputation (ms): %u\n", precomputationRealTime);
	fprintf(timingRecord, "precomputation (clock ms): %u\n", precomputationClockTime);
	fprintf(timingRecord, "total interpolation (ms): %u\n", sumOfInterpolationRealTimes);
	fprintf(timingRecord, "total interpolation (clock ms): %u\n", sumOfInterpolationClockTimes);
	fprintf(timingRecord, "interpolation count: %d\n", alphaSteps);
	fprintf(timingRecord, "\n");
	fclose(timingRecord);

	return 0;
}

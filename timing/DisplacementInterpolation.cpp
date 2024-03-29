// Quick Note: this is the toy example provided by the displacement
// interpolation paper with some timing code added.

////////////////////////////////////////////////////////////////////////
// DisplacementInterpolation.cpp  , Sept 12th 2011
// Displacement Interpolation toy example using the Interpolator class
// author: Nicolas Bonneel
// Copyright 2011 Nicolas Bonneel, Michiel van de Panne, Sylvain Paris, Wolfgang Heidrich.
// All rights reserved. Web: http://www.cs.ubc.ca/labs/imager/tr/2011/DisplacementInterpolation/
//
// The Interpolator is free software: you can 
// redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Note : This example is intended to be a toy example only. For efficient
// displacement interpolation of images, please refer for example to 
// "Optimal Mass Transport for Registration and Warping", Haker et al. 2004
// This code is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty 
// of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
// See the GNU General Public License for more details.
//
// If you use this code for research purpose, please reference
// the following paper :
//
// Nicolas Bonneel, Michiel van de Panne, Sylvain Paris, Wolfgang Heidrich
// "Diplacement Interpolation using Lagrangian Mass Transport", 
// ACM Transactions on Graphics (Proceedings of SIGGRAPH ASIA 2011)
///////////////////////////////////////////////////////////////////////////

#include "Interpolator.h"
#include <vector>

// --added for timing code-- //
#include <ctime>
#include <time.h>

// --added for timing code-- //
class timekeeper {
	struct timespec realTimeStart;
	struct timespec realTimeStop;

	unsigned clockTimeStart;
	unsigned clockTimeStop;

public:
	void clear() {
		memset(&realTimeStart, 0, sizeof(realTimeStart));
		memset(&realTimeStop, 0, sizeof(realTimeStop));

		clockTimeStart = 0;
		clockTimeStop = 0;
	}

	timekeeper() {
		clear();
	}

	void start() {
		clock_gettime(CLOCK_MONOTONIC, &realTimeStart);
		clockTimeStart = clock();
	}

	void stop() {
		clock_gettime(CLOCK_MONOTONIC, &realTimeStop);
		clockTimeStop = clock();
	}

	unsigned getElapsedRealMS() {
		unsigned milliseconds = 1000 * (realTimeStop.tv_sec - realTimeStart.tv_sec);
		milliseconds += (realTimeStop.tv_nsec - realTimeStart.tv_nsec) / 1000000;

		return milliseconds;
	}

	unsigned getElapsedClockMS() {
		unsigned milliseconds = clockTimeStop - clockTimeStart;
		milliseconds /= (CLOCKS_PER_SEC / 1000);

		return milliseconds;
	}
};

void saveFile(int i, std::vector<double> &values)
{
	std::ostringstream s;
	s<<"out"<<i<<".txt";
	FILE* f = fopen(s.str().c_str(), "w+");
	unsigned int N = (unsigned int) sqrt((double) values.size());
	for (unsigned int i=0; i<N; i++)
	{
		for (unsigned int j=0; j<N; j++)
			fprintf(f, "%f ", values[i*N+j]);
		fprintf(f, "\n");
	}
	fclose(f);
}

int main()
{
	// --added for timing code-- //
	timekeeper myTimer;
	unsigned precomputationRealTime, precomputationClockTime;
	unsigned sumOfInterpolationRealTimes = 0;
	unsigned sumOfInterpolationClockTimes = 0;

	int W=50;

	std::vector<Vector<2,double> > samplesPos(W*W);
	std::vector<double> values1(W*W, 0.);
	std::vector<double> values2(W*W, 0.);
	std::vector<double> valuesR(W*W, 0.);

	for (int i=0; i<W; i++)
	{
		for (int j=0; j<W; j++)
		{
			samplesPos[i*W+j] = Vector<2,double>(i/(double)W,j/(double)W); // the data lie on the unit grid
			values1[i*W+j] = 0.;
			values2[i*W+j] = 0.;
	
			// generate a square
			if (i>5 && i<45 && j>5 && j<45)
				values1[i*W+j] = 1;
			else
				values1[i*W+j] = 0;

			// generate a disk
			if ((i-25)*(i-25)+(j-25)*(j-25)<509)
				values2[i*W+j] = 1;
			else
				values2[i*W+j] = 0;
		}
	}

	Interpolator<2,double> interp(samplesPos, values1,  // source distribution, in R^2 
		samplesPos, values2,							// target distribution
		sqrDistLinear, rbfFuncLinear, interpolateBinsLinear, // how to represent and move the particles
		2,												// particle spread : distance to 2nd nearest neighbor at each sample point
		1);											   // 1 frequency band (standard displacement interpolation)

	// --added for timing code-- //
	myTimer.start();

	interp.precompute();

	// --added for timing code-- //
	myTimer.stop();
	precomputationRealTime = myTimer.getElapsedRealMS();
	precomputationClockTime = myTimer.getElapsedClockMS();
	myTimer.clear();

	int N = 50; // we get 50 intermediate steps
	for (int p=0; p<N; p++)
	{
		double alpha = p/((double)N-1.);

		// --added for timing code-- //
		myTimer.start();

		interp.interpolate(alpha, samplesPos, valuesR);

		// --added for timing code-- //
		myTimer.stop();
		sumOfInterpolationRealTimes += myTimer.getElapsedRealMS();
		sumOfInterpolationClockTimes += myTimer.getElapsedClockMS();
		myTimer.clear();

		saveFile(p, valuesR);
	}

	// --added for timing code-- //
	FILE* timingRecord = fopen("timing", "a");
	fprintf(timingRecord, "entry start\n");
	fprintf(timingRecord, "precomputation (ms): %u\n", precomputationRealTime);
	fprintf(timingRecord, "precomputation (clock ms): %u\n", precomputationClockTime);
	fprintf(timingRecord, "total interpolation (ms): %u\n", sumOfInterpolationRealTimes);
	fprintf(timingRecord, "total interpolation (clock ms): %u\n", sumOfInterpolationClockTimes);
	fprintf(timingRecord, "interpolation count: %d\n", N);
	fprintf(timingRecord, "\n");

	return 0;
}


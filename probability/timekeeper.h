#ifndef _TIMEKEEPER_H_
#define _TIMEKEEPER_H_

#include <ctime>
#include <time.h>

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

#endif


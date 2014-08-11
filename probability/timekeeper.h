#ifndef _TIMEKEEPER_H_
#define _TIMEKEEPER_H_

#include <ctime>
#include <cstring>
#include <sys/resource.h>

class timekeeper {
	struct timespec realTimeStart;
	struct timespec realTimeStop;

	struct rusage clockTimeStart;
	struct rusage clockTimeStop;

public:
	void clear() {
		memset(&realTimeStart, 0, sizeof(realTimeStart));
		memset(&realTimeStop, 0, sizeof(realTimeStop));

		memset(&clockTimeStart, 0, sizeof(clockTimeStart));
		memset(&clockTimeStop, 0, sizeof(clockTimeStop));
	}

	timekeeper() {
		clear();
	}

	void start() {
		clear();

		clock_gettime(CLOCK_MONOTONIC, &realTimeStart);
		getrusage(RUSAGE_SELF, &clockTimeStart);
	}

	void stop() {
		clock_gettime(CLOCK_MONOTONIC, &realTimeStop);
		getrusage(RUSAGE_SELF, &clockTimeStop);
	}

	unsigned getElapsedRealMS() {
		unsigned milliseconds = 1000 * (realTimeStop.tv_sec - realTimeStart.tv_sec);
		milliseconds += (realTimeStop.tv_nsec - realTimeStart.tv_nsec) / 1000000;

		return milliseconds;
	}

	unsigned getElapsedClockMS() {
		unsigned milliseconds = 1000 * (clockTimeStop.ru_utime.tv_sec -
			clockTimeStart.ru_utime.tv_sec);
		milliseconds += (clockTimeStop.ru_utime.tv_usec -
			clockTimeStart.ru_utime.tv_usec) / 1000;

		milliseconds += 1000 * (clockTimeStop.ru_stime.tv_sec -
			clockTimeStart.ru_stime.tv_sec);
		milliseconds += (clockTimeStop.ru_stime.tv_usec -
			clockTimeStart.ru_stime.tv_usec) / 1000;

		return milliseconds;
	}
};

#endif


#include "timer.h"

namespace util{
	Timer::Timer(bool start) {
		if (start == 1) {
			start_time = std::chrono::high_resolution_clock::now();
		}
	}
	long long Timer::getElapsed() {
		return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start_time).count();
	}
	void Timer::refresh() {
		start_time = std::chrono::high_resolution_clock::now();
	}
}
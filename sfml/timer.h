#pragma once

#include <chrono>

namespace util {
	class Timer {
	public:
		Timer(bool start);
		long long getElapsed();
		void refresh();
	private:
		std::chrono::high_resolution_clock::time_point start_time;
	};
}
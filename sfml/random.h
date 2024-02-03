#pragma once

#include <random>

class Procedural {
public:
	Procedural(unsigned int seed);
	long long getRandomNumber(long long boundary = LLONG_MAX);
private:
	std::mt19937 rng;    // random-number engine used (Mersenne-Twister in this case)
	std::uniform_int_distribution<long long> uni; // guaranteed unbiased
};
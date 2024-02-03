#include "random.h"

Procedural::Procedural(unsigned int seed)
	: rng(seed) {

}
long long Procedural::getRandomNumber(long long boundary) {
	return uni(rng) % boundary;
}
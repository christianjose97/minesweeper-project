#include "Randomizer.h"
#include <ctime>

std::mt19937 Randomizer::random(time(0));

int Randomizer::Int(int min, int max)
{
	std::uniform_int_distribution<int> dist(min, max);
	return dist(random);
}

float Randomizer::Float(float min, float max)
{
	std::uniform_real_distribution<float> dist(min, max);
	return dist(random);
}

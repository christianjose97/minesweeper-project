#pragma once
#include <random>

class Randomizer
{

	static std::mt19937 random;
public:

	static int Int(int min, int max);

	static float Float(float min, float max);

};


#pragma once

#include <cstdlib>

class Random
{
public:
	Random() = default;
	~Random() = default;

	static unsigned int NextInt(unsigned int max)
	{
		return 0 + (rand() % static_cast<int>(max - 0 + 1));
	}	
};

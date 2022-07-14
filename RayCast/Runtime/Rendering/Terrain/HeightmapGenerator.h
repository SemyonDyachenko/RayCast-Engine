#ifndef HEIGHTMAP_GENERATOR_H
#define HEIGHTMAP_GENERATOR_H

#include "../../Core/Random.h"
#include <glm.hpp>

#include <iostream>
#include <ctime>
#include <random>



class HeightmapGenerator
{
public:
	HeightmapGenerator();

	float GenerateHeight(int x,int z);

private:
	float GetNoise(int x, int z);

	float GetSmoothNoise(int x, int z);

	float Interpolate(float a,float b,float blend);

	float GetInterpolatedNoise(float x, float z);
private:

	int m_Seed;
	float m_Aplitude = 70.f;
};

#endif
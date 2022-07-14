#include "HeightmapGenerator.h"

namespace RayCast {

	HeightmapGenerator::HeightmapGenerator()
	{
		srand(time(0));
		m_Seed = rand() % 100000000;

	}

	float HeightmapGenerator::GenerateHeight(int x, int z)
	{
		float total = GetInterpolatedNoise(x / 8.f, z / 8.f) * m_Aplitude;
		total += GetInterpolatedNoise(x / 4.f, z / 4.f) * m_Aplitude / 3.f;
		total += GetInterpolatedNoise(x / 2.f, z / 2.f) * m_Aplitude / 9.f;
		total += GetInterpolatedNoise(x, z) * m_Aplitude / 27.f;
		return total;
	}

	float HeightmapGenerator::GetNoise(int x, int z)
	{
		srand(x * 49632 + z * 325176 + m_Seed);
		return ((float)rand() / (float)(RAND_MAX)) * 2.f - 1.f;
	}

	float HeightmapGenerator::GetSmoothNoise(int x, int z)
	{
		float corners = (GetNoise(x - 1, z - 1) + GetNoise(x + 1, z - 1)
			+ GetNoise(x - 1, z + 1) + GetNoise(x + 1, z + 1)) / 16.0f;
		float sides = (GetNoise(x - 1, z) + GetNoise(x + 1, z)
			+ GetNoise(x, z + 1) + GetNoise(x, z + 1)) / 8.0f;
		float center = GetNoise(x, z) / 4.0f;
		return corners + sides + center;
	}

	float HeightmapGenerator::Interpolate(float a, float b, float blend)
	{
		double theta = blend * 3.1456; // PI
		float f = (float)(1.0f - cos(theta)) * 0.5f;
		return a * (1.0f - f) + b * f;

	}

	float HeightmapGenerator::GetInterpolatedNoise(float x, float z)
	{
		int intX = (int)(x);
		int intZ = (int)(z);

		float fracX = x - intX;
		float fracZ = z - intZ;

		float v1 = GetSmoothNoise(intX, intZ);
		float v2 = GetSmoothNoise(intX + 1, intZ);
		float v3 = GetSmoothNoise(intX, intZ + 1);
		float v4 = GetSmoothNoise(intX + 1, intZ + 1);
		float i1 = Interpolate(v1, v2, fracX);
		float i2 = Interpolate(v3, v4, fracZ);
		return Interpolate(i1, i2, fracZ);
	}

}
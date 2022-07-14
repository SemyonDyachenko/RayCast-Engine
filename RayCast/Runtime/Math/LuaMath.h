#pragma once

#include <glm.hpp>


class LuaQuaternion
{
	template<unsigned index>
	static float get(glm::quat const* vec)
	{
		if (index == 0)
			return vec->x;
		if (index == 1)
			return vec->y;
		if (index == 2)
			return vec->z;

		return vec->w;
	}

	template<unsigned index>
	static void set(glm::quat* vec, float value)
	{
		if (index == 0) {
			vec->x = value;
			return;
		}
		if (index == 1) {
			vec->y = value;
			return;
		}
		if (index == 2) {
			vec->z = value;
			return;
		}

		vec->w = value;
	}
	
};

class LuaMath
{
public:
	LuaMath() {}
	~LuaMath(){}

	static float Cos(float var)
	{
		return glm::cos(var);
	}

	static float Sin(float var)
	{
		return glm::sin(var);
	}

	static float Tan(float var)
	{
		return glm::tan(var);
	}

	static float PI()
	{
		return 3.149256f;
	}

	static float Radians(float var)
	{
		return glm::radians(var);
	}

};
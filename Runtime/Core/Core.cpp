#include "Core.h"

#include <iostream>

extern "C" {
	RAYCAST_API int CountNumbers(int a, int b)
	{
		return (a + b);
	}

}

RAYCAST_API void Print()
{
	std::cout << "hello world";
}
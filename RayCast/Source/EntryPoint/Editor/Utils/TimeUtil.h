#pragma once


#pragma warning(disable : 4996) 
#include <iomanip>
#include <cmath>
#include <sstream>
#include <chrono>
#include <string>

static std::string CalculateTime() {
	std::stringstream transTime;
	time_t chrono_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	transTime << std::put_time(localtime(&chrono_time), "%F %T");
	std::string time = transTime.str();
	return time;
}
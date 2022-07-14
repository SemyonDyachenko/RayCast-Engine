#pragma once
#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <map>

/*class Timer {
public:
	Timer() {};

	virtual ~Timer() = default;

	void Start() {
		m_Active = true;
		m_StartPoint = std::chrono::high_resolution_clock::now();
	}
	void Stop() {
		m_Active = false;
	}

	double Duration() {
		return m_Duration;
	}	

private:
	double m_Duration = 0.0;
	std::chrono::time_point<std::chrono::steady_clock> m_StartPoint;
	bool m_Active = false;
	static std::map<std::string, Timer*> s_Timers;
	

};*/

#endif
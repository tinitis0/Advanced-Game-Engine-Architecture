/* * \file winTimer */
#pragma once

#include <windows.h>
#include "core/timer.h"

namespace Engine
{
	/** \ class winTimer
	* Windows specific timer using queryPerformanceCount
	*/

	class winTimer : public Timer
	{
	public:
		virtual void start() override 
		{
			QueryPerformanceFrequency(&m_frequency);
			QueryPerformanceCounter(&m_startTime);
		};
		virtual inline void reset() override 
		{
			QueryPerformanceCounter(&m_startTime);
		};

		virtual float getElapsedTime() override 
		{
			QueryPerformanceCounter(&m_endTime);
			float result = (m_endTime.QuadPart - m_startTime.QuadPart) * 1000.f / m_frequency.QuadPart;
			result /= 1000.f;
			return result;
		}
	private:
		LARGE_INTEGER m_startTime; //!< Start timer
		LARGE_INTEGER m_endTime; //!< End timer
		LARGE_INTEGER m_frequency; //!< Tick per second of this CPU
	};
}
/*! \ file timer.h */
#pragma once

#include <chrono>

namespace Engine
{

	/*!
	\class Timer - interface class for timer
	*/

	class Timer
	{
	public:
		virtual void start() = 0; //!< Start timer
		virtual void reset() = 0; //!< Reset Timer
		virtual float getElapsedTime() = 0; //!< Time elapsed
	};
	
	/*!
	\class ChronoTimer - chrono timer class
	*/

	class ChronoTimer : public Timer
	{
	public:
		virtual inline void start() override { m_startPoint = std::chrono::high_resolution_clock::now(); }
		virtual inline void reset() override { m_startPoint = std::chrono::high_resolution_clock::now(); }
		virtual float getElapsedTime() override
		{
			m_endPoint = std::chrono::high_resolution_clock::now(); //!< Chrono Timer
			std::chrono::duration<float, std::milli> elapsed = m_endPoint - m_startPoint; //!< Time in milliseconds
			return elapsed.count() / 1000.f;
		}
	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_startPoint; //!< Start timer
		std::chrono::time_point<std::chrono::high_resolution_clock> m_endPoint; //!< End timer
	};
}
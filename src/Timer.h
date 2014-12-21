#ifndef TIMER_H
#define TIMER_H
#pragma once

#include <SDL2/SDL.h>

namespace tiledl
{

	class Timer
	{
	public:
		Timer();
		~Timer();

		void start();
		void stop();

		Uint32 getDelta();
		Uint32 getCurrentDelta();
		Uint32 getTimerDelta();

		float getDeltams();
		float getDeltas();
		float getDelta(float peroid);
	private:
		Uint32 start_time, stop_time;
		bool timing;
	};
} // namespace frame2d
#endif // TIMER_H

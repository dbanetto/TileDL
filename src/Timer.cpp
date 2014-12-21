#include "Timer.h"

using namespace tiledl;

Timer::Timer()
{
	timing = false;
	start_time = stop_time = 0;
}

Timer::~Timer()
{

}
/**
 * Starts the timer
 *
 * @note if called when already timing, it will reset the start time
 */
void Timer::start()
{
	if (timing) {
		SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "%x : Restarting timer", this);
	}

	timing = true;
	start_time = SDL_GetTicks();
}
/**
 * Stops the timer
 *
 * @note Needs to be timing before hand
 */
void Timer::stop()
{
	if (!timing) {
		SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "%x : Stopping when not timing", this);
		return;
	}

	stop_time = SDL_GetTicks();
	timing = false;
}

/**
 * Get the time difference in ticks between start() and end(), given stop() has been
 * called, otherwise now
 *
 * @return getCurrentDelta() if is timing, or getTimerDelta() when not timing
 * @note Results is undefined if called before start()
 */
Uint32 Timer::getDelta()
{
	if (timing) {
		return SDL_GetTicks() - start_time;
	} else {
		return stop_time - start_time;
	}
}

/**
 * Get the time difference in ticks between start() and now
 *
 * @return Ticks between start time, and now.
 * If start() has not been before, result is undefined.
 */
Uint32 Timer::getCurrentDelta()
{
	return SDL_GetTicks() - start_time;
}

/**
 * Get the time difference in ticks between start() and stop()
 *
 * @return Ticks between start time, and stop time.
 * If start() and stop() has not been before, result is undefined.
 */
Uint32 Timer::getTimerDelta()
{
	return stop_time - start_time;
}

/**
 * Get the time difference using getDelta() divided by a defined period
 *
 * @return a double of getDelta() divided by a period
 */
float Timer::getDelta(float peroid)
{
	return (float)(getDelta()) / peroid;
}

/**
 * Get the time difference using getDelta() in milliseconds
 *
 * @return a double of getDelta() represented in terms of milliseconds
 */
float Timer::getDeltams()
{
	return getDelta(1.0f);
}

/**
 * Get the time difference using getDelta() in seconds
 *
 * @return a double of getDelta() represented in terms of seconds
 */
float Timer::getDeltas()
{
	return getDelta(1000.0f);
}


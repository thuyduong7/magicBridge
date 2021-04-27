#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>

struct Timer
{
		Timer();
        ~Timer();
		void start();
		void stop();
		void pause();
		void unpause();
		Uint32 getTicks();

		Uint32 startTicks;
		Uint32 pausedTicks;
		bool paused;
		bool started;
};

#endif // TIMER_H

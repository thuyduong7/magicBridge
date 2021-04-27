#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>

struct Timer
{
		//Initializes variables
		Timer();
        ~Timer();
		//The various clock actions
		void start();
		void stop();
		void pause();
		void unpause();

		//Gets the timer's time
		Uint32 getTicks();

		//Checks the status of the timer
		bool isStarted();
		bool isPaused();


		//The clock time when the timer started
		Uint32 startTicks;

		//The ticks stored when the timer was paused
		Uint32 pausedTicks;

		//The timer status
		bool paused;
		bool started;
};

#endif // TIMER_H

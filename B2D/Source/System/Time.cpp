#include "System.h"
#include <iostream>

#if defined (_WIN32) || defined (_WIN64)
    #include <time.h>
#elif defined (__gnu_linux__) || defined (__APPLE__)
    #include <sys/time.h>
#endif

///////////////////////////////////////////
//     This File Handles Everything      //
//             Time Related              //
///////////////////////////////////////////

namespace b2d{

	// Init Variables
	double Time::currentTime = 0;
	double Time::previousTime = 0;
	double Time::deltaTime = 0;
    double Time::frameCount = 0;
	double Time::timePerFrame = 0;
	double Time::fps = 0;

	// Gets The Current System Time In Seconds, Minutes, Or Hours
	double Time::GetSystemTime (int SecMinHour){

		// Create Time Variables
		time_t cTime = time (0);
		tm *currentTime = localtime (&cTime);

		// Get Seconds
		if (SecMinHour == 0){
			return currentTime -> tm_sec;
		}

		// Get Minutes
		else if (SecMinHour == 1){
			return currentTime -> tm_min;
		}

		// Get Hours
		else if (SecMinHour == 2){
			return currentTime -> tm_hour;
		}

		// Get Error
		else{

			std::cout << stderr << " Invalid time type selected" << '\n';
			return 0;
		}
	}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Get Delta Time
	void Time::GetDeltaTime(){

        #if defined (_WIN32) || defined (_WIN64)

            Time::currentTime = clock();
            Time::deltaTime = (Time::currentTime - Time::previousTime) / CLOCKS_PER_SEC;
            Time::previousTime = Time::currentTime;

        #elif defined (__gnu_linux__) || defined (__APPLE__)

            timeval t;
            gettimeofday (&t, NULL);
            Time::currentTime = t.tv_usec;
            Time::deltaTime = (Time::currentTime - Time::previousTime) / 100000 / 10;
            Time::previousTime = Time::currentTime;

            if (Time::deltaTime < 0){

                Time::currentTime = t.tv_usec;
                Time::deltaTime = (Time::currentTime - Time::previousTime) / 100000 / 10;
                Time::previousTime = Time::currentTime;
            }

        #endif
	}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Reset Delta Time
	void Time::ResetDeltaTime(){

		Time::currentTime = 0.0;
		Time::deltaTime = 0.0;
		Time::previousTime = 0.0;
	}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Get FPS
	double Time::GetFPS(){

		// If One Second Has Not Passed, Add 1 Frame To Count
		if (Time::timePerFrame < 1){

			++Time::frameCount;
			Time::timePerFrame += Time::deltaTime;
		}

		// Otherwise, Return Frame Count
		else{

			Time::fps = Time::frameCount;
			Time::frameCount = 0;
			Time::timePerFrame = 0;

			return Time::fps;
		}

		return Time::fps;
	}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Wait For Seconds
	void Time::WaitForSeconds (double WaitTime){

		double timer = 0;

		while (timer < WaitTime){

			Time::GetDeltaTime();
			timer += Time::deltaTime;
		}
	}
}

//
//  fps.cpp
//  pendulum
//
//  Created by Ran Bao on 9/23/13.
//  Copyright (c) 2013 R&B. All rights reserved.
//

#include "fps.h"
#include <ctime>
#include <string>

/**
* Get the frame per second
* Method 1: Count the time for tick reach certain value
* @return FPS value
*/
double get_fps_1()
{
	static int count;
	static double save;
	static clock_t last, current;
	double timegap;

	++count;
	if (count <= 10)
		return save;
	count = 0;
	last = current;
	current = clock();
	timegap = (current - last) / (double)CLOCKS_PER_SEC;
	save = 10.0 / timegap;
	return save;
}

/**
* Get the frame per second
* Method 2: Count the frame within certain tick interval
* @return FPS value
*/
float get_fps_2(){
	static unsigned int frame = 0;
	static unsigned int interval = 1000;
	static unsigned int start, end;
	static float f = 0.0f;

	// start counting time
	if (frame == 0){
		start = (unsigned int)clock();
	}

	frame += 1;

	end = (unsigned int)clock();

	if ((end - start) >= interval){
		f = (float)frame / (end - start) * CLOCKS_PER_SEC / 2;
		frame = 0;
	}

	return f;
}

float get_fps_3(){
	static unsigned int frame = 0;
	static unsigned int interval = 10;
	static unsigned int start, end;
	static float f = 0.0f;

	// start takeing time of frame0
	if (frame == 0){
		start = (unsigned int)clock();
	}

	frame += 1;

	if (frame >= interval){
		end = (unsigned int)clock();
		f = (float)interval / (end - start) * CLOCKS_PER_SEC;
		frame = 0;
	}

	return f;
}
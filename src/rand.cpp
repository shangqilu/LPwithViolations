//--------------------------------------------
// this file contains necessary random number
// generators
// 
// collected by Yufei Tao
//--------------------------------------------

#include "rand.h"

#include <math.h>
#include <random>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <vector>


#define WIN

#ifdef WIN
#include <chrono>
#endif





int yufeitao_seed = -1; //the program will use a random seed if this is -1

/************************************************************
 ***  Given a mean and a standard deviation, gaussian       **
 **   generates a normally distributed random number        **
 **   Algorithm:  Polar Method, p.  104, Knuth, vol. 2      **
 ************************************************************/

float gaussian(float mean, float sigma) {
	float v1, v2;
	float s;
	float x;

	do {
		v1 = 2 * uniform(0, 1) - 1;
		v2 = 2 * uniform(0, 1) - 1;
		s = v1 * v1 + v2 * v2;
	} while (s >= 1.);

	x = v1 * (float) sqrt(-2. * log(s) / s);

	/*  x is normally distributed with mean 0 and sigma 1.  */

	x = x * sigma + mean;

	return (x);
}

/************************************************************
 ** Generates a random number between _min and _max         **
 ** uniformly                                               **
 By Yufei Tao
 ************************************************************/
#ifdef WIN

double uniform(float _min, float _max) {
	static bool used_seed = false;
	static std::mt19937 gen(static_cast<long unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count()));

	if (yufeitao_seed < 0) {
		//gen = std::mt19937(rd());
	}
	else {
		if (!used_seed){
			gen = std::mt19937(yufeitao_seed);
			used_seed = true;
		}
	}

	static std::uniform_real_distribution<> dist(_min, _max);

	return dist(gen);
}


#else

double uniform(float _min, float _max) {

	static bool used_seed = false;
	static std::mt19937 gen;
	static std::random_device rd;
	if (yufeitao_seed < 0) {
		gen = std::mt19937(rd());
	} else {
		if (!used_seed){
			gen = std::mt19937(yufeitao_seed);
			used_seed = true;
		}
	}

	std::uniform_real_distribution<> dist(_min, _max);

	return dist(gen);
}
#endif

/************************************************************
** Generates a random integer between _min and _max         **
** uniformly                                               **

************************************************************/
#ifdef WIN

int uniform_int(int _min, int _max)
{
	static bool used_seed = false;
	static std::mt19937 gen(static_cast<long unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count()));

	if (yufeitao_seed < 0) {
		//gen = std::mt19937(rd());
	}
	else {
		if (!used_seed){
			gen = std::mt19937(yufeitao_seed);
			used_seed = true;
		}
	}
	std::uniform_int_distribution<> dist(_min, _max);

	return dist(gen);
}


#else
int uniform_int(int _min, int _max) {

	static bool used_seed = false;
	static std::mt19937 gen;
	static std::random_device rd;
	if (yufeitao_seed < 0) {
		gen = std::mt19937(rd());
	}
	else {
		if (!used_seed){
			gen = std::mt19937(yufeitao_seed);
			used_seed = true;
		}
	}

	std::uniform_int_distribution<> dist(_min, _max);

	return dist(gen);
}

#endif

#ifndef DATAGENERATOR_H_INCLUDED
#define DATAGENERATOR_H_INCLUDED

#include "headers.h"
#include "geometry.h"
#include "fileIO.h"

/*
*   generating a two dimension dataset
*	in the odd quadrant: label is 1
*	in the even quadrant: label is -1
*/
void GenTwoDimensinoGridDataSet(char *filename, int totalNum);


/*
*   generating a dataset
*	all points are in a ball with given radius
*	and the optimal plane has the given margin
*/
void GenMarginDataSet(char *filename, double margin, double radius,
	int totalNum, int noiseNum);


void GenOriginDataSet(char *filename, double margin, double radius,
	int totalNum, int noiseNum);


void GenRandomDataSet(char *filename, double margin, 
	int totalNum, int noiseNum, double ratio);

#endif // DATAGENERATOR_H_INCLUDED

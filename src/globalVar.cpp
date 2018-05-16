#include "globalVar.h"


void PrintError(string msg)
{
	printf("%s\n", msg.c_str());
	exit(0);
}

/*
*  the number of points
*/
int N = -1;
/*
*  the dimensionality of points
*/
int Dim = -1;

/*
*  the percent data for testing or the percent of noise points
*/
double Percent = -1;

/*
*	method
*/
int Method = 0;
/*
*  N*Percent
*/
int K = -1;

/*
*  The chosen radius of dataset.
*/
double Radius = 1;
/*
*  The chosen margin of dataset.
*/
double Margin = 0.1;



int Label_type = 0;



int Sample_size = 1;

/*
*  the approximation for error rate
*/
double Epsilon = 0.1;

/*
*  The failing probability
*/
double Delta = 0.5;

#ifndef GLOBALVAR_H_INCLUDED
#define GLOBALVAR_H_INCLUDED

#include "headers.h"

#include <string>
using namespace std;




void PrintError(string msg);


/*
*  the number of points
*/
extern int N;


/*
*  the dimensionality of points
*/
extern int Dim;

/*
*	the percent of noise points
*/
extern double Percent;

/*
*	method
*/
extern int Method;

/*
*  N*Percent
*/
extern int K;



/*
*  The chosen radius of dataset.
*/
extern double Radius;
/*
*  The chosen margin of dataset.
*/
extern double Margin;



/*
*	the label type
*	0: 1 and others
*	1: <=4 and >= 5
*/
extern int Label_type;
/*
*	sorting type
*/


/*
*	the sampling size in our sampling method
*/
extern int Sample_size;



/*
*  the approximation for error rate
*/
extern double Epsilon;

/*
*  The failing probability
*/
extern double Delta;

#endif // GLOBALVAR_H_INCLUDED

#ifndef KVIOLATION_H_INCLUDED
#define KVIOLATION_H_INCLUDED

#include "headers.h"
#include "geometry.h"

PointIndex Sampling(PointIndex &points, double p);

/*
*	compute a separation hyperplane violating no more than (1+epsilon)*k points
*/
bool ApproximateKViolation(PointSet &points, HyperPlane &optimal_plane);

/*
*	compute a separation hyperplane violating no more than k points
*/
bool KViolation(PointSet &points, HyperPlane &optimal_plane);


#endif

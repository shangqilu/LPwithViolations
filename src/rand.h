//--------------------------------------------
// this function contains necessary random number
// generators
// 
// collected by Yufei Tao
//--------------------------------------------

#ifndef RAND_H
#define RAND_H
#include <vector>

extern int yufeitao_seed;

//--------------------------------------------
float gaussian(float mean, float sigma);
double uniform(float _min, float _max);
int uniform_int(int _min, int _max);
//float new_uniform(float _min, float _max);
//int	  new_uniform(int _d_num);
float zipf(float x1, float x2, double p);
void newzipf_helper(int U, double p, std::vector<double> & cdf);
int newzipf(std::vector<double> &cdf);
//--------------------------------------------
#endif


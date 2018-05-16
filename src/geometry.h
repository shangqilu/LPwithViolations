#ifndef GEOMETRY_H_INCLUDED
#define GEOMETRY_H_INCLUDED

#include "headers.h"
/*
*   the class of a point
*/
class Point{
public:
    double *x;
    int y;

	/*
	*	the remaining copy of the point 
	*/
    int counter;

	/*
	*	the distance from  the point to the origin in kernel space
	*/
	double dis;

	/*in noise perceptron*/
	int alpha;
    Point(int d, double *x)
    {
		this->x = x;
        for (int i = 0; i < d; i++)
            x[i] = 0;
        y = 0;
        counter = 0;
		alpha = 0;
    }

private:
	//Point(const Point& obj){}
	//Point& operator = (const Point & obj) {}
};


/*
*   the class of a hyperplane
*/
class HyperPlane
{
public:
	double *w;  //weights
	double b;   //bias
	int d;      //dimension
	HyperPlane(int d)
	{
		this->w = new double[d];
		for (int i = 0; i < d; i++) w[i] = 0;
		this->b = 0;
		this->d = d;
	}
	~HyperPlane()
	{
		delete []w;
	}

    void Clear()
    {
        for (int i = 0; i < this->d; i++)
            this->w[i] = 0;
        this->b = 0;
    }

private:
	HyperPlane(const HyperPlane &obj){}
	HyperPlane& operator = (const HyperPlane &obj){}

};



/*
*   structure of the Bounding Box
*/
class BoundingBox{
public:
	double *U;
	double *L;
	int d;

	BoundingBox(int d)
	{
		this->U = new double[d];

		this->L = new double[d];
		for (int i = 0; i < d; i++) {
			U[i] = 0;
			L[i] = 0;
		}
		this->d = d;
	}
	~BoundingBox()
	{
		if (U != NULL) {
			delete[]U;
			U = NULL;
		}
		if (L != NULL) {
			delete[]L;
			L = NULL;
		}
	}
private:
	BoundingBox(const BoundingBox &obj){}
	BoundingBox & operator = (const BoundingBox & obj){}
};



/*
*   Points Set
*/
typedef vector<Point*> PointSet;
/*
*   Points List
*/
typedef list<Point*> PointList;
/*
*	Point Index
*/
typedef vector<int> PointIndex;


double Dot(double* w, double *x, int dimension);

double Dot(Point &pt1, Point &pt2, int dimension);


void PrintHyperPlane(HyperPlane &plane);

double Distance(HyperPlane &plane, Point &pt, int dimension);

double Distance(Point &pt1, Point &pt2, int dimension);

bool K_separable(PointSet &points, HyperPlane &plane, int k, int &real_k);
bool Separable(PointSet &points, HyperPlane &plane);
double Distance_Plus(HyperPlane &plane, Point &pt, int dimension);

void PrintPoints(PointSet &points, int dimension);


long long Factorial(int d);


double LogFactorial(int d);


int Choose(int n, int k);

void TransformingPoints(PointSet &points, double **T, int point_dimension);


void ScalingPoints(PointSet &points);

int Sign(double value);



PointIndex Sampling(int n, double p);
PointIndex Sampling(PointIndex &points, double p);

void PermutingPoints(PointSet &points);


bool compDown(Point *a, Point* b);

bool compUp(Point *a, Point* b);
#endif // GEOMETRY_H_INCLUDED

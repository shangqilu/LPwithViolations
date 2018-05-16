#include "geometry.h"
#include "headers.h"
#include "rand.h"
using namespace std;

double Dot(double* w, double *x, int dimension)
{
	double sum = 0;
	for (int i = 0; i < dimension; i++)
	{
		sum += (*w) * (*x);
		w++;
		x++;
	}
	return sum;
}

double Dot(Point &pt1, Point &pt2, int dimension)
{
	double sum = 0;
	for (int i = 0; i < dimension; i++)
	{
		sum += pt1.x[i] * pt2.x[i];
	}
	return sum;
}



void PrintHyperPlane(HyperPlane &plane)
{
	cout << "w: (";
	for (int i = 0; i < plane.d; i++)
	{
		cout << plane.w[i];
		if (i != plane.d - 1)
		{
			cout << ", ";
		}
	}
	cout << ") ";
	cout << "b: " << plane.b << endl;
}

double Distance(HyperPlane &plane, Point &pt, int dimension)
{
	double dis = 0, denominator = 0;
	for (int i = 0; i < dimension; i++)
	{
		dis += plane.w[i] * pt.x[i];
		denominator += plane.w[i] * plane.w[i];
	}
	dis += plane.b;
	return fabs(dis) / sqrt(denominator);
}


double Distance_Plus(HyperPlane &plane, Point &pt, int dimension)
{
	double dis = 0, denominator = 0;
	for (int i = 0; i < dimension; i++)
	{
		dis += plane.w[i] * pt.x[i];
		denominator += plane.w[i] * plane.w[i];
	}
	denominator += plane.b*plane.b;
	dis += plane.b;
	if(denominator < ZERO_ERROR) {
		PrintError("denominator is 0");
	}
	return fabs(dis) / sqrt(denominator);
}





double Distance(Point &pt1, Point &pt2, int dimension)
{
	double dis = 0;
	for (int i = 0; i < dimension; i++)
	{
		dis += (pt1.x[i] - pt2.x[i]) * (pt1.x[i] - pt2.x[i]);
	}
	return sqrt(dis);
}


bool K_separable(PointSet &points, HyperPlane &plane, int k, int &real_k)
{
	int wrong_num = 0;
	int n = points.size();
	for (int i = 0; i < n; i++) {
		if (points[i]->y * (Dot(plane.w, points[i]->x, Dim) + plane.b) <= 0) {
			wrong_num ++;
		}
	}
	if (wrong_num <= k) {
		real_k = wrong_num;
		return true;
	}else {
		real_k = wrong_num;
		return false;
	}
}


bool Separable(PointSet &points, HyperPlane &plane)
{
	int wrong_num = 0;
	int n = points.size();
	for (int i = 0; i < n; i++) {
		if (points[i]->y * (Dot(plane.w, points[i]->x, Dim) + plane.b) <= 0) {
			return false;
		}
	}
	return true;
}
void PrintPoints(PointSet &points, int dimension)
{
	for (int i = 0; i < points.size(); i++)
	{
		for (int j = 0; j < dimension; j++)
		{
			cout << points[i]->x[j] << " ";
		}
		cout << "label: " << points[i]->y;
		cout << endl;
	}
}


long long Factorial(int d)
{
	long long ans = 1;
	for (int i = 2; i <= d; i++)
	{
		ans = ans * i;
	}
	return ans;
}

double LogFactorial(int d)
{
	double ans = 0;
	for (int i = 1; i <= d; i++)
	{
		ans += log(i);
	}
	return ans;
}


int Choose(int n, int k)
{
	if (n < k) {
		PrintError("n less than k!");
	}

	int ans = 1;
	if (n - k < k) { k = n - k; }

	for (int i = 1; i <= k; i++) {
		ans = ans * (n + 1 - i) / i;
	}
	return ans;

}

void TransformingPoints(PointSet &points, double **T, int point_dimension)
{
	int n = points.size();
	double *x = new double[point_dimension + 1];
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < point_dimension + 1; j++)
		{
			x[j] = 0;
			for (int k = 0; k < point_dimension + 1; k++)
			{
				if (k < point_dimension)
					x[j] += points[i]->x[k] * T[j][k];
				else
					x[j] += T[j][k];
			}
		}
		for (int j = 0; j < point_dimension; j++)
		{
			points[i]->x[j] = x[j];
		}
	}
	delete[]x;
}


void ScalingPoints(PointSet &points)
{
	int n = points.size();
	double *max = new double[Dim];
	for (int j = 0; j < Dim; j++) max[j] = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < Dim; j++) {
			if (max[j] < fabs(points[i]->x[j])) {
				max[j] = fabs(points[i]->x[j]);
			}
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < Dim; j++) {
			points[i]->x[j] /= max[j];
		}
	}
	for (int i = 0; i < Dim; i++) cout << max[i] << " ";
	cout << endl;

	for (int j = 0; j < Dim; j++) max[j] = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < Dim; j++) {
			if (max[j] < fabs(points[i]->x[j])) {
				max[j] = fabs(points[i]->x[j]);
			}
		}
	}
	for (int i = 0; i < Dim; i++) cout << max[i] << " ";
	cout << endl;
	delete []max;
}

int Sign(double value)
{
	if (fabs(value) < ZERO_ERROR) return 0;
	if (value > 0) return 1;
	else return -1;
}


PointIndex Sampling(int n, double p)
{
	PointIndex index_points;
	if (fabs(p - 1) <= ZERO_ERROR || p >= 1) {
		index_points.resize(n);
		for (int i = 0; i < n; i++) {
			index_points[i] = i;
		}
		return index_points;
	}
	for (int i = 0; i < n; i++)
	{
		double r = uniform(0.0, 1.0);
		//printf("%d %lf\n", i, r);
		if (r < p)
		{
			index_points.push_back(i);
		}
	}
	return index_points;
}


PointIndex Sampling(PointIndex &points, double p)
{
	PointIndex index_points;
	if (fabs(p - 1) <= ZERO_ERROR || p >= 1) {
		return points;
	}
	int n = points.size();
	for (int i = 0; i < n; i++)
	{
		double r = uniform(0.0, 1.0);
		//printf("%d %lf\n", i, r);
		if (r < p)
		{
			index_points.push_back(points[i]);
		}
	}
	return index_points;

}
void PermutingPoints(PointSet &points)
{
	int n = points.size();
	for (int i = 1; i < n; i++) {
		int j = uniform_int(0, i);
		Point *tmp = points[i];
		points[i] = points[j];
		points[j] = tmp;
	}
}



bool compDown(Point *a, Point* b)
{
	return a->dis > b->dis;
}

bool compUp(Point *a, Point* b)
{
	return a->dis < b->dis;
}
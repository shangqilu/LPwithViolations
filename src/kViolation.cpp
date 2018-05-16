#include "kViolation.h"
#include "rand.h"
#include "simplex.h"
#include "headers.h"
#include "geometry.h"







/*
*	compute a separation hyperplane violating no more than (1+epsilon)*k points
*/
bool ApproximateKViolation(PointSet &points, HyperPlane &optimal_plane)
{
	puts("approximate algorithm...");
	int n = points.size();
    printf("Original Set size %d ...\n", n);
	
	double temp = 1 + Epsilon / 2;
	
    double rho;
    if (Epsilon < 0.5) {
    	rho = 12*(Dim * log(n) + log(1/Delta))/(Epsilon*Epsilon*K);
    }else {
    	rho = 8*(1+Epsilon)*(Dim * log(n) + log(1/Delta))
    							/(Epsilon*Epsilon*K);
    }

    //sampling probability
    cout << "first sample probability p: " << rho << endl;

    //in the sample set the separation plane
    //shoud violate no more than k_prime points
    int k_prime = temp * K * rho;
    //cout << "k: " << K << " k_prime: " << k_prime << endl;
    if (k_prime > K)
    {
        k_prime = K;
    }

    cout << "k: " << K << " k_prime: " << k_prime << endl;
	PointIndex subIndex = Sampling(n, rho);
    int subn = subIndex.size();
	PointSet subPoints;
	for (int i = 0; i < subn; i++) {
		subPoints.push_back(points[subIndex[i]]);
	}
	printf("n_prime: %d ...\n", subn);


	int Original_k = K;
	K = k_prime;
	bool found = KViolation(subPoints, optimal_plane);
	bool find_solution = false;
	int  violation_num = 0;
    if (found)
    {
    	//puts("find a solution in the sample set");
    	bool k_separable = K_separable(points, optimal_plane, (1+Epsilon)*Original_k, violation_num);
    	if (k_separable) {
    		find_solution = true;
    		//puts("find a solution on the Original pointset");
    	}
		
    } 
    if (find_solution) {
		puts("find a approximate k violation solution");
		printf("wrong_num: %d\n", violation_num);
		PrintHyperPlane(optimal_plane);
	}else {
		puts("approximate k violation no solution");
	}
    return find_solution;
}

/*
*	compute a separation hyperplane violating no more than k points
*/
bool KViolation(PointSet &points, HyperPlane &optimal_plane)
{
	puts("exact algorithm...");
	long long times = 0;
	if (Dim < K){
		times = (long long)(pow(K, Dim) * exp(Dim)
						/ pow(1.0*Dim, Dim) * log(1 / Delta));
	}else {
		times = (long long)(pow(K, Dim) * log(1 / Delta));
	}

	int n = points.size();
	bool find_solution = false;
	if (K == 0) times = 1;
	
	if (times <= 0) {
		times = 10000;
	}

	int violation_num = 0;
	printf("max repeating times %lld\n", times);
	for (int curtime = 0; curtime < times; curtime++){
		printf("Current repeating time: %d\n", curtime);
		double p;
		if (Dim < K) {
			p = 1.0 * Dim / K;
		}else {
			p = 1.0 / K;
		}
		PointIndex subIndex = Sampling(n, p);
		int subn = subIndex.size();
		PointSet subPoints;
		for (int i = 0; i < subn; i++) {
			subPoints.push_back(points[subIndex[i]]);
		}

		printf("Sub Set size %d ...\n", subn);
		if (subn < 2) {
			continue;
		}
        HyperPlane plane(Dim);

        /*find a solution on the sampling subset*/
        //PrintPoints(subPoints, Dim);
        bool found = LPMarginclassification(subPoints, plane);

        if(found) {
        	puts("separable in the subset");
        	int largest_k;
        	bool k_separable = K_separable(points, plane, K, violation_num);
        	if (k_separable) {
        		for (int i = 0; i < plane.d; i++)
				{
					optimal_plane.w[i] = plane.w[i];
				}
				optimal_plane.b = plane.b;
				find_solution = true;
        		break;
        	}else {
        		printf("cur real_K: %d\n", violation_num);
        	}
        	
        }
	}

	if (find_solution) {
		puts("find a k violation solution");
		printf("wrong_num: %d\n", violation_num);
		PrintHyperPlane(optimal_plane);
	}else {
		puts("k violation no solution");
	}
	

	return find_solution;
}



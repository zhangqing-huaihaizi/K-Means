#ifndef KMEANS_H  
#define KMEANS_H  
#include <stdlib.h>  
#include <stdio.h>  
#include <math.h>  
#include <time.h>  
#include <vector>  
#include <fstream>  
#include <iostream>  
using namespace std;  
#include "KmPoint.h"  
#define PI 3.14159265358979323846  

template<typename Real = double, int Dim = 2>  
class KMeans{  
public:  
	typedef KmPoint<Real, Dim> KmPoint;  
public:  
	KMeans(){ srand((unsigned)time(0)); }  
	Real randf(Real m){  
		return m * rand() / (RAND_MAX - 1.);  
	}  

	Real dist(KmPoint &a, KmPoint &b){  
		Real len = 0;  
		for(int i = 0; i < Dim; ++i){  
			len += (a[i] - b[i]) * (a[i] - b[i]);  
		}  
		return len;  
	}  

	void dataGenerator(int count, Real radius, vector<KmPoint> &pts);  
	int nearest(KmPoint &pt, vector<KmPoint> &cents, Real &d);  
	void kpp(vector<KmPoint> &pts, vector<KmPoint> &cents);  
	void kmcluster(vector<KmPoint> &pts, int k, vector<KmPoint> &outCents, vector<vector<KmPoint>> &outPts);  
	void serialize(vector<vector<KmPoint>> &outPts);  
};  

#endif  
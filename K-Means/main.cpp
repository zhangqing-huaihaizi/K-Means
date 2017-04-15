#include "KMeans.cpp"
int main(){  
	KMeans<> km;  
	vector<KmPoint<>> pts, outCents;  
	int k = 7;  
	vector<vector<KmPoint<>>> outPts;  
	km.dataGenerator(10000, 10, pts);  
	km.kmcluster(pts, k, outCents, outPts);  
	km.serialize(outPts);  
	return 0;  
}  
#include "Kmeans.h"  

template<typename Real, int Dim>  
void KMeans<Real, Dim>::dataGenerator(int count, Real radius, vector<KmPoint> &pts){  
	if(pts.size() <= 0)  
		pts.resize(count);  
	for(int i = 0; i < count; ++i){  
		Real ang = randf(2 * PI);  
		Real r = randf(radius);  
		KmPoint p;  
		p[0] = r * cos((Real)ang);  
		p[1] = r * sin((Real)ang);  
		pts[i] = p;  
	}  
}  

template<typename Real, int Dim>  
int KMeans<Real, Dim>::nearest(KmPoint &pt, vector<KmPoint> &cents, Real &d){  
	int i, min_i;  
	Real d1, min_d;  
	min_d = HUGE_VAL;  
	min_i = pt.id();  
	for(i = 0; i < (int)cents.size(); ++i){  
		KmPoint c = cents[i];  
		if(min_d > (d1 = dist(c, pt))){  
			min_d = d1;  
			min_i = i;  
		}  
	}  
	d = min_d;  
	return min_i;  
}  

//d数组存放所有点到每一个聚类中心的最近距离
//所有最近距离的和为sum
template<typename Real, int Dim>  
void KMeans<Real, Dim>::kpp(vector<KmPoint> &pts, vector<KmPoint> &cents){  
	Real sum = 0;  
	vector<Real> d;  
	d.resize(pts.size());  
	cents[0] = pts[rand() % pts.size()];  
	vector<KmPoint> tmpCents;  
	tmpCents.push_back(cents[0]);  
	for(int k = 1; k < (int)cents.size(); ++k){  
		sum = 0;  
		for(int i = 0; i < (int)pts.size(); ++i){  
			nearest(pts[i], tmpCents, d[i]);  
			sum += d[i];  
		}  
		sum = randf(sum);  
		for(int i = 0; i < (int)pts.size(); ++i){  
			if((sum -= d[i]) > 0)    continue;  
			cents[k] = pts[i];  
			tmpCents.push_back(cents[k]);  
			break;  
		}  
	}  
	for(int i = 0; i < (int)pts.size(); ++i){  
		int id = nearest(pts[i], cents, *(new Real));  
		pts[i].setId(id);  
	}  
}  

template<typename Real, int Dim>  
void KMeans<Real, Dim>::kmcluster(vector<KmPoint> &pts, int k, vector<KmPoint> &outCents, vector<vector<KmPoint>> &outPts){  
	if(outCents.size() <= 0)  
		outCents.resize(k);  
	if(outPts.size() <= 0)  
		outPts.resize(k);  
	kpp(pts, outCents);  
	int changed;  
	do{  
		for(int i = 0; i < (int)outCents.size(); ++i){  
			for(int j = 0; j < Dim; ++j)  
				outCents[i][j] = 0;  
			outCents[i].setId(0);  
		}  
		vector<int> cnt(k, 0);  
		for(int i = 0; i < (int)pts.size(); ++i){  
			int k = pts[i].id();  
			for(int j = 0; j < Dim; ++j)  
				outCents[k][j] += pts[i][j];  
			cnt[k]++;  
		}  
		for(int i = 0; i < (int)outCents.size(); ++i){  
			for(int j = 0; j < Dim; ++j)  
				outCents[i][j] /= cnt[i];  
		}  
		changed = 0;  
		for(int i = 0; i < (int)pts.size(); ++i){  
			int min_i = nearest(pts[i], outCents, *(new Real));  
			if(min_i != pts[i].id()){  
				changed++;  
				pts[i].setId(min_i);  
			}  
		}  
	}while(changed > 0.001 * pts.size());  
	for(int i = 0; i < (int)outCents.size(); ++i)  
		outCents[i].setId(i);  
	for(int i = 0; i < (int)pts.size(); ++i)  
		outPts[pts[i].id()].push_back(pts[i]);  
}  

template<typename Real, int Dim>  
void KMeans<Real, Dim>::serialize(vector<vector<KmPoint>> &outPts){  
	ofstream ofs("./cluster.txt", ofstream::out);  
	if(!ofs.is_open()){  
		cout<<"open file failed!"<<endl;  
		return ;  
	}  
	for(int i = 0; i < (int)outPts.size(); ++i){  
		for(int j = 0; j < (int)outPts[i].size(); ++j){  
			ofs<<outPts[i][j]<<endl;  
		}  
	}  
	ofs.close();  
} 
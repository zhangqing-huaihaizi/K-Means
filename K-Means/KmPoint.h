#ifndef KMPOINT_H  
#define KMPOINT_H  

template<typename Real = double, int Dim = 2>  
struct KmPoint{  
public:  
	typedef KmPoint<Real, Dim> Self;  

	KmPoint(){  
		for(int i = 0; i < Dim; ++i){  
			x[i] = 0;  
		}  
		gid = 0;  
	}  

	KmPoint(Real (&x)[Dim], int gid = -1){  
		for(int i = 0; i < Dim; ++i){  
			this->x[i] = x[i];  
		}  
		this->gid = gid;  
	}  

	KmPoint(const Self &other){  
		for(int i = 0; i < Dim; ++i){  
			x[i] = other[i];  
		}  
		gid = other.gid;  
	}  

	Real &operator[](int idx){  return x[idx];  }  
	const Real &operator[](int idx) const { return x[idx]; }  

	int id(){ return gid; }  
	void setId(int id){  
		gid = id;  
	}  

	Real get(int idx){ return x[idx]; }  
private:  
	Real x[Dim];  
	int gid;  
};  

template<class Real, int Dim>  
ostream& operator<<(ostream &out, KmPoint<Real, Dim> &other){  
	out<<other[0];  
	for(int i = 1; i < Dim; ++i)  
		out<<" "<<other[i];  
	out<<" "<<other.id();  
	return out;  
}  

#endif  
#include"matrix.hpp"
#include <random>
#include<string>
#include<algorithm>
#include<cmath>
#include<iostream>
#include<iomanip>
#include<sstream>
#include"functions.hpp"
#define SELF (*this)
#define FORV(i,v) for(int i=0;i<v.size();i++)
#define FOR_COLS(i,A) for(int i=0;i<A.size2();i++)
namespace pp{

// bool approx(NUMBER x,NUMBER y,NUMBER acc=1e-6,NUMBER eps=1e-6){
// 	if(std::fabs(x-y) < acc)return true;
// 	if(std::fabs(x-y) < eps*(std::fabs(x)+std::fabs(y)))return true;
// 	return false;
// }

bool approx(const vector& u,const vector& v,NUMBER acc,NUMBER eps){
	if(u.size()!=v.size())return false;
	for(int i=0;i<u.size();i++)if(!approx(u[i],v[i],acc,eps))return false;
	return true;
}

vector& vector::operator+=(const vector& other) {
	FORV(i,SELF) data[i]+=other.data[i];
	return SELF; }

vector& vector::operator-=(const vector& other) {
	FORV(i,SELF) data[i]-=other.data[i];
	return SELF; }

vector& vector::operator*=(NUMBER x) {
	FORV(i,SELF) data[i]*=x;
	return SELF; }

vector& vector::operator/=(NUMBER x) {
	FORV(i,SELF) data[i]/=x;
	return SELF; }
	
bool vector::operator==(const vector& vec) const
{
	if(vec.size() != size()) {
		return false;
	}
	for (int i =0; i < size(); i++) {
		if(!pp::approx(data[i], vec[i])) return false;
	}
	return true;
}

	
NUMBER vector::norm() const
{
	NUMBER sum = 0;
	for (int i = 0; i < size(); ++i) {
		sum += data[i] * data[i];
	}
	return std::sqrt(sum);
}

NUMBER vector::dot(const vector& v) const
{
	if (size() != v.size()) 
		{
			throw std::invalid_argument("Vectors must be of the same size");
		}
		NUMBER sum = 0;
		for (int i = 0; i< size(); i++)
		{
			sum += data[i]*v.data[i];
		}
	return sum;
}



void vector::print(std::string s,FILE* stream) const {
	fprintf(stream,"%s\n",s.c_str());
	FORV(i,SELF)fprintf(stream,"%9.4g ",(double)SELF[i]);
	fprintf(stream,"\n");
	}

vector operator/(const vector& v, NUMBER x){
	vector r=v;
	r/=x;
	return r; }

vector operator*(const vector& v, NUMBER x){
	vector r=v;
	r*=x;
	return r; }

vector operator*(NUMBER x,const vector& a){ return a*x; }

vector operator+(const vector& a, const vector& b){
	vector r=a;
	r+=b;
	return r; }

vector operator-(const vector& a, const vector& b){
	vector r=a;
	r-=b;
	return r; }

vector operator-(const vector& a){
	vector r=a*(-1);
	return r; }


void matrix::resize(int n, int m){
	cols.resize(m);
	for(int i=0;i<m;++i)cols[i].resize(n);
	}

matrix matrix::transpose() {
    // matrix R; R.resize(size2(),size1());
	matrix R(size2(), size1());
    for (int j = 0; j < R.size2(); ++j)
    	for (int i = 0; i < R.size1(); ++i)
            R[i, j] = SELF[j, i];
    return R;
        }

matrix& matrix::operator+=(const matrix& other) {
	FOR_COLS(i,SELF) SELF[i]+=other[i];
	return SELF; }

matrix& matrix::operator-=(const matrix& other) {
	FOR_COLS(i,SELF) SELF[i]-=other[i];
	return SELF; }

matrix& matrix::operator*=(NUMBER x) {
	FOR_COLS(i,SELF) SELF[i]*=x;
	return SELF; }

matrix& matrix::operator/=(NUMBER x) {
	FOR_COLS(i,SELF) SELF[i]/=x;
	return SELF; }
	
bool matrix::operator==(const matrix& mat) const
{
	if (mat.size2() != size2() || mat.size1() != size1())
		return false;
for (int i = 0; i < size2(); ++i) {
	for (int j = 0; j < size1(); ++j) {
		if (!pp::approx(mat[j,i], SELF[j,i])) {
			return false;
		}
	}
}
return true;
}

matrix matrix::identity(int n) {
    matrix mat(n, n);
    for (int j = 0; j < n; ++j) {
        mat.cols[j][j] = 1.0;
    }
    return mat;
}

matrix matrix::rndMatrix(int n, int m, NUMBER min, NUMBER max)
{
	std::random_device rd;  // Seed for the random number generator
    std::mt19937 gen(rd()); // Mersenne Twister engine
    std::uniform_real_distribution<NUMBER> dist(min, max); // Uniform distribution
	matrix tmp(n,m);
    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < m; ++i) {
            tmp[j, i] = dist(gen); // Assign a random value to each element
        }
    }
	return tmp;
}

matrix matrix::rndSymMatrix(int n, NUMBER min, NUMBER max)
{
	std::random_device rd;  // Seed for the random number generator
    std::mt19937 gen(rd()); // Mersenne Twister engine
    std::uniform_real_distribution<NUMBER> dist(min, max); // Uniform distribution
	matrix tmp(n,n);
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; j++) {
			NUMBER val = dist(gen);
            tmp[j, i] = val; // Assign a random value to each element
			tmp[i, j] = val; // Assign a random value to each element
        }
    }
	return tmp;
}



void matrix::setDiagonal(NUMBER value, int offset) {
    int m = size1();
    int n = size2();
    for (int i = 0; i < m; ++i) {
        int j = i + offset;
        if (j >= 0 && j < n) {
            cols[j][i] = value;
        }
    }
}

bool matrix::lowerTriangular() const
{
for (int i = 0; i < std::min(size1(), size2()); i++) {
	for (int j = i + 1; j < size1(); j++) {  // Only check above the diagonal (i, j)
		if (!pp::approx(SELF[i, j], 0.0)) {
			return false;  // Found a nonzero element above the diagonal
		}
	}
}
return true;	
}

bool matrix::upperTriangular() const
{
for (int i = 1; i < size2(); i++) {  // Start from row 1, since this makes sense.
	for (int j = 0; j < std::min(i, size1()); j++) {  // Only check below the diagonal (i, j)
		if (!pp::approx(SELF[i, j], 0.0)) {
			return false;  // Found a nonzero element below the diagonal
		}
	}
}
return true;
}

matrix operator/(const matrix& A,NUMBER x){
	matrix R=A;
	R/=x;
	return R; }

matrix operator*(const matrix& A,NUMBER x){
	matrix R=A;
	R*=x;
	return R; }

matrix operator*(NUMBER x,const matrix& A){
	return A*x; }

matrix operator+(const matrix& A, const matrix& B){
	matrix R=A;
	R+=B;
	return R; }

matrix operator-(const matrix& A, const matrix& B){
	matrix R=A;
	R-=B;
	return R; }

vector operator*(const matrix& M, const vector& v){
	vector r; r.resize(M.size1());
	for(int i=0;i<r.size();i++){
		NUMBER sum=0;
		for(int j=0;j<v.size();j++)sum+=M[i,j]*v[j];
		r[i]=sum;
		}
	return r;
}

matrix operator*(const matrix &A, const matrix &B) {
  matrix R(A.size1(), B.size2());
  for (int k = 0; k < A.size2(); k++)
    for (int j = 0; j < B.size2(); j++) {
      for (int i = 0; i < A.size1(); i++)
        R[i, j] += A[i, k] * B[k, j];
    }
  return R;
}
/*
vector matrix::get_col(int j){
        vector cj=SELF[j];
        return cj;
        }

void matrix::set_col(int j,vector& cj){
        SELF[i]=cj;
        }
*/

void matrix::print(std::string s,FILE* stream){
	fprintf(stream,"%s\n",s.c_str());
	for(int i=0;i<size1();i++){
		for(int j=0;j<size2();j++)fprintf(stream,"%9.4g ",(double)SELF[i,j]);
		fprintf(stream,"\n");
		}
	}

std::ostream& operator<<(std::ostream& os, const matrix& mat) {
    std::ostringstream buffer; // costly i/o calls so use large buffer.
	for (int i = 0; i < mat.size1(); ++i) {
        for (int j = 0; j < mat.size2(); ++j) {
            buffer << std::setprecision(4) << mat[i, j] << " ";
        }
        buffer << "\n";
    }
    return os << buffer.str();
}

std::ostream& operator<<(std::ostream& os, const vector& obj)
{
	std::ostringstream buffer;
	int length = obj.size();
	for (int i = 0; i < length - 1; i++) {
		buffer << std::setprecision(4) << obj[i] << " ";
	}
	buffer << std::setprecision(4) << obj[length-1];
	//buffer << "\n";
	return os << buffer.str();
}

}//pp
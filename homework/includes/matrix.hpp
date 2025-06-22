#ifndef HAVE_MATRIX_H
#define HAVE_MATRIX_H
#ifdef LONG_DOUBLE
	#define NUMBER long double
#else
	#define NUMBER double
#endif
#include<string>
#include<vector>
namespace pp{
struct vector {
	std::vector<NUMBER> data;
	vector(int n) : data(n) {}
	vector()			=default;
	vector(const vector&)		=default;
	vector(vector&&)		=default;
	vector& operator=(const vector&)=default;
	vector& operator=(vector&&)	=default;
	void push_back(const NUMBER n) {data.push_back(n);}
	int size() const {return data.size();}
	void resize(int n) {data.resize(n);}
	NUMBER& operator[](int i) {return data[i];}
	// iterator implementation
    const auto begin() const { return data.begin(); } // first element
    const auto end() const { return data.end(); } // one past last element per convention.
	auto begin() { return data.begin(); } // first element
    auto end() { return data.end(); } // one past last element per convention.
	const NUMBER& operator[](int i) const {return data[i];}
	vector& operator+=(const vector&);
	vector& operator-=(const vector&);
	vector& operator*=(NUMBER);
	vector& operator/=(NUMBER);
	bool operator==(const vector& vec) const;
	NUMBER norm() const; 
	NUMBER dot(const vector& v) const;
	void print(std::string s="",FILE* stream=stdout) const;
};

vector operator+(const vector&, const vector&);
vector operator-(const vector&, const vector&);
vector operator-(const vector&);
vector operator*(const vector&, NUMBER);
vector operator*(NUMBER, const vector&);
vector operator/(const vector&, NUMBER);
bool approx(const vector&, const vector&, NUMBER acc=1e-6, NUMBER eps=1e-6);

struct matrix {
	std::vector<vector> cols;
	matrix()=default;
	matrix(int n,int m) : cols(m, vector(n)) {}
	matrix(const matrix& other)=default;
	matrix(matrix&& other)=default;
	matrix& operator=(const matrix& other)=default;
	matrix& operator=(matrix&& other)=default;
	int size1() const {return cols.empty() ? 0 : cols[0].size(); } // rows
	int size2() const {return cols.size();} // cols
	void resize(int n, int m);
	
	NUMBER get (int i, int j) {return cols[j][i];}
	void set(int i, int j, NUMBER value){cols[j][i] = value;}
	NUMBER& operator()(int i, int j){return cols[j][i];}
	NUMBER& operator[](int i, int j){return cols[j][i];}
	const NUMBER& operator[](int i, int j) const {return cols[j][i];}
	vector& operator[](int i){return cols[i];}
	const vector& operator[](int i) const {return cols[i];}
	// Iterators
    auto begin() { return cols.begin()->begin(); }
    auto end() { return cols.back().end(); }
    const auto begin() const { return cols.begin()->begin(); }
    const auto end() const { return cols.back().end(); }
//	vector get_col(int j);
//	void set_col(int j,vector& cj);
	matrix transpose();
	static matrix identity(int n);
	static matrix rndMatrix(int n, int m, NUMBER min = 0.0, NUMBER max = 10.0);
	static matrix rndSymMatrix(int n, NUMBER min = 0.0, NUMBER max = 10.0);
	void setDiagonal(NUMBER value, int offset = 0);
	bool lowerTriangular() const;
	bool upperTriangular() const;

	matrix& operator+=(const matrix&);
	matrix& operator-=(const matrix&);
	matrix& operator*=(const matrix&);
	matrix& operator*=(const NUMBER);
	matrix& operator/=(const NUMBER);
	matrix  operator^(int);
	bool operator==(const matrix& mat) const;

	//void print(const char* s="");
	void print(std::string s="",FILE* stream=stdout);

};

std::ostream& operator<<(std::ostream& os, const matrix& obj);
std::ostream& operator<<(std::ostream& os, const vector& obj);
matrix operator+(const matrix&, const matrix&);
matrix operator-(const matrix&, const matrix&);
matrix operator*(const matrix&, const matrix&);
matrix operator*(const matrix&, NUMBER);
matrix operator*(NUMBER, const matrix&);
matrix operator/(const matrix&, NUMBER);
vector operator*(const matrix&, const vector&);
}
#endif
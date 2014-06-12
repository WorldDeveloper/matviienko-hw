#pragma once
#include <ostream>
using namespace std;

class Matrix
{
	int** mValue;
	int mVSize;
	int mHSize;
public:
	Matrix() : mValue(nullptr), mVSize(0), mHSize(0){}
	Matrix(const int m, const int n);
	~Matrix();
	void CreateMatrix(const int m, const int n);
	void DeleteMatrix();
	
	Matrix(const Matrix &source);
	Matrix& operator=(const Matrix& result);

	int &operator()(const int m, const int n) const;
	Matrix operator+(const Matrix& operand2);
	Matrix& operator++();
	Matrix operator*(const Matrix& operand2);

	int GetVSize() const { return mVSize; }
	int GetHSize() const { return mHSize; }

	friend ostream &operator<<(ostream &stream, const Matrix &output);
};


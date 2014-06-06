#pragma once
#include <ostream>
using namespace std;

class Matrix
{
	int** mValue;
	int mVSize;
	int mHSize;
public:
	Matrix() : mValue{ nullptr }, mVSize{ 0 }, mHSize{ 0 }{}
	Matrix(const int m, const int n);
	~Matrix();
	void CreateMatrix(const int m, const int n);
	void DeleteMatrix();
	
	Matrix(Matrix &source);
	Matrix operator=(const Matrix result);

	int &operator()(int m, int n);
	Matrix operator+(Matrix operand2);
	Matrix operator++();
	Matrix operator*(Matrix operand2);

	int GetVSize(){ return mVSize; }
	int GetHSize(){ return mHSize; }

	friend ostream &operator<<(ostream &stream, Matrix &output);
};


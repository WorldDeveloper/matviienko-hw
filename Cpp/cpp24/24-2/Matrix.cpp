#include "Matrix.h"
#include <new>
using namespace std;


void Matrix::CreateMatrix(const int m, const int n)
{
	mVSize = m;
	mHSize = n;

	try
	{
		mValue = new int*[m];

		for (int i = 0; i < m; i++)
		{
			mValue[i] = new int[n];
		}

		for (int i = 0; i < m; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				mValue[i][j] = 0;
			}
		}
	}
	catch (bad_alloc)
	{
		exit(1);
	}
}

Matrix::Matrix(const int m, const int n)
{
	CreateMatrix(m, n);
}

int &Matrix::operator()(int i, int j)
{
	if (i >= 0 && i < mVSize && j >= 0 && j < mHSize)
	{
		return mValue[i][j];
	}
	else
	{
		exit(1);
	}
}
void Matrix::DeleteMatrix()
{
	if (mValue)
	{
		for (int i = 0; i < mVSize; i++)
		{
			delete[] mValue[i];
		}
		delete[] mValue;
	}
}

Matrix::~Matrix()
{
	DeleteMatrix();
}


Matrix Matrix::operator=(Matrix result)
{
	if (mVSize != result.mVSize && mHSize != result.mHSize)
	{
		DeleteMatrix();
		CreateMatrix(result.mVSize, result.mHSize);
	}
	for (int i = 0; i < mVSize; ++i)
	{
		for (int j = 0; j < mHSize; ++j)
		{
			mValue[i][j] = result.mValue[i][j];
		}
	}
	return *this;
}


Matrix::Matrix(Matrix &source)
{
	CreateMatrix(source.mVSize, source.mHSize);
	for (int i = 0; i < mVSize; ++i)
	{
		for (int j = 0; j < mHSize; ++j)
		{
			mValue[i][j] = source.mValue[i][j];
		}
	}
}

Matrix Matrix::operator+(Matrix operand2)
{
	if (mVSize != operand2.mVSize || mHSize != operand2.mHSize)
	{
		exit(1);
	}

	Matrix tmp(mVSize, mHSize);
	for (int i = 0; i < mVSize; ++i)
	{
		for (int j = 0; j < mHSize; ++j)
		{
			tmp.mValue[i][j] = mValue[i][j] + operand2.mValue[i][j];
		}
	}
	return tmp;

}

Matrix Matrix::operator++()
{
	Matrix transp(mHSize, mVSize);
	for (int i = 0; i < mVSize; ++i)
	{
		for (int j = 0; j < mHSize; ++j)
		{
			transp.mValue[j][i] = mValue[i][j];
		}
	}
	DeleteMatrix();
	CreateMatrix(transp.mVSize, transp.mHSize);
	*this = transp;
	return *this;
}

Matrix Matrix::operator*(Matrix operand2)
{
	if (mVSize != operand2.mHSize || mHSize != operand2.mVSize)
	{
		exit(1);
	}
	
	Matrix tmp(mVSize, operand2.mHSize);
	for (int k = 0; k < tmp.mHSize; ++k)
	{
		for (int i = 0; i < mVSize; ++i)
		{
			for (int j = 0; j < mHSize; ++j)
			{
				tmp.mValue[i][k] += mValue[i][j] * operand2.mValue[j][k];
			}
		}
	}
	return tmp;
}
#include <iostream>
using namespace std;

class Point{
	int mX;
	int mY;
public:
	Point(const int x, const int y) : mX(x), mY(y){}
	void SetPoint(int x, int y)
	{
		mX = x;
		mY = y;
	}
	void ShowPoint() const
	{
		cout << "(" << mX << ", " << mY << ")";
	}
};
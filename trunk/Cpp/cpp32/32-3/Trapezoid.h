#include "Figure.h"

class Trapezoid : public Figure
{
	float mSideA;
	float mSideB;
	float mHeight;
public:
	Trapezoid(const float sideA, const float sideB, const float height)
		: Figure("Trapezoid"), mSideA(sideA), mSideB(sideB), mHeight(height){}
	virtual ~Trapezoid(){}
	virtual float GetArea() const
	{
		return (mSideA + mSideB)*mHeight / 2;
	}
};
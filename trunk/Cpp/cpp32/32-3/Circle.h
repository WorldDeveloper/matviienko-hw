#include "Figure.h"

class Circle : public Figure
{
	float mRadius;
	const float mPi;
public:
	Circle(const float radius)
		: Figure("Circle"), mRadius(radius), mPi(3.14){}
	virtual ~Circle(){}
	virtual float GetArea() const
	{
		return mPi*mRadius*mRadius;
	}
};
#include "Figure.h"

class RightTriangle : public Figure
{
	float mBase;
	float mHeight;
public:
	RightTriangle(const float base, const float height)
		: Figure("Right Triangle"), mBase(base), mHeight(height){}
	virtual ~RightTriangle(){}
	virtual float GetArea() const
	{
		return 0.5*mBase*mHeight;
	}
};
#include "Figure.h"

class Rectangle : public Figure
{
	float mWidth;
	float mHeight;
public:
	Rectangle(const float width, const float height)
		: Figure("Rectangle"), mWidth(width), mHeight(height){}
	virtual ~Rectangle(){}
	virtual float GetArea() const
	{
		return mWidth*mHeight;
	}
};
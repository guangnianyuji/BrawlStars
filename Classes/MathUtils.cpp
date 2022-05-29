#include "MathUtils.h"
#include"cocos2d.h"
using namespace cocos2d;

Point MathUtils::PolarToRectangular(float Radius, float Rad)
{
	return(Point(Radius * cos(Rad), Radius * sin(Rad)));
}

float MathUtils::getRad(const Vec2& StartPoint, const Vec2& EndPoint)
{
	auto Delta = EndPoint - StartPoint;
	auto Distance = StartPoint.distance(EndPoint);
	auto CosRad = Delta.x / Distance;
	auto Rad = acos(CosRad);
	if (StartPoint.y > EndPoint.y)
	{
		Rad = - Rad;
	}
	return Rad;
}

 Vec2 MathUtils::getVectorialSpeed(float Rad, float Speed)
{
	return Vec2(cos(Rad) * Speed, sin(Rad) * Speed);
}

 bool MathUtils::isTouchEffective(const Vec2& TouchPoint, const Vec2& centre, const float radius)
 {
	 if (centre.distance(TouchPoint) > radius)
		 return false;
	 else
		 return true;
 }

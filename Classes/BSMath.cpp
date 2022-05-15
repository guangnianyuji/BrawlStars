#include "BSMath.h"
#include"cocos2d.h"
using namespace cocos2d;

Point BSMath::PolarToRectangular(float Radius, float Rad)
{
	return(Point(Radius * cos(Rad), Radius * sin(Rad)));
}

float BSMath::getRad(const Vec2& StartPoint, const Vec2& EndPoint)
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

 Vec2 BSMath::getVectorialSpeed(float Rad, float Speed)
{
	return Vec2(cos(Rad) * Speed, sin(Rad) * Speed);
}
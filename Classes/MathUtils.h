#ifndef __MATHUTILS_H__
#define __MATHUTILS_H__
#define Pi 3.14159265358979323846

#include"cocos2d.h"
using namespace cocos2d;

class MathUtils
{
public:
	//极坐标变为直角坐标
	static Point PolarToRectangular(float Radius, float Rad);
	//得到弧度大小
	static float getRad(const Vec2& StartPoint, const Vec2& EndPoint);
	//得到速度的矢量式
	static Vec2 getVectorialSpeed(float Rad, float Speed);
};

#endif //__MATH_H__

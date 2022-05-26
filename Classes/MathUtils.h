#ifndef __MATHUTILS_H__
#define __MATHUTILS_H__
#define Pi 3.14159265358979323846

#include"cocos2d.h"
using namespace cocos2d;

class MathUtils
{
public:
	//�������Ϊֱ������
	static Point PolarToRectangular(float Radius, float Rad);
	//�õ����ȴ�С
	static float getRad(const Vec2& StartPoint, const Vec2& EndPoint);
	//�õ��ٶȵ�ʸ��ʽ
	static Vec2 getVectorialSpeed(float Rad, float Speed);
};

#endif //__MATH_H__
#ifndef __ANIMATIONUTILS_H__
#define __ANIMATIONUTILS_H__

#include "cocos2d.h"

using namespace cocos2d;

class AnimationUtils
{
public:

	/* ������ɫ��������ʱ�Ķ��� */
	static Animate* createAnimation(const std::string& name, const std::string& direction);

	/* ������ͨ�������� */
	static Animate* createNormalAttackAnimation(const std::string& name);

	/* ������ɫ���ڷǹ���״̬�µļ��ܶ��� */
	static Animate* createSkillAnimation(const std::string& name);
};

#endif

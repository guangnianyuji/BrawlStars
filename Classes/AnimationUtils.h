#ifndef __ANIMATIONUTILS_H__
#define __ANIMATIONUTILS_H__

#include "cocos2d.h"

using namespace cocos2d;

class AnimationUtils
{
public:

	/* 创建角色四向行走时的动画 */
	static Animate* createAnimation(const std::string& name, const std::string& direction);

	/* 创建普通攻击动画 */
	static Animate* createNormalAttackAnimation(const std::string& name,const int loops);

	static Animate* createACEAnimation(const std::string& name,int loops);
};

#endif

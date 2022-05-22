#ifndef __ANIMATIONUTILS_H__
#define __ANIMATIONUTILS_H__

#include "cocos2d.h"

using namespace cocos2d;

class AnimationUtils
{
public:
	static Animate* createAnimation(const std::string& name, const std::string& direction);
};

#endif

#ifndef __CHARACTER_H__
#define __CHARACTER_H__

#include "cocos2d.h"
#include "AnimationUtils.h"

USING_NS_CC;

class Character
{
public:

	Sprite* m_FrontBody;
	Sprite* m_BehindBody;
	Sprite* m_LeftBody;
	Sprite* m_RightBody;
public:
	Animate* m_FrontMove;
	Animate* m_BehindMove;
	Animate* m_LeftMove;
	Animate* m_RightMove;
};


#endif

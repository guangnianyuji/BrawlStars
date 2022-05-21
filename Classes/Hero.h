#ifndef __HERO_H__
#define __HERO_H__

#include "cocos2d.h"
#include "Entity.h"
#include "MathUtils.h"
#include "Character.h"

using namespace cocos2d;

class Hero :public Entity
{
public:
	bool init() override;
protected:
	//Ӣ�۵Ľ�ɫ
	Character m_Character;

	Sprite* m_Body;
	//Ӣ���Ƿ������ƶ�
	bool m_isMoving;

	void onEnter() override;
public:
	//��������
	void setAnimation(const float& Angle);
	//ֹͣ��������
	void stopAnimation();
};

#endif

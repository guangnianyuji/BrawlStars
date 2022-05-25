#ifndef __ATTACK_LAYER__
#define __ATTACK_LAYER__

#include "cocos2d.h"

class AttackLayer:public cocos2d::Layer
{
public:
	static AttackLayer* create(cocos2d::Vec2 position1,cocos2d::Vec2 position2);

	virtual bool init() override;

	void initNormalAttackButton();

	void initAceButton();

	void setButtonDisable(); 

	void setButtonEnable();

	inline const bool& isAttacking() { return _isAttacking; }

	//CREATE_FUNC(AttackLayer);

private:

	cocos2d::EventListenerTouchOneByOne* TouchListener;

	cocos2d::EventListenerKeyboard* KeyboardListener;


	cocos2d::Vec2 normalAttackButtonPosition;

	cocos2d::Vec2 aceButtonPosition;

	cocos2d::Sprite* normalAttackButton_Normal;

	cocos2d::Sprite* normalAttackButton_Pressed;

	cocos2d::Menu* aceButton;

	bool _isAttacking = false;
};
#endif

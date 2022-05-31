#ifndef __ATTACK_LAYER__
#define __ATTACK_LAYER__

#include "cocos2d.h"


class AttackLayer:public cocos2d::Layer
{
	friend class FightControllerLayer;
public:
	static AttackLayer* create(cocos2d::Vec2 position1,cocos2d::Vec2 position2);

	virtual bool init() override;

	/* 设置技能摇杆为可用状态 */
	void setRockerDisable(); 

	/* 设置技能摇杆为不可用状态 */
	void setRockerEnable();

	/* 判断人物是否在进行普通攻击 */
	inline const bool isAttackTime() { return _isAttackTime; }

	/* 判断人物是否在放大招 */
	inline const bool isAceTime() { return _isAceTime; }

	inline void setAttackState(bool State) { _isAttackTime = State; }

	/* 得到普攻摇杆方向角 */
	inline const float getNormalRockerAngle() { return normalAttackRockerAngle; }

	/* 得到绝招摇杆方向角 */
	inline const float getAceRockerAngle() { return aceRockerAngle; }

private:

	/* 加入普通攻击摇杆 */
	void initNormalAttackRocker();

	/* 加入绝招摇杆 */
	void initAceRocker();

	cocos2d::Vec2 normalAttackRockerBGPosition;

	cocos2d::Vec2 normalAttackRockerPosition;

	cocos2d::Vec2 aceRockerBGPosition;

	cocos2d::Vec2 aceRockerPosition;

	cocos2d::Sprite* normalAttackRockerBG;

	cocos2d::Sprite* normalAttackRocker;

	cocos2d::Sprite*  aceRockerBG;

	cocos2d::Sprite* aceRocker;

	/* 摇杆的半径 */
	float RockerBackgroundRadius;

	/* 松开摇杆前普通攻击摇杆的方向角 */
	float normalAttackRockerAngle;

	/* 松开摇杆前绝招摇杆的方向角 */
	float aceRockerAngle;


	bool _isAttackTime = false;

	bool _isAceTime = false;
};
#endif

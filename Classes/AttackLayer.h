#ifndef __ATTACK_LAYER__
#define __ATTACK_LAYER__

#include "cocos2d.h"


class AttackLayer:public cocos2d::Layer
{
	friend class FightControllerLayer;
public:
	static AttackLayer* create(cocos2d::Vec2 position1,cocos2d::Vec2 position2);

	virtual bool init() override;

	/* ���ü���ҡ��Ϊ����״̬ */
	void setRockerDisable(); 

	/* ���ü���ҡ��Ϊ������״̬ */
	void setRockerEnable();

	/* �ж������Ƿ��ڽ�����ͨ���� */
	inline const bool isAttacking() { return _isAttacking; }

	/* �ж������Ƿ��ڷŴ��� */
	inline const bool isAceTime() { return _isAceTime; }

	/* �õ��չ�ҡ�˷���� */
	inline const float getNormalRockerAngle() { return normalAttackRockerAngle; }

	/* �õ�����ҡ�˷���� */
	inline const float getAceRockerAngle() { return aceRockerAngle; }

private:

	/* ������ͨ����ҡ�� */
	void initNormalAttackRocker();

	/* �������ҡ�� */
	void initAceRocker();

	void update(float delta);

	//����ҡ����ָ�Ƕ�
	void updateRad();

	cocos2d::Vec2 normalAttackRockerBGPosition;

	cocos2d::Vec2 normalAttackRockerPosition;

	cocos2d::Vec2 aceRockerBGPosition;

	cocos2d::Vec2 aceRockerPosition;

	cocos2d::Sprite* normalAttackRockerBG;

	cocos2d::Sprite* normalAttackRocker;

	cocos2d::Sprite*  aceRockerBG;

	cocos2d::Sprite* aceRocker;

	/* ҡ�˵İ뾶 */
	float RockerBackgroundRadius;

	/* ��ͨ����ҡ�˵ķ���� */
	float normalAttackRockerAngle;

	/* ����ҡ�˵ķ���� */
	float aceRockerAngle;


	bool _isAttacking = false;

	bool _isAceTime = false;
};
#endif

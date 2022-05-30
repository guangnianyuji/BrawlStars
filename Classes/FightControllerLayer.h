#ifndef __FIGHTCONTROLLERLAYER_H__
#define __FIGHTCONTROLLERLAYER_H__

#include "cocos2d.h"
#include "Math.h"
#include "AttackLayer.h"
using namespace cocos2d;

class AttackLayer;

class FightControllerLayer :public Layer
{
	friend class AttackLayer;
public:
	//�������Ʋ�
	static FightControllerLayer* create(Vec2 position);

	//�����ƶ�ҡ�ˣ�����ҡ�ˣ����������¼���
	void startMoveRocker(bool isStop);

	//ֹͣ�ƶ�ҡ�ˣ�����ҡ�ˣ�ȡ�������¼���
	void stopMoveRocker();

	//�õ��Ƿ��ܲٿ��ƶ�ҡ��
	bool getisCanMove();

	//�õ������
	float getMoveRockerAngle();

	AttackLayer* m_AttackLayer;

private:


	void initMoveRocker();

	void initEventListener();

	//�Ƿ�ɲ����ƶ�ҡ��
	bool m_isCanMove;

	EventListenerTouchAllAtOnce* m_TouchListener;

	EventListenerKeyboard* m_KeyboardListener;

	//��ʼ��
	virtual bool init() override;

	//ҡ�˽ڵ�
	Sprite* m_MoveRockerBackgroundSprite;

	//ҡ�˱����ڵ�
	Sprite* m_MoveRockerSprite;

	//ҡ�˱���������
	Vec2 m_MoveRockerBackgroundPosition;

	//ҡ�˱����İ뾶
	float m_MoveRockerBackgroundRadius;

	//ҡ�˵�����
	Vec2 m_MoveRockerPosition;

	//ҡ�˵õ��ķ����
	float m_MoveRockerAngle;

	void update(float delta);

	//����ҡ����ָ�Ƕ�
	void updateRad( );

};

#endif//__FIGHTCONTROLLERLAYER_H__
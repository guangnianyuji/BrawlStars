#ifndef __FIGHTCONTROLLERLAYER_H__
#define __FIGHTCONTROLLERLAYER_H__

#include "cocos2d.h"
#include "Math.h"
using namespace cocos2d;

class FightControllerLayer :public Layer
{
public:
	//�������Ʋ�
	static FightControllerLayer* create(Vec2 position);

	//����ҡ�ˣ�����ҡ�ˣ����������¼���
	void startRocker(bool isStop);

	//ֹͣҡ�ˣ�����ҡ�ˣ�ȡ�������¼���
	void stopRocker();

	//�õ��Ƿ��ܲٿ�ҡ��
	bool getisCanMove();

	//�õ������
	float getRockerAngle();

private:
	//�Ƿ�ɲ���ҡ��
	bool m_isCanMove;

	//������
	EventListenerTouchOneByOne* m_TouchListener;
	EventListenerKeyboard* m_KeyboardListener;

	//��ʼ��
	bool init()override;

	//ҡ�˽ڵ�
	Sprite* m_RockerBackgroundSprite;

	//ҡ�˱����ڵ�
	Sprite* m_RockerSprite;

	//ҡ�˱���������
	Vec2 m_RockerBackgroundPosition;

	//ҡ�˱����İ뾶
	float m_RockerBackgroundRadius;

	//ҡ�˵�����
	Vec2 m_RockerPosition;

	//ҡ�˵õ��ķ����
	float m_RockerAngle;

	void update(float delta);

	//����ҡ����ָ�Ƕ�
	void updateRad( );
};

#endif//__FIGHTCONTROLLERLAYER_H__
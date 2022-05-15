#ifndef _FIGHTCONTROLLERLAYER_H__
#define _FIGHTCONTROLLERLAYER_H__

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
	//�жϿ��Ƹ˷��������ж�������������ƶ�
	int RocketDirection;
	

private:
	//�Ƿ�ɲ���ҡ��
	bool isCanMove;
	//������
	EventListenerTouchOneByOne* TouchListener;
	EventListenerKeyboard* KeyboardListener;
	//��ʼ��
	bool init()override;
	//ҡ�˽ڵ�
	Sprite* RockerBackgroundSprite;
	//ҡ�˱����ڵ�
	Sprite* RockerSprite;
	//ҡ�˱���������
	Vec2 RockerBackgroundPosition;
	//ҡ�˱����İ뾶
	float RockerBackgroundRadius;
	//ҡ�˵�����
	Vec2 RockerPosition;

	void update(float dt);
};

#endif//__FIGHTCONTROLLERLAYER_H__
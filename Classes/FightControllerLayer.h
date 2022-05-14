#ifndef _FIGHTCONTROLLERLAYER_H__
#define _FIGHTCONTROLLERLAYER_H__

#include "cocos2d.h"
#include "Math.h"
using namespace cocos2d;

class FightControllerLayer :public Layer
{
public:
	//�������Ʋ�
	static FightControllerLayer* create();
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
	//����״̬
	std::map <EventKeyboard::KeyCode, bool> KeyStateValueMap;

};

#endif//__FIGHTCONTROLLERLAYER_H__
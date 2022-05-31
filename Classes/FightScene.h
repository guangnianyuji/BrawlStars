#ifndef  __FIGHTSCENE_H__
#define  __FIGHTSCENE_H__

#include "cocos2d.h"
#include "Player.h"
#include "BSScene\BaseScene.h"
#include "FightControllerLayer.h"
#include "AttackLayer.h"
#include "Character.h"
#include "TimeCounter.h"
#include  <typeinfo>

using namespace cocos2d;

class FightScene:public BaseScene
{
public:
	//���쳡��
	static FightScene* create(Character character);

private:	
	//��ʼ������
	bool init() override;

	void update(float delta);

    //�õ�ͼ�����ǹ���
	void updateViewPointByPlayer();

	//�����������״̬
	void updatePlayerMove();

	//������ҵ��չ����ܷ���
	void updatePlayerAttack(float nowTime);

	//������ҵľ��м��ܷ���
	void updatePlayerAce();

	//�ڳ����п�����ײ����
	void startContactListen();

	//�����������忪ʼ��ײ�Ļص�����
	bool onContactBegin(cocos2d::PhysicsContact& contact);


	TMXTiledMap* m_TiledMap;
	TMXLayer* m_WallLayer;

	FightControllerLayer* m_FightControllerLayer;

	Player* m_Player;

	EventListenerPhysicsContact* m_ContactListener;

	TimeCounter* m_TimeCounter;

	//�����ຯ��
	//����������ת��Ϊ��Ƭ����
	Vec2 PositionToTiled(const Vec2& position);
};

#endif // ! __FIGHTSCENE_H__


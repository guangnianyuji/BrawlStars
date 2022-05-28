#ifndef  __FIGHTSCENE_H__
#define  __FIGHTSCENE_H__

#include "cocos2d.h"
#include "Player.h"
#include "BSScene\BaseScene.h"
#include "MoveControllerLayer.h"
#include "AttackLayer.h"
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

	//���ż��ܶ�������
	void updatePlayerAttack();

	//�ڳ����п�����ײ����
	void startContactListen();

	//�����������忪ʼ��ײ�Ļص�����
	bool OnContactBegin(cocos2d::PhysicsContact& contact);


	TMXTiledMap* m_TiledMap;
	TMXLayer* m_WallLayer;

	MoveControllerLayer* m_MoveControllerLayer;

	AttackLayer* m_AttackLayer;

	Player* m_Player;

	EventListenerPhysicsContact* m_ContactListener;

	//�����ຯ��
	//����������ת��Ϊ��Ƭ����
	Vec2 PositionToTiled(const Vec2& position);
};

#endif // ! __FIGHTSCENE_H__


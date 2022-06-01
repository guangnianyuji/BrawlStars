#ifndef  __FIGHTSCENE_H__
#define  __FIGHTSCENE_H__

#include "cocos2d.h"
#include "Player.h"
#include "AI.h"
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
	static FightScene* create(std::vector<Character>);

private:	
	//��ʼ������
	bool init() override;

	//void onEnter() override;

	void update(float delta);

    //�õ�ͼ�����ǹ���
	void updateViewPointByPlayer();

	//�����������״̬
	void updatePlayerMove();

    //���¶���
	void updateToxicFog();

	//���¶����˺�
	void updateToxicFogDamage();

	//���ż��ܶ�������
	//void updatePlayerAttack();

	//������ҵļ��ܷ���
	void updatePlayerAttack(float nowTime);

	//������ҵľ��м��ܷ���
	void updatePlayerAce();

	//�ڳ����п�����ײ����
	//void startContactListen();

	//�����������忪ʼ��ײ�Ļص�����
	//bool onContactBegin(cocos2d::PhysicsContact& contact);


	TMXTiledMap* m_TiledMap;
	TMXLayer* m_WallLayer;

	std::map < Vec2, bool > m_ToxicFogMap;//��¼ĳһ��Ƭλ���Ƿ��ж���
	TimeCounter* m_ToxicFogTimeCounter;//������Χ�ļ�ʱ��
	int m_ToxicFogLevel;//��Ȧ�ĵȼ�
	int m_TempToxicFogLevel;//��Ȧ����ʱ�ȼ�
	std::vector<Sprite*> m_ToxicFogSpriteVec;

	FightControllerLayer* m_FightControllerLayer;

	Player* m_Player;
	std::vector<AI*> m_AIVec;

	EventListenerPhysicsContact* m_ContactListener;

	TimeCounter* m_TimeCounter;

	//�����ຯ��
	//����������ת��Ϊ��Ƭ����
	Vec2 PositionToTiled(const Vec2& position);
	//����Ƭ����ת��Ϊ��������
	Vec2 TiledToPosition(const Vec2& position);
};

#endif // ! __FIGHTSCENE_H__


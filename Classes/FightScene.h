#ifndef  __FIGHTSCENE_H__
#define  __FIGHTSCENE_H__

#include "cocos2d.h"
#include "Player.h"
#include "AI.h"
#include "Box.h"
#include "FightControllerLayer.h"
#include "TimeCounter.h"
#include "PauseScene.h"
#include "MathUtils.h"
#include "NotifyUtil.h"
#include "PathFinding.h"
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

	//������ҵļ��ܷ���
	void updatePlayerAttack();

	//������ҵľ��м��ܷ���
	void updatePlayerACE();

	//�ڳ����п�����ײ����
	void startContactListen();

	//���±���
	void updateBox();

	//�����������忪ʼ��ײ�Ļص�����
	bool onContactBegin(cocos2d::PhysicsContact& contact);


	TMXTiledMap* m_TiledMap;
	TMXLayer* m_WallLayer;
	std::vector<Sprite*> m_WallTield;

	std::map < Vec2, bool > m_ToxicFogMap;//��¼ĳһ��Ƭλ���Ƿ��ж���
	TimeCounter* m_ToxicFogTimeCounter;//������Χ�ļ�ʱ��
	int m_ToxicFogLevel;//��Ȧ�ĵȼ�
	int m_TempToxicFogLevel;//��Ȧ����ʱ�ȼ�
	std::vector<Sprite*> m_ToxicFogSpriteVec;

	FightControllerLayer* m_FightControllerLayer;

	Player* m_Player;

	std::vector<AI*> m_AIVec;
	std::vector<Box*> m_BoxVec;
     std::map<Vec2, bool> m_canPutBox;

	EventListenerPhysicsContact* m_ContactListener;
	
	//Ϊ����������λ��
	Vec2 RandomTiledforBox();
};

#endif // ! __FIGHTSCENE_H__


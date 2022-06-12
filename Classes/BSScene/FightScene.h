#ifndef  __FIGHTSCENE_H__
#define  __FIGHTSCENE_H__

#include "cocos2d.h"
#include "Entity/Hero/Player.h"
#include "Entity/Hero/AI.h"
#include "Entity/Box.h"
#include "BSLayer/FightControllerLayer.h"
#include "Util/TimeCounter.h"
#include "BSScene/PauseScene.h"
#include "Util/MathUtils.h"
#include "Util/NotifyUtil.h"
#include "Util/PathFinding.h"
#include "BSScene/ScoreScene.h"
#include  <typeinfo>

using namespace cocos2d;

class FightScene:public BaseScene
{
public:
	//���쳡��
	static FightScene* create(std::vector<Character>,std::string& map);

private:	
	//��ʼ������
	bool init() override;

	//void onEnter() override;

	void initPauseButton();

	void startToxic();

	void getWall();

	void addAI();

	//��ʼ��ʱ�򽫱�����ӽ�����
	void addBox();


	void update(float delta);

    //�õ�ͼ�����ǹ���
	void updateViewPointByPlayer();

	//�����������״̬
	void updatePlayerMove();

    //���¶���
	void updateToxicFog();

	//���¶����˺�
	void updateToxicFogDamage(float delta);

	//������ҵļ��ܷ���
	void updatePlayerAttack();

	//������ҵľ��м��ܷ���
	void updatePlayerACE();

	//�ڳ����п�����ײ����
	void startContactListen();

	//���±���
	void updateBox();

	//����Hero�Լ�Box��λ����Ϣ��������֪ͨ
	void updatePositionInformation(float delta);

	//�����������忪ʼ��ײ�Ļص�����
	bool onContactBegin(cocos2d::PhysicsContact& contact);

	//�����Ҵ�������
	void updateSurvivor();

	//�����Ҵ�����Ϣ
	void updateSurvivorLabel();


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

	Label* m_SurvivorLabel;
	int m_SurvivorNumber;
	int m_TempSurvivorNumber;
	
	//Ϊ����������λ��
	Vec2 RandomTiledforBox();
};

#endif // ! __FIGHTSCENE_H__


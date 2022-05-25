#ifndef  __FIGHTSCENE_H__
#define  __FIGHTSCENE_H__

#include "cocos2d.h"
#include "Player.h"
#include "BSScene\BaseScene.h"
#include "FightControllerLayer.h"
#include "AttackLayer.h"

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


	TMXTiledMap* m_TiledMap;

	FightControllerLayer* m_FightControllerLayer;

	AttackLayer* m_AttackLayer;

	Player* m_Player;


};

#endif // ! __FIGHTSCENE_H__


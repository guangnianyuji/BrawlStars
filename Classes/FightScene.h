#ifndef  __FIGHTSCENE_H__
#define  __FIGHTSCENE_H__

#include "cocos2d.h"
#include "Player.h"
#include "TiledMapUtils.h"
#include "FightControllerLayer.h"

using namespace cocos2d;

class FightScene:public Scene
{
public:
	//���쳡��
	static FightScene* create(Character character);

private:	
	//��ʼ������
	bool init() override;
    //�õ�ͼ�����ǹ���
	void setViewPointByPlayer();

	//�����������״̬
	void updatePlayerMove(float delta);

	TMXTiledMap* m_TiledMap;
	FightControllerLayer* m_FightControllerLayer;
	Player* m_Player;


};

#endif // ! __FIGHTSCENE_H__


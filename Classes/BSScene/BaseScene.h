
#ifndef __BASE_SCENE_H__
#define __BASE_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "AudioEngine.h"
#include "BSLayer/BrawlStarsMenu.h"



/* BaseScene����Ϸ�������� */
class BaseScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init() override;

    /* �ڳ����м���˵����˵���ť */
    void addMenu();
    void initMenuButton();
    void menuCallback(Ref* pSender);

    /* ���Ƴ��������������ɹ�������� */
    void drawBackGround(cocos2d::Sprite*);

    
    CREATE_FUNC(BaseScene);

protected:

    cocos2d::Sprite* bgSprite = nullptr;
    cocos2d::Menu* menuButton=nullptr;

};

#endif 

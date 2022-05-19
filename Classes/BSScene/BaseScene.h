
#ifndef __BASE_SCENE_H__
#define __BASE_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "AudioEngine.h"
#include "BrawlStarsMenu.h"



/* BaseScene是游戏场景基类 */
class BaseScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init() override;

    /* 在场景中加入菜单及菜单按钮 */
    void addMenu();
    void initMenuButton();
    void menuCallback(Ref* pSender);

    /* 绘制场景背景函数，可供子类调用 */
    void drawBackGround(cocos2d::Sprite*);

    
    CREATE_FUNC(BaseScene);

protected:

    cocos2d::Sprite* bgSprite = nullptr;
    cocos2d::Menu* menuButton=nullptr;

};

#endif 

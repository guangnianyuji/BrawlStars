#ifndef __BrawlStars_Menu_H__
#define __BrawlStars_Menu_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace cocos2d::ui;

class BrawlStarsMenu :public cocos2d::Layer
{
public:

	static cocos2d::Layer* createLayer();
	//cocos2d::Scene* createScene();
	virtual bool init() override;

	void drawMenuBackGround();
	void initMenuLabel();

	void initExitButton();
	void initPauseButton();
	void initBackgroundMusicButton();
	void initSoundEffectsButton();
	void initCloseButton();


	void exitCallback(cocos2d::Ref* pSender);
	void pauseCallback(cocos2d::Ref* pSender);
	void closeCallback(cocos2d::Ref* pSender);
	//��д�������������ʼ������
	CREATE_FUNC(BrawlStarsMenu);

protected:

	cocos2d::Sprite* menuSprite = nullptr;
	cocos2d::Label* menuLabel = nullptr;

	cocos2d::Menu* exitButton=nullptr;
	cocos2d::Menu* pauseButton=nullptr;
	cocos2d::Menu* musicButton=nullptr;
	cocos2d::Menu* soundEffectsButton=nullptr;
	cocos2d::Menu* closeButton = nullptr;


private:

};


#endif

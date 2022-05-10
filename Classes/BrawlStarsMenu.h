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

	void initExitButton();
	void initPauseButton();
	void initBackgroundMusicButton();
	void initSoundEffectsButton();

	void exitCallback(cocos2d::Ref* pSender);
	//void pauseCallback(cocos2d::Ref* pSender);

	void Test();

	//不写这个函数场景初始化不了
	CREATE_FUNC(BrawlStarsMenu);

protected:
	/*
	Button* exitButton;
	Button* pauseButton;
	Button* musicButton;
	Button* soundEffectsButton;
	*/

	cocos2d::Menu* exitButton;
};


#endif

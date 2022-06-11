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

	virtual void onEnter();

	void drawMenuBackGround();
	void initMenuLabel();
	void playbgMusic();

	void initExitButton();
	void initDNDButton();
	void initCloseButton();


	void initBackgroundMusicButton();
	void initSoundEffectsButton();

	void initBackgroundMusicSlider();
	void initSoundEffectsSlider();

	//不写这个函数场景初始化不了
	CREATE_FUNC(BrawlStarsMenu);

private:

	void exitCallback(cocos2d::Ref* pSender);
	void DNDCallback(cocos2d::Ref* pSender);
	void closeCallback(cocos2d::Ref* pSender);

	void musicSliderCallback(cocos2d::Ref* ref, cocos2d::ui::Slider::EventType type);
	void soundEffectsSliderCallback(cocos2d::Ref* ref, cocos2d::ui::Slider::EventType type);

	cocos2d::Sprite* menuSprite;
	cocos2d::Label* menuLabel;

	cocos2d::Menu* exitButton;
	cocos2d::Menu* DNDButton;
	cocos2d::Menu* closeButton;
	cocos2d::ui::CheckBox* musicButton;
	cocos2d::ui::CheckBox* soundEffectsButton;
	cocos2d::ui::Slider* musicSlider;
	cocos2d::ui::Slider* soundEffectsSlider;

	int bgMusicID;

	/* 用静态变量控制背景音乐状态 */
	static bool whetherToPlaybgMusic;

	static bool isbgMusicPlaying;

	static int bgMusicVolume;

};


#endif

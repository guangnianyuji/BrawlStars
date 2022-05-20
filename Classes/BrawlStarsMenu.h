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
	void bgplayMusic();

	void initExitButton();
	void initDNDButton();
	void initCloseButton();


	void initBackgroundMusicButton();
	void initSoundEffectsButton();

	void initBackgroundMusicSlider();
	void initSoundEffectsSlider();


	void exitCallback(cocos2d::Ref* pSender);
	void DNDCallback(cocos2d::Ref* pSender);
	void closeCallback(cocos2d::Ref* pSender);

	void musicSliderCallback(cocos2d::Ref* ref, cocos2d::ui::Slider::EventType type);
	void soundEffectsSliderCallback(cocos2d::Ref* ref, cocos2d::ui::Slider::EventType type);

	//不写这个函数场景初始化不了
	CREATE_FUNC(BrawlStarsMenu);

protected:

	cocos2d::Sprite* menuSprite = nullptr;
	cocos2d::Label* menuLabel = nullptr;

	cocos2d::Menu* exitButton=nullptr;
	cocos2d::Menu* DNDButton=nullptr;
	cocos2d::Menu* closeButton = nullptr;
	cocos2d::ui::CheckBox* musicButton=nullptr;
	cocos2d::ui::CheckBox* soundEffectsButton=nullptr;
	cocos2d::ui::Slider* musicSlider = nullptr;
	cocos2d::ui::Slider* soundEffectsSlider = nullptr;



private:

	int bgMusicID;
	bool isbgMusicPlaying = false;
};


#endif

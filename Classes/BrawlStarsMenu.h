#ifndef __BrawlStars_Menu_H__
#define __BrawlStars_Menu_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace cocos2d::ui;

class BrawlStarsMenu :public cocos2d::Layer
{
public:

	static cocos2d::Layer* createLayer();
	virtual bool init() override;
	void initExitButton();
	void initPauseButton();
	void initBackgroundMusicButton();
	void initSoundEffectsButton();
	
	void exitCallback(cocos2d::Ref* pSender);
	void pauseCallback(cocos2d::Ref* pSender);

protected:
	Button* exitButton;
	Button* pauseButton;
	Button* musicButton;
	Button* soundEffectsButton;
};


#endif

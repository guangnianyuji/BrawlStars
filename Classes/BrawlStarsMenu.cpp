#include "BrawlStarsMenu.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace cocos2d::ui;

cocos2d::Layer* BrawlStarsMenu::createLayer()
{
	return cocos2d::Layer::create();
}

bool BrawlStarsMenu::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	auto origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	initExitButton();

	//initPauseButton();
	
	//initBackgroundMusicButton();

	//initSoundEffectsButton();

	return true;
}

void BrawlStarsMenu::initExitButton()
{
	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	auto origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	exitButton = Button::create("Normal_Button.png", "Pressed_Button.png");

	exitButton->setTitleText("exit Game");

	exitButton->setTitleFontSize(35);

	exitButton->setPosition(cocos2d::Vec2(200, 200));

	exitButton->setTouchEnabled(false);

	exitButton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			break;
		case ui::Widget::TouchEventType::ENDED:
			Director::getInstance()->end();
			break;
		default:
			break;
		}
		});

	this->addChild(exitButton, 0);
}
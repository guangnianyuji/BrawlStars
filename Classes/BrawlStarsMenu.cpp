#include "BrawlStarsMenu.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

cocos2d::Layer* BrawlStarsMenu::createLayer()
{
	return BrawlStarsMenu::create();
}

void BrawlStarsMenu::initExitButton()
{
	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	auto origin = cocos2d::Director::getInstance()->getVisibleOrigin();


	auto exitBtnPic = cocos2d::MenuItemImage::create("Normal_Button.png",
		"Pressed_Button.png",
		CC_CALLBACK_1(BrawlStarsMenu::exitCallback, this));
	if (exitBtnPic == nullptr ||
		exitBtnPic->getContentSize().width <= 0 ||
		exitBtnPic->getContentSize().height <= 0)
	{
		//problemLoading("'CloseNormal.png' and 'CloseSelected.png'");

	}
	else
	{
		float x = origin.x + visibleSize.width / 3;
		float y = origin.y + visibleSize.height / 2;
		exitBtnPic->setAnchorPoint(cocos2d::Vec2::ZERO);
		exitBtnPic->setPosition(cocos2d::Vec2(x, y));
	}

	this->exitButton = Menu::create(exitBtnPic, nullptr);
	//这里以前错写为menu->setPosition(Vec2...)导致按钮未显示
	this->addChild(exitButton, 0);

	this->exitButton->retain();

	exitButton->setPosition(Vec2::ZERO);
	


	cocos2d::Director::getInstance()->getOpenGLView()->setCursorVisible(true);

}
bool BrawlStarsMenu::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	auto origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	//this->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height/2 + origin.y));


	initExitButton();

	//initPauseButton();

	//initBackgroundMusicButton();

	//initSoundEffectsButton();

	/*
	auto layer1 = LayerColor::create(Color4B(255, 0, 0, 255), 100, 100);
	layer1->setPosition(Vec2(200, 200));
	layer1->retain();
	this->addChild(layer1, 0);

	auto layer2 = LayerColor::create(Color4B(255, 125, 0, 255), 100, 100);
	layer2->setPosition(Vec2(150, 150));
	layer2->retain();
	this->addChild(layer2);

	auto layer3 = LayerColor::create(Color4B(255, 200, 0, 255), 100, 100);
	layer3->setPosition(Vec2(100, 100));
	layer3->retain();
	this->addChild(layer3);
	*/
	return true;
}

void BrawlStarsMenu::exitCallback(Ref* psender)
{
	Director::getInstance()->end();
}
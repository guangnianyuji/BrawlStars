#include "BrawlStarsMenu.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

cocos2d::Layer* BrawlStarsMenu::createLayer()
{
	return BrawlStarsMenu::create();
}


void BrawlStarsMenu::drawMenuBackGround()
{
	Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	Point origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	//this->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height/2 + origin.y));

	this->menuSprite = cocos2d::Sprite::create("Menu3.png");

	menuSprite->setScaleY(1.5);

	if (menuSprite == nullptr)
	{

	}
	else
	{
		float x = origin.x + visibleSize.width / 2;
		float y = origin.y + visibleSize.height / 2;
		menuSprite->setPosition(cocos2d::Vec2(x, y));
		this->addChild(menuSprite, -1);
	}
}

void BrawlStarsMenu::initMenuLabel()
{
	Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	Point origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	this->menuLabel = Label::createWithTTF("Menu", "fonts/Marker Felt.ttf", 24);
	if (menuLabel == nullptr)
	{
		//problemLoading("'fonts/Marker Felt.ttf'");
	}
	else
	{
		// position the label on the center of the screen
		menuLabel->setPosition(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height - menuLabel->getContentSize().height * 2));

		// add the label as a child to this layer
		this->addChild(menuLabel, 1);
	}

}

void BrawlStarsMenu::initExitButton()
{

	Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	Point origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	auto exitBtnPic = cocos2d::MenuItemImage::create("Normal_exitButton.png",
		"Pressed_exitButton.png",
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
		float y = origin.y + visibleSize.height / 3;
		exitBtnPic->setAnchorPoint(cocos2d::Vec2::ZERO);
		exitBtnPic->setPosition(cocos2d::Vec2(x, y));
	}

	this->exitButton = Menu::create(exitBtnPic, nullptr);
	//这里以前错写为menu->setPosition(Vec2...)导致按钮未显示
	this->addChild(exitButton, 0);
	exitButton->setPosition(Vec2::ZERO);

}

void BrawlStarsMenu::initPauseButton()
{
	Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	Point origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	auto pauseBtnPic = cocos2d::MenuItemImage::create("Normal_pauseButton.png",
		"Pressed_pauseButton.png",
		CC_CALLBACK_1(BrawlStarsMenu::exitCallback, this));
	if (pauseBtnPic == nullptr ||
		pauseBtnPic->getContentSize().width <= 0 ||
		pauseBtnPic->getContentSize().height <= 0)
	{
		//problemLoading("'CloseNormal.png' and 'CloseSelected.png'");

	}
	else
	{
		float x = origin.x + visibleSize.width / 3;
		float y = origin.y + visibleSize.height / 2;
		pauseBtnPic->setAnchorPoint(cocos2d::Vec2::ZERO);
		pauseBtnPic->setPosition(cocos2d::Vec2(x, y));
	}

	this->pauseButton = Menu::create(pauseBtnPic, nullptr);
	//这里以前错写为menu->setPosition(Vec2...)导致按钮未显示
	this->addChild(pauseButton, 0);
	pauseButton->setPosition(Vec2::ZERO);
}

void BrawlStarsMenu::initCloseButton()
{
	Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	Point origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	auto closeBtnPic = cocos2d::MenuItemImage::create("Normal_closeButton.png",
		"Pressed_closeButton.png",
		CC_CALLBACK_1(BrawlStarsMenu::closeCallback, this));
	if (closeBtnPic == nullptr ||
		closeBtnPic->getContentSize().width <= 0 ||
		closeBtnPic->getContentSize().height <= 0)
	{
		//problemLoading("'CloseNormal.png' and 'CloseSelected.png'");

	}
	else
	{
		float x = origin.x + visibleSize.width / 3.15;
		float y = origin.y + visibleSize.height / 1.3;
		closeBtnPic->setAnchorPoint(cocos2d::Vec2::ZERO);
		closeBtnPic->setPosition(cocos2d::Vec2(x, y));
	}

	this->closeButton = Menu::create(closeBtnPic, nullptr);
	//这里以前错写为menu->setPosition(Vec2...)导致按钮未显示
	this->addChild(closeButton, 0);
	closeButton->setPosition(Vec2::ZERO);
}

bool BrawlStarsMenu::init()
{
	if (!Layer::init())
	{
		return false;
	}

	drawMenuBackGround();
	
	initMenuLabel();
	initExitButton();

	initPauseButton();

	initCloseButton();

	//initBackgroundMusicButton();

	//initSoundEffectsButton();
	
	return true;
}



void BrawlStarsMenu::exitCallback(Ref* psender)
{
	Director::getInstance()->end();
}

void BrawlStarsMenu::closeCallback(Ref* psender)
{
	Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	Point origin = cocos2d::Director::getInstance()->getVisibleOrigin();


	float x = origin.x - visibleSize.width;
	float y = origin.y - visibleSize.height;

	this->setPosition(x, y);
}
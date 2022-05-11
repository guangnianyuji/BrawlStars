#include "BrawlStarsMenu.h"
#include "AudioEngine.h"

USING_NS_CC;

cocos2d::Layer* BrawlStarsMenu::createLayer()
{
	return BrawlStarsMenu::create();
}

void BrawlStarsMenu::drawMenuBackGround()
{
	Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	Point origin = cocos2d::Director::getInstance()->getVisibleOrigin();


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
		menuLabel->setPosition(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height - menuLabel->getContentSize().height * 2));

		this->addChild(menuLabel, 1);
	}

}

void BrawlStarsMenu::bgplayMusic()
{
	if (!isbgMusicPlaying)
	{
		bgMusicID = experimental::AudioEngine::play2d("bgMusic.mp3",true);
		isbgMusicPlaying = true;
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
		float x = origin.x + visibleSize.width / 32*16;
		float y = origin.y + visibleSize.height / 16*2.5;
		exitBtnPic->setAnchorPoint(cocos2d::Vec2::ZERO);
		exitBtnPic->setPosition(cocos2d::Vec2(x, y));
	}

	this->exitButton = Menu::create(exitBtnPic, nullptr);
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
		float x = origin.x + visibleSize.width / 32*11;
		float y = origin.y + visibleSize.height / 16*2.5;
		pauseBtnPic->setAnchorPoint(cocos2d::Vec2::ZERO);
		pauseBtnPic->setPosition(cocos2d::Vec2(x, y));
	}

	this->pauseButton = Menu::create(pauseBtnPic, nullptr);
	this->addChild(pauseButton, 0);
	pauseButton->setPosition(Vec2::ZERO);
}

void BrawlStarsMenu::initBackgroundMusicButton()
{
	Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	Point origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	musicButton = cocos2d::ui::CheckBox::create("Selected_CheckBox.png",
		"Selected_CheckBox.png","Normal_CheckBox.png","Normal_CheckBox.png", "Normal_CheckBox.png");

	if (musicButton == nullptr ||
		musicButton->getContentSize().width <= 0 ||
		musicButton->getContentSize().height <= 0)
	{
		//problemLoading("'CloseNormal.png' and 'CloseSelected.png'");

	}
	else
	{
		musicButton->setScale(0.3);

		musicButton->setAnchorPoint(Vec2(0, 0));

		auto musicLabel = Label::createWithTTF("music", "fonts/Marker Felt.ttf", 60);

		musicLabel->setAnchorPoint(Vec2(-0.8, 0));


		musicButton->addChild(musicLabel);

	

		float x = origin.x + visibleSize.width / 32*10.3;
		float y = origin.y + visibleSize.height / 16*9.5;
		musicButton->setPosition(cocos2d::Vec2(x, y));

		this->addChild(musicButton,0);
	}

	musicButton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:

			break;
		case ui::Widget::TouchEventType::ENDED:
			
			if (isbgMusicPlaying)
			{
				experimental::AudioEngine::stop(bgMusicID);
				musicSlider->setTouchEnabled(false);
				isbgMusicPlaying = false;
			}
			else
			{
				bgMusicID = experimental::AudioEngine::play2d("bgMusic.mp3");
				musicSlider->setTouchEnabled(true);
				isbgMusicPlaying = true;
			}

			break;
		default:
			break;
		}
		});
}

void BrawlStarsMenu::initSoundEffectsButton()
{
	Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	Point origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	soundEffectsButton = cocos2d::ui::CheckBox::create("Selected_CheckBox.png",
		"Selected_CheckBox.png", "Normal_CheckBox.png", "Normal_CheckBox.png", "Normal_CheckBox.png");

	if (soundEffectsButton == nullptr ||
		soundEffectsButton->getContentSize().width <= 0 ||
		soundEffectsButton->getContentSize().height <= 0)
	{
		//problemLoading("'CloseNormal.png' and 'CloseSelected.png'");

	}
	else
	{
		soundEffectsButton->setScale(0.3);

		soundEffectsButton->setAnchorPoint(Vec2(0.5,0.5));

		auto soundEffectsLabel = Label::createWithTTF("sound effeccts", "fonts/Marker Felt.ttf", 60);

		soundEffectsLabel->setAnchorPoint(Vec2(-0.3, 0));


		soundEffectsButton->addChild(soundEffectsLabel);



		float x = origin.x + visibleSize.width / 32*11.1;
		float y = origin.y + visibleSize.height / 16*7;
		soundEffectsButton->setPosition(cocos2d::Vec2(x, y));

		this->addChild(soundEffectsButton, 0);
	}

	soundEffectsButton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:

			break;
		case ui::Widget::TouchEventType::ENDED:

			if (isbgMusicPlaying)
			{
				experimental::AudioEngine::stop(bgMusicID);
				soundEffectsSlider->setTouchEnabled(false);
				isbgMusicPlaying = false;
			}
			else
			{
				bgMusicID = experimental::AudioEngine::play2d("bgMusic.mp3");
				soundEffectsSlider->setTouchEnabled(true);
				isbgMusicPlaying = true;
			}

			break;
		default:
			break;
		}
		});
}


void BrawlStarsMenu::initBackgroundMusicSlider()
{
	Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	Point origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	musicSlider = Slider::create();
	musicSlider->loadBarTexture("Slider_Back.png");
	musicSlider->loadSlidBallTextures("Slider_Normal.png", "Slider_Press.png", "Slider_Press.png");
	musicSlider->loadProgressBarTexture("Slider_PressBar.png");
	if (musicSlider == nullptr ||
		musicSlider->getContentSize().width <= 0 ||
		musicSlider->getContentSize().height <= 0)
	{
		//problemLoading("'CloseNormal.png' and 'CloseSelected.png'");

	}
	else
	{
		musicSlider->setPercent(80);
		musicSlider->addEventListener(CC_CALLBACK_2(BrawlStarsMenu::musicSliderCallback, this));

		musicSlider->setAnchorPoint(Vec2(0.5, 0.5));

		float x = origin.x + visibleSize.width / 32 * 11.1;
		float y = origin.y + visibleSize.height / 16 * 7;
		musicSlider->setPosition(cocos2d::Vec2(x, y));

		this->addChild(musicSlider, 0);
	}
	
	this->addChild(musicSlider);
}

void BrawlStarsMenu::initSoundEffectsSlider()
{
	soundEffectsSlider = Slider::create();
	soundEffectsSlider->loadBarTexture("Slider_Back.png");
	soundEffectsSlider->loadSlidBallTextures("Slider_Normal.png", "Slider_Press.png", "Slider_Press.png");
	soundEffectsSlider->loadProgressBarTexture("Slider_PressBar.png");

	soundEffectsSlider->setPercent(80);

	soundEffectsSlider->addEventListener(CC_CALLBACK_2(BrawlStarsMenu::soundEffectdSliderCallback, this));

	this->addChild(soundEffectsSlider);
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
		float x = origin.x + visibleSize.width / 3.2;
		float y = origin.y + visibleSize.height / 1.3;
		closeBtnPic->setAnchorPoint(cocos2d::Vec2::ZERO);
		closeBtnPic->setPosition(cocos2d::Vec2(x, y));
	}

	this->closeButton = Menu::create(closeBtnPic, nullptr);
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
	bgplayMusic();
	
	initMenuLabel();
	initExitButton();

	initPauseButton();
	initCloseButton();

	initBackgroundMusicButton();
	initSoundEffectsButton();

	initBackgroundMusicSlider();
	initSoundEffectsSlider();

	
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

void BrawlStarsMenu::musicSliderCallback(cocos2d::Ref* ref, cocos2d::ui::Slider::EventType type)
{
	switch (type)
	{
	case cocos2d::ui::Slider::EventType::ON_PERCENTAGE_CHANGED:
	{
		int percent = musicSlider->getPercent();
		//log("slider percent = %d", percent);
		if (isbgMusicPlaying)
		{
			experimental::AudioEngine::setVolume(bgMusicID, percent);
		}
	}
	break;
	default:
		break;
	}
}

void BrawlStarsMenu::soundEffectdSliderCallback(cocos2d::Ref* ref, cocos2d::ui::Slider::EventType type)
{

	switch (type)
	{
	case cocos2d::ui::Slider::EventType::ON_PERCENTAGE_CHANGED:
	{
		int percent = soundEffectsSlider->getPercent();
		//log("slider percent = %d", percent);
		if (isbgMusicPlaying)
		{
			experimental::AudioEngine::setVolume(bgMusicID, percent);
		}
	}
	break;
	default:
		break;
	}
}

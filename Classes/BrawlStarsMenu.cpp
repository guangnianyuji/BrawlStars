#include "BrawlStarsMenu.h"
#include "AudioEngine.h"

USING_NS_CC;

bool BrawlStarsMenu::isbgMusicPlaying = true;

cocos2d::Layer* BrawlStarsMenu::createLayer()
{
	return BrawlStarsMenu::create();
}

void BrawlStarsMenu::drawMenuBackGround()
{
	Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	Point origin = cocos2d::Director::getInstance()->getVisibleOrigin();


	this->menuSprite = cocos2d::Sprite::create("ui/BG.png");

	

	if (menuSprite == nullptr)
	{

	}
	else
	{
		menuSprite->setScaleY(0.6);
		menuSprite->setScaleX(0.4);
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

	this->menuLabel = Label::createWithTTF("Menu", "fonts/Marker Felt.ttf", 40);
	if (menuLabel == nullptr)
	{

	}
	else
	{
		menuLabel->setPosition(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height/16*13));

		this->addChild(menuLabel, 1);
	}

}

void BrawlStarsMenu::bgplayMusic()
{
	if (!isbgMusicPlaying)
	{
		bgMusicID = experimental::AudioEngine::play2d("music/bgMusic.mp3",true);
		isbgMusicPlaying = true;
	}
}

void BrawlStarsMenu::initExitButton()
{

	Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	Point origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	auto exitBtnPic = cocos2d::MenuItemImage::create("ui/Exit.png",
		"ui/Exit.png",
		CC_CALLBACK_1(BrawlStarsMenu::exitCallback, this));
	if (exitBtnPic == nullptr ||
		exitBtnPic->getContentSize().width <= 0 ||
		exitBtnPic->getContentSize().height <= 0)
	{
	}
	else
	{
		float x = origin.x + visibleSize.width / 32*22;
		float y = origin.y + visibleSize.height / 16*2;
		exitBtnPic->setAnchorPoint(cocos2d::Vec2(0.5,0.5));
		exitBtnPic->setPosition(cocos2d::Vec2(x, y));
	}

	this->exitButton = Menu::create(exitBtnPic, nullptr);
	this->addChild(exitButton, 0);
	exitButton->setPosition(Vec2::ZERO);
	exitButton->setScale(0.6);

}

void BrawlStarsMenu::initDNDButton()
{
	Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	Point origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	auto DNDBtnPic = cocos2d::MenuItemImage::create("ui/Notifications_ON.png",
		"ui/Notifications_OFF.png",
		CC_CALLBACK_1(BrawlStarsMenu::exitCallback, this));
	if (DNDBtnPic == nullptr ||
		DNDBtnPic->getContentSize().width <= 0 ||
		DNDBtnPic->getContentSize().height <= 0)
	{
	}
	else
	{
		float x = origin.x + visibleSize.width / 32*10;
		float y = origin.y + visibleSize.height / 16*2;
		DNDBtnPic->setAnchorPoint(cocos2d::Vec2(0.5,0.5));
		DNDBtnPic->setPosition(cocos2d::Vec2(x, y));
	}

	this->DNDButton = Menu::create(DNDBtnPic, nullptr);
	this->addChild(DNDButton, 0);
	DNDButton->setPosition(Vec2::ZERO);
	DNDButton->setScale(0.6);
}

void BrawlStarsMenu::initBackgroundMusicButton()
{
	Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	Point origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	musicButton = cocos2d::ui::CheckBox::create("ui/Music_ON.png",
		"ui/Music_ON.png","ui/Music_OFF.png","ui/Music_OFF.png", "ui/Music_OFF.png");

	if (musicButton == nullptr ||
		musicButton->getContentSize().width <= 0 ||
		musicButton->getContentSize().height <= 0)
	{
	}
	else
	{
		musicButton->setScale(0.6);

		musicButton->setAnchorPoint(Vec2(0, 0));

		auto musicLabel = Label::createWithTTF("music", "fonts/Marker Felt.ttf", 55);

		musicLabel->setAnchorPoint(Vec2(-1.5, 0));


		musicButton->addChild(musicLabel);

	

		float x = origin.x + visibleSize.width / 32*11;
		float y = origin.y + visibleSize.height / 16*10;
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
				soundEffectsSlider->setTouchEnabled(false);
				isbgMusicPlaying = false;
			}
			else
			{
				bgMusicID = experimental::AudioEngine::play2d("music/bgMusic.mp3");
				musicSlider->setTouchEnabled(true);
				int percent = musicSlider->getPercent();
				experimental::AudioEngine::setVolume(bgMusicID,(float)percent/100);
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

	soundEffectsButton = cocos2d::ui::CheckBox::create("ui/Sound_ON.png",
		"ui/Sound_ON.png", "ui/Sound_OFF.png", "ui/Sound_OFF.png", "ui/Sound_OFF.png");

	if (soundEffectsButton == nullptr ||
		soundEffectsButton->getContentSize().width <= 0 ||
		soundEffectsButton->getContentSize().height <= 0)
	{
	}
	else
	{
		soundEffectsButton->setScale(0.6);

		soundEffectsButton->setAnchorPoint(Vec2(0,0));

		auto soundEffectsLabel = Label::createWithTTF("sound effects", "fonts/Marker Felt.ttf", 55);

		soundEffectsLabel->setAnchorPoint(Vec2(-0.5, 0));


		soundEffectsButton->addChild(soundEffectsLabel);



		float x = origin.x + visibleSize.width / 32*11;
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
	musicSlider->loadBarTexture("ui/Load_BG.png");
	musicSlider->loadSlidBallTextures("ui/Slider.png", "ui/Slider.png", "ui/Slider.png");
	musicSlider->loadProgressBarTexture("ui/Load.png");
	if (musicSlider == nullptr ||
		musicSlider->getContentSize().width <= 0 ||
		musicSlider->getContentSize().height <= 0)
	{
		//problemLoading("'CloseNormal.png' and 'CloseSelected.png'");

	}
	else
	{
		musicSlider->setPercent(100);
		musicSlider->setScale(0.5);
		musicSlider->addEventListener(CC_CALLBACK_2(BrawlStarsMenu::musicSliderCallback, this));

		musicSlider->setAnchorPoint(Vec2(0.5, 0.5));

		float x = origin.x + visibleSize.width / 32 * 16;
		float y = origin.y + visibleSize.height / 16 * 9.5;
		musicSlider->setPosition(cocos2d::Vec2(x, y));

		this->addChild(musicSlider, 0);
	}
}

void BrawlStarsMenu::initSoundEffectsSlider()
{
	Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	Point origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	soundEffectsSlider = Slider::create();
	soundEffectsSlider->loadBarTexture("ui/Load_BG.png");
	soundEffectsSlider->loadSlidBallTextures("ui/Slider.png", "ui/Slider.png", "ui/Slider.png");
	soundEffectsSlider->loadProgressBarTexture("ui/Load.png");

if (soundEffectsSlider == nullptr ||
		soundEffectsSlider->getContentSize().width <= 0 ||
		soundEffectsSlider->getContentSize().height <= 0)
	{
		//problemLoading("'CloseNormal.png' and 'CloseSelected.png'");

	}
	else
	{
		soundEffectsSlider->setPercent(100);

		soundEffectsSlider->setScale(0.5);
		soundEffectsSlider->addEventListener(CC_CALLBACK_2(BrawlStarsMenu::soundEffectsSliderCallback, this));

		soundEffectsSlider->setAnchorPoint(Vec2(0.5, 0.5));

		float x = origin.x + visibleSize.width / 32 * 16;
		float y = origin.y + visibleSize.height / 16 * 6;
		soundEffectsSlider->setPosition(cocos2d::Vec2(x, y));

		this->addChild(soundEffectsSlider, 0);
	}
}

void BrawlStarsMenu::initCloseButton()
{
	Size winSize = cocos2d::Director::getInstance()->getWinSize();
	Point origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	auto closeBtnPic = cocos2d::MenuItemImage::create("ui/Close.png",
		"ui/Close.png",
		CC_CALLBACK_1(BrawlStarsMenu::closeCallback, this));
	if (closeBtnPic == nullptr ||
		closeBtnPic->getContentSize().width <= 0 ||
		closeBtnPic->getContentSize().height <= 0)
	{
		//problemLoading("'CloseNormal.png' and 'CloseSelected.png'");

	}
	else
	{
		float x = origin.x + winSize.width/32*10;
		float y = origin.y + winSize.height/16*14;
		closeBtnPic->setAnchorPoint(cocos2d::Vec2::ZERO);
		closeBtnPic->setPosition(cocos2d::Vec2(x, y));
	}

	this->closeButton = Menu::create(closeBtnPic, nullptr);
	this->addChild(closeButton, 0);
	closeButton->setPosition(Vec2::ZERO);
	closeButton->setScale(0.6);
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

	initDNDButton();
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
		log("slider percent = %d", percent);
		if (isbgMusicPlaying)
		{
			experimental::AudioEngine::setVolume(bgMusicID, (float)percent/100);
		}
	}
	break;
	default:
		break;
	}
}

void BrawlStarsMenu::soundEffectsSliderCallback(cocos2d::Ref* ref, cocos2d::ui::Slider::EventType type)
{

	switch (type)
	{
	case cocos2d::ui::Slider::EventType::ON_PERCENTAGE_CHANGED:
	{
		
	}
	break;
	default:
		break;
	}
}

#include "PauseScene.h"

PauseScene* PauseScene::create(cocos2d::RenderTexture* renderTexture)
{
	PauseScene* pRet = new(std::nothrow)PauseScene();

	auto  VisibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	renderTexture -> setPosition(VisibleSize / 2);
	pRet->addChild(renderTexture,-1);

	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}

bool PauseScene::init()
{
	if (!BaseScene::init())
	{
		return  false;
	}

	auto  VisibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	auto PauseSprite = cocos2d::Sprite::create("ui/BG2.png");

	if (PauseSprite == nullptr)
	{

	}
	else
	{
		PauseSprite->setScaleY(0.6);
		PauseSprite->setScaleX(0.4);
		float x = VisibleSize.width / 2;
		float y = VisibleSize.height / 2;
		PauseSprite->setPosition(cocos2d::Vec2(x, y));
		this->addChild(PauseSprite, 0);
	}


	auto PauseLabel = cocos2d::Label::createWithTTF("Pause", "fonts/Marker Felt.ttf", 40);
	if (PauseLabel == nullptr)
	{

	}
	else
	{
		PauseLabel->setPosition(cocos2d::Vec2( VisibleSize.width / 2,
			VisibleSize.height / 16 * 13));

		this->addChild(PauseLabel, 1);
	}

	auto ContinueMenuItem = MenuItemImage::create("ui/Play2.png", "ui/Play.png", [&](Ref* psender)->void
		{
			cocos2d::Director::getInstance()->popScene();
		});

    ContinueMenuItem->setScale(0.6);
	
	
    auto ReplayMenuItem = MenuItemImage::create("ui/Replay2.png", "ui/Replay.png", [&](Ref* psender)->void
	   {
			auto startscene = StartScene::create();
			if (startscene != nullptr)
			{
				cocos2d::Director::getInstance()->replaceScene(startscene);
			}
	   }); 
	      
	ReplayMenuItem->setScale(0.6);

	auto menu = Menu::create(ContinueMenuItem, ReplayMenuItem, NULL);
	menu->alignItemsVerticallyWithPadding(30);

	addChild(menu, 1);
	return true;
}
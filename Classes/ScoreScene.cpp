#include "ScoreScene.h"

ScoreScene* ScoreScene::create(int rank)
{
	ScoreScene* pRet = new(std::nothrow)ScoreScene();

	pRet->m_Rank = rank;

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

bool ScoreScene::init()
{
	if (!BaseScene::init())
	{
		return false;
	}
	this->drawBackGround(cocos2d::Sprite::create("scene_graph/background3.png"));
	
	cocos2d::Vec2 VisibleSize = cocos2d::Director::getInstance()->getVisibleSize();


	auto HeadLabel=cocos2d::Label::createWithTTF("SCORE","fonts/Marker Felt.ttf", 60);
	HeadLabel->setPosition(cocos2d::Vec2(VisibleSize.x/2, VisibleSize.y * 7 / 8));
	addChild(HeadLabel);

	auto RankLabel = cocos2d::Label::createWithTTF("YOU GET   "+cocos2d::Value(m_Rank).asString()+"    PLACE ",
		"fonts/Marker Felt.ttf", 100);
	RankLabel->setPosition(cocos2d::Vec2(VisibleSize.x / 2, VisibleSize.y * 2 / 3));
	addChild(RankLabel);

	std::string RemarkString;

	switch (m_Rank)
	{
	    case(1):RemarkString = "Winner Winner Chicken Dinner!!!"; break;

		case(2):
		case(3):RemarkString = "You Are Only One Step Away From Victory..."; break;

		case(4):
		case(5):
		case(6):
		case(7):RemarkString = "Play Again And Show Me Your Power..."; break;

		case(8):
		case(9):RemarkString = "You Should Hide Away At First..."; break;

		case(10):RemarkString = "Exit And Never Touch Me Again!!!"; break;
		
	}
	
	auto ReMarkLabel = cocos2d::Label::createWithTTF(RemarkString,"fonts/Marker Felt.ttf", 90);
	ReMarkLabel->setPosition(cocos2d::Vec2(VisibleSize.x / 2, VisibleSize.y /2));
	addChild(ReMarkLabel);

	auto CupLabel = cocos2d::Label::createWithTTF("You Win  "+cocos2d::Value(11-m_Rank).asString(), "fonts/Marker Felt.ttf", 90);
	CupLabel->setPosition(cocos2d::Vec2(VisibleSize.x / 2, VisibleSize.y / 4));
	addChild(CupLabel);

	auto CupSprite = cocos2d::Sprite::create("trophycup.png");
	CupSprite->setPosition(cocos2d::Vec2(VisibleSize.x * 5 / 7, VisibleSize.y  / 4));
	addChild(CupSprite);

	auto ExitButton = Button::create("ui/Exit.png");
	ExitButton->addTouchEventListener([&](Ref* psender, Widget::TouchEventType type)->void
			{
				cocos2d::Director::getInstance()->end();
			});
	ExitButton->setScale(0.6);
	ExitButton->setPosition(cocos2d::Vec2(VisibleSize.x - ExitButton->getContentSize().width / 2, ExitButton->getContentSize().height / 2));
	addChild(ExitButton);

	auto ReplayButton = Button::create("ui/Replay.png");
	ReplayButton->addTouchEventListener([&](Ref* psender, Widget::TouchEventType type)->void
		{
			cocos2d::Director::getInstance()->replaceScene(StartScene::create());
		});
	ReplayButton->setScale(0.6);
	ReplayButton->setPosition(cocos2d::Vec2(ReplayButton->getContentSize().width / 2, ReplayButton->getContentSize().height / 2));
	addChild(ReplayButton);
	
	return true;
}
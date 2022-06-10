#include "RoomScene.h"

RoomScene* RoomScene::create()
{
	RoomScene* pRet = new(std::nothrow)RoomScene();

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

bool RoomScene::init()
{
	if (!BaseScene::init())
	{
		return false;
	}
	this->drawBackGround(cocos2d::Sprite::create("scene_graph/background2.png"));

    m_TempFlag = 0;

    m_SelectedFlag = 10;//随意初始化无意义

	m_CharacterVec = { 10,Nothing() };
	m_TempCharacterVec = { 10,Nothing() };

	m_TipString = "Now you choose a Character for\n";

	m_CharacterItemVec = { 5,NULL };
	m_HeroItemVec = { 10,NULL };
	
	for (int i = 0; i < 10; i++)
	{
		auto HeroSprite = Sprite::create();
	    m_HeroSpriteVec.push_back (HeroSprite);
	}

	Vec2 visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	auto HeroMenu = Menu::create();

	m_HeroItemVec[0] = MenuItemImage::create("ui/Add1.png", "ui/Add11.png", ([&](Ref* psender)->void
		{
			m_TempFlag = 0;
		}
	));
	HeroMenu->addChild(m_HeroItemVec[0]);


	m_HeroItemVec[1] = MenuItemImage::create("ui/Add2.png", "ui/Add22.png", ([&](Ref* psender)->void
		{
			m_TempFlag = 1;
		}
	));
	HeroMenu->addChild(m_HeroItemVec[1]);
	
	m_HeroItemVec[2] = MenuItemImage::create("ui/Add2.png", "ui/Add22.png", ([&](Ref* psender)->void
		{
			m_TempFlag = 2;
		}
	));
	HeroMenu->addChild(m_HeroItemVec[2]);

	m_HeroItemVec[3] = MenuItemImage::create("ui/Add2.png", "ui/Add22.png", ([&](Ref* psender)->void
		{
			m_TempFlag = 3;
		}
	));
	HeroMenu->addChild(m_HeroItemVec[3]);

	m_HeroItemVec[4] = MenuItemImage::create("ui/Add2.png", "ui/Add22.png", ([&](Ref* psender)->void
		{
			m_TempFlag = 4;
		}
	));
	HeroMenu->addChild(m_HeroItemVec[4]);

	m_HeroItemVec[5] = MenuItemImage::create("ui/Add2.png", "ui/Add22.png", ([&](Ref* psender)->void
		{
			m_TempFlag = 5;
		}
	));
	HeroMenu->addChild(m_HeroItemVec[5]);

	m_HeroItemVec[6] = MenuItemImage::create("ui/Add2.png", "ui/Add22.png", ([&](Ref* psender)->void
		{
			m_TempFlag = 6;
		}
	));
	HeroMenu->addChild(m_HeroItemVec[6]);

	m_HeroItemVec[7] = MenuItemImage::create("ui/Add2.png", "ui/Add22.png", ([&](Ref* psender)->void
		{
			m_TempFlag = 7;
		}
	));
	HeroMenu->addChild(m_HeroItemVec[7]);

	m_HeroItemVec[8] = MenuItemImage::create("ui/Add2.png", "ui/Add22.png", ([&](Ref* psender)->void
		{
			m_TempFlag = 8;
		}
	));
	HeroMenu->addChild(m_HeroItemVec[8]);

	m_HeroItemVec[9] = MenuItemImage::create("ui/Add2.png", "ui/Add22.png", ([&](Ref* psender)->void
		{
			m_TempFlag =9;
		}
	));
	HeroMenu->addChild(m_HeroItemVec[9]);

	HeroMenu->alignItemsInColumns(5,5, NULL);
	HeroMenu->setPosition(visibleSize.x/2, visibleSize.y*2/3);
	addChild(HeroMenu);

	m_TipLabel = Label::create();
	addChild(m_TipLabel);

	auto CharacterMenu = Menu::create();
	m_CharacterItemVec[0] = MenuItemImage::create("F/Ff1.png", "F/Fb1.png", ([&](Ref* psender)->void
		{
			m_SelectedCharacter = Fei();
			m_TempCharacterVec[m_TempFlag] = m_SelectedCharacter;
		}
	));
	CharacterMenu->addChild(m_CharacterItemVec[0]);
	m_CharacterItemVec[1] = MenuItemImage::create("Y/Yf1.png", "Y/Yb1.png", ([&](Ref* psender)->void
		{
			m_TempCharacter = Yu();
			m_TempCharacterVec[m_TempFlag] = m_TempCharacter;
		}
	));
	CharacterMenu->addChild(m_CharacterItemVec[1]);
	m_CharacterItemVec[2] = MenuItemImage::create("J/Jf1.png", "J/Jb1.png", ([&](Ref* psender)->void
		{
			m_TempCharacter = Jide();
			m_TempCharacterVec[m_TempFlag] = m_TempCharacter;
		}
	));
	CharacterMenu->addChild(m_CharacterItemVec[2]);
	m_CharacterItemVec[3] = MenuItemImage::create("L/Lf1.png", "L/Lb1.png", ([&](Ref* psender)->void
		{
			m_TempCharacter =Lin();
			m_TempCharacterVec[m_TempFlag] = m_TempCharacter;
		}
	));
	CharacterMenu->addChild(m_CharacterItemVec[3]);
	m_CharacterItemVec[4] = MenuItemImage::create("ui/Close.png", "ui/Close1.png", ([&](Ref* psender)->void
		{
			m_TempCharacter =Nothing();
			m_TempCharacterVec[m_TempFlag] = m_TempCharacter;
		}
	));
	CharacterMenu->addChild(m_CharacterItemVec[4]);

	CharacterMenu->alignItemsHorizontallyWithPadding(80);
	CharacterMenu->setPosition(visibleSize.x /4, visibleSize.y / 6);
	addChild(CharacterMenu);

	for (int i = 0; i < 10; i++)
	{
		addChild(m_HeroSpriteVec[i]);
	}

	auto PlayButton = Button::create("ui/Leader.png", "ui/Leader1.png");
	PlayButton->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
		{
			//如果没有选择玩家角色，默认为菲
			if (m_CharacterVec[0] == Nothing())
			{
				m_CharacterVec[0] = Fei();
			}
			//如果没有选择AI 角色。默认为羽
			bool AIExistFlag = false;
			for (int i=1;i<10;i++)
			{
				if (!(m_CharacterVec[i] == Nothing()))
				{
					AIExistFlag = true;
					break;
				}
			}
			if (!AIExistFlag)
			{
				m_CharacterVec[1] = Yu();
			}
			Director::getInstance()->pushScene(FightScene::create(m_CharacterVec));
		});
	
	PlayButton->setPosition(Vec2(visibleSize.x * 3 / 4, visibleSize.y / 6));
	addChild(PlayButton);

	scheduleUpdate();

	return true;
}

void RoomScene::update(float delta)
{
	updateTip();
	updateHero();
}

void RoomScene::updateTip()
{

	if (m_TempFlag == m_SelectedFlag)
	{
		return;
	}
	Vec2 visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	m_SelectedFlag = m_TempFlag;
	removeChild(m_TipLabel);

	if (!m_SelectedFlag)
	{
		m_TipLabel = Label::createWithTTF(m_TipString + "Player", "fonts/Marker Felt.ttf", 30);
		m_TipLabel->setPosition(visibleSize.x / 8, visibleSize.y / 3);
		addChild(m_TipLabel);
		return;
	}

	m_TipLabel = Label::createWithTTF(m_TipString + "AI  "+Value(m_SelectedFlag).asString(), "fonts/Marker Felt.ttf", 30);
	m_TipLabel->setPosition(visibleSize.x / 8, visibleSize.y / 3);
	addChild(m_TipLabel);

}

void RoomScene::updateHero()
{
	for (int i = 0; i < 10; i++)
	{
		if (m_CharacterVec[i] == m_TempCharacterVec[i])
		{
			continue;
		}     
		 removeChild(m_HeroSpriteVec[i]);
		 m_CharacterVec[i] = m_TempCharacterVec[i];
		 if (m_TempCharacterVec[i] == Nothing())
		 {
			 return;
		 } 
		 Vec2 visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
		 Vec2 selectedposition = Vec2(visibleSize.x / 2, visibleSize.y * 2 / 3 )+m_HeroItemVec[i]->getPosition();
		 m_HeroSpriteVec[i] = Sprite::create(m_CharacterVec[i].m_Name+"/"+ m_CharacterVec[i].m_Name + "f1.png");
		 m_HeroSpriteVec[i]->setPosition(selectedposition);
		 addChild(m_HeroSpriteVec[i],2);
		 
	}
}
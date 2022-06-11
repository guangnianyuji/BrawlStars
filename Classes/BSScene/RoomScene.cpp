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
	Vec2 visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	this->drawBackGround(cocos2d::Sprite::create("scene_graph/background2.png"));

    m_TempFlag = 0;
    m_SelectedFlag = 10;//随意初始化无意义

	m_MapFlag = 1;
	m_TempMapFlag = 1;//随意初始化无意义
	m_TipLabel2 = Label::createWithTTF("Now you Choose 1 DESERT map", "fonts/Marker Felt.ttf", 30);
	m_TipLabel2->setPosition(Vec2(visibleSize.x * 3 / 4, visibleSize.y /8));
	addChild(m_TipLabel2);

	m_CharacterVec = { 10,Nothing() };
	m_TempCharacterVec = { 10,Nothing() };

	m_TipString = "Now you choose a Character for\n";

	m_CharacterItemVec = { 5,NULL };
	m_HeroItemVec = { 10,NULL };
	
	m_MapItemVec = { 3,NULL };

	for (int i = 0; i < 10; i++)
	{
		auto HeroSprite = Sprite::create();
	    m_HeroSpriteVec.push_back (HeroSprite);
		addChild(m_HeroSpriteVec[i]);
		
	}

	m_HeroMenu = Menu::create();

	m_HeroItemVec[0] = MenuItemImage::create("ui/Add1.png", "ui/Add11.png", ([&](Ref* psender)->void
		{
			m_TempFlag = 0;
		}
	));
	m_HeroMenu->addChild(m_HeroItemVec[0]);


	m_HeroItemVec[1] = MenuItemImage::create("ui/Add2.png", "ui/Add22.png", ([&](Ref* psender)->void
		{
			m_TempFlag = 1;
		}
	));
	m_HeroMenu->addChild(m_HeroItemVec[1]);
	
	m_HeroItemVec[2] = MenuItemImage::create("ui/Add2.png", "ui/Add22.png", ([&](Ref* psender)->void
		{
			m_TempFlag = 2;
		}
	));
	m_HeroMenu->addChild(m_HeroItemVec[2]);

	m_HeroItemVec[3] = MenuItemImage::create("ui/Add2.png", "ui/Add22.png", ([&](Ref* psender)->void
		{
			m_TempFlag = 3;
		}
	));
	m_HeroMenu->addChild(m_HeroItemVec[3]);

	m_HeroItemVec[4] = MenuItemImage::create("ui/Add2.png", "ui/Add22.png", ([&](Ref* psender)->void
		{
			m_TempFlag = 4;
		}
	));
	m_HeroMenu->addChild(m_HeroItemVec[4]);

	m_HeroItemVec[5] = MenuItemImage::create("ui/Add2.png", "ui/Add22.png", ([&](Ref* psender)->void
		{
			m_TempFlag = 5;
		}
	));
	m_HeroMenu->addChild(m_HeroItemVec[5]);

	m_HeroItemVec[6] = MenuItemImage::create("ui/Add2.png", "ui/Add22.png", ([&](Ref* psender)->void
		{
			m_TempFlag = 6;
		}
	));
	m_HeroMenu->addChild(m_HeroItemVec[6]);

	m_HeroItemVec[7] = MenuItemImage::create("ui/Add2.png", "ui/Add22.png", ([&](Ref* psender)->void
		{
			m_TempFlag = 7;
		}
	));
	m_HeroMenu->addChild(m_HeroItemVec[7]);

	m_HeroItemVec[8] = MenuItemImage::create("ui/Add2.png", "ui/Add22.png", ([&](Ref* psender)->void
		{
			m_TempFlag = 8;
		}
	));
	m_HeroMenu->addChild(m_HeroItemVec[8]);

	m_HeroItemVec[9] = MenuItemImage::create("ui/Add2.png", "ui/Add22.png", ([&](Ref* psender)->void
		{
			m_TempFlag =9;
		}
	));
	m_HeroMenu->addChild(m_HeroItemVec[9]);

	m_HeroMenu->alignItemsInColumns(5,5, NULL);
	m_HeroMenu->setPosition(visibleSize.x/2, visibleSize.y*2/3);
	addChild(m_HeroMenu);

	m_TipLabel1 = Label::create();
	addChild(m_TipLabel1);

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
	m_CharacterItemVec[4]->setScale(0.6);
	CharacterMenu->addChild(m_CharacterItemVec[4]);

	CharacterMenu->alignItemsHorizontallyWithPadding(50);
	CharacterMenu->setPosition(visibleSize.x /5, visibleSize.y / 6);
	addChild(CharacterMenu);

	m_MapMenu = Menu::create();

	m_MapItemVec[0] = MenuItemImage::create("map/map1.png", "ui/OK.png", ([&](Ref* psender)->void
		{
			m_MapFlag = 1;
		}));
	m_MapItemVec[0]->setScale(2);
	m_MapMenu->addChild(m_MapItemVec[0]);
	
	m_MapItemVec[1] = MenuItemImage::create("map/map2.png", "ui/OK.png", ([&](Ref* psender)->void
		{
			m_MapFlag = 2;
		}));
	m_MapItemVec[1]->setScale(2);
	m_MapMenu->addChild(m_MapItemVec[1]);
	
	m_MapItemVec[2] = MenuItemImage::create("map/map3.png", "ui/OK.png", ([&](Ref* psender)->void
		{
			m_MapFlag = 3;
		}));
	m_MapItemVec[2]->setScale(2);
	m_MapMenu->addChild(m_MapItemVec[2]);

	m_MapMenu->alignItemsHorizontallyWithPadding(20);

	m_MapMenu->setPosition(Vec2(visibleSize.x * 3 / 4, visibleSize.y / 3));
	addChild(m_MapMenu,2);


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
			std::string map = "map/map" + Value(m_MapFlag).asString()+".tmx";
			Director::getInstance()->pushScene(FightScene::create(m_CharacterVec,map));
		});
	
	PlayButton->setPosition(Vec2(visibleSize.x  / 2, visibleSize.y / 6));
	addChild(PlayButton);

	scheduleUpdate();

	return true;
}

void RoomScene::update(float delta)
{
	updateHero();
	updateTip1();
	updateTip2();
}

void RoomScene::updateTip1()
{

	if (m_TempFlag == m_SelectedFlag)
	{
		return;
	}
	Vec2 visibleSize = cocos2d::Director::getInstance()->getVisibleSize();

	m_SelectedFlag = m_TempFlag;
	removeChild(m_TipLabel1);

	if (!m_SelectedFlag)
	{
		m_TipLabel1 = Label::createWithTTF(m_TipString + "Player", "fonts/Marker Felt.ttf", 30);
		m_TipLabel1->setPosition(visibleSize.x / 8, visibleSize.y / 3);
		addChild(m_TipLabel1);
		return;
	}

	m_TipLabel1 = Label::createWithTTF(m_TipString + "AI  "+Value(m_SelectedFlag).asString(), "fonts/Marker Felt.ttf", 30);
	m_TipLabel1->setPosition(visibleSize.x / 8, visibleSize.y / 3);
	addChild(m_TipLabel1);

}

void RoomScene::updateTip2()
{
	if (m_TempMapFlag == m_MapFlag)
	{
		return;
	}
	Vec2 visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	m_TempMapFlag = m_MapFlag;
	removeChild(m_TipLabel2);
	std::string mapString;
	switch (m_MapFlag)
	{
	case 1:mapString = "1 DESERT"; break;
	case 2:mapString = "2 HELL"; break;
	case 3:mapString = "3 COUNTRYSIDE"; break;
	}
	
	m_TipLabel2 = Label::createWithTTF("Now you Choose "+ mapString+" map", "fonts/Marker Felt.ttf", 30);
	m_TipLabel2->setPosition(Vec2(visibleSize.x * 3 / 4, visibleSize.y / 8));
    addChild(m_TipLabel2);
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
		 Vec2 selectedposition =m_HeroMenu->getPosition()+m_HeroItemVec[i]->getPosition();
		 m_HeroSpriteVec[i] = Sprite::create(m_CharacterVec[i].m_Name+"/"+ m_CharacterVec[i].m_Name + "f1.png");
		 m_HeroSpriteVec[i]->setPosition(selectedposition);
		 addChild(m_HeroSpriteVec[i],2);
		 
	}
}
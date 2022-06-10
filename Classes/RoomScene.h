#ifndef __ROOMSCENE_H__
#define __ROOMSCENE_H__

#include "BSScene/BaseScene.h"
#include"FightScene.h"
#include "Character.h"

class RoomScene :public BaseScene
{
public:
	static RoomScene* create();

private:
	bool init() override;

	std::vector<Character> m_CharacterVec;
	std::vector<Character> m_TempCharacterVec;

	std::vector<MenuItemImage*> m_CharacterItemVec;

	std::vector<MenuItemImage*> m_HeroItemVec;
	Menu* m_HeroMenu;

	std::vector<MenuItemImage*> m_MapItemVec;
	Menu* m_MapMenu;

	std::string m_TipString;
	Label* m_TipLabel1;

	Character m_SelectedCharacter;
	Character m_TempCharacter;

	int m_SelectedFlag;
    int m_TempFlag;

	int m_MapFlag;
	int m_TempMapFlag;

	Label* m_TipLabel2;

	std::vector<Sprite*> m_HeroSpriteVec;



	void update(float delta) override;
	void updateTip1();
	void updateHero();
	void updateTip2();
};

#endif __ROOMSCENE_H__
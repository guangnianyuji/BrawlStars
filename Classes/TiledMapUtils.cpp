#include "TiledMapUtils.h"

void TiledMapUtils::putPlayer(TMXTiledMap* map, Player* player)
{
	//���ض����
	TMXObjectGroup* objectgroup = map->getObjectGroup("objects");
	//�����������
	ValueMap playerbitrhpoint = objectgroup->getObject("PlayerBirthPoint");
	float playerX = playerbitrhpoint.at("x").asFloat();
	float playerY = playerbitrhpoint.at("y").asFloat();

	player->setPosition(Point(playerX, playerY));
	map->addChild(player);
}
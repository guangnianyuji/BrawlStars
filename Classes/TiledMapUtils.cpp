#include "TiledMapUtils.h"

void TiledMapUtils::putPlayer(TMXTiledMap* map, Player* player)
{
	//加载对象层
	TMXObjectGroup* objectgroup = map->getObjectGroup("objects");
	//加载玩家坐标
	ValueMap playerbitrhpoint = objectgroup->getObject("PlayerBirthPoint");
	float playerX = playerbitrhpoint.at("x").asFloat();
	float playerY = playerbitrhpoint.at("y").asFloat();

	player->setPosition(Point(playerX, playerY));
	map->addChild(player);
}
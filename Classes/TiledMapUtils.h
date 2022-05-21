#ifndef __TILEDMAPUTILS_H__
#define __TILEDMAPUTILS_H__

#include "cocos2d.h"
#include "Player.h"

using namespace cocos2d;

class TiledMapUtils
{
public:
	static void putPlayer(TMXTiledMap* map, Player* player);
};


#endif
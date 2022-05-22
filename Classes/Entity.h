#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "cocos2d.h"

USING_NS_CC;

class Entity:public Node
{
public:	
	void setOriginalPositionInMap(TMXTiledMap* Map,const std::string& strPlace);

	bool init()override;
};

#endif

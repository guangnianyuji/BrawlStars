#include "Entity.h"

bool Entity::init()
{
	if (!Node::init())
	{
		return false;
	}

	return true;
}

void Entity::setOriginalPositionInMap(TMXTiledMap* Map,const std::string& strPlace)
	                           
{
	auto ObjectGroup = Map->getObjectGroup("objects");

	auto PlaceValueMap = ObjectGroup->getObject(strPlace);
	float oneEntityX = PlaceValueMap.at("x").asFloat();
	float oneEntityY = PlaceValueMap.at("y").asFloat();

	this->setPosition(Vec2(oneEntityX, oneEntityY));
}

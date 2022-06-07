#ifndef __ENTITY_H__
#define __ENTITY_H__

#include "cocos2d.h"
#include "ProgressView.h"

USING_NS_CC;

class Entity:public Node
{
public:	
	void setOriginalPositionInMap(TMXTiledMap* Map,const std::string& strPlace);

	bool init() override;

	int getArea() const { return m_Area; }

	void setArea(int Area) { m_Area = Area; }

	virtual void beAttacked(const float& Damage) = 0;

	virtual void Death() = 0;

	ProgressView* m_Blood;

protected:
	Sprite* m_Body;

	/* À˘ Ù«¯”Ú */
	int m_Area = 0;
};

#endif

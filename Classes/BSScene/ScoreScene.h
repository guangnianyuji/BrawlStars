#ifndef __SCORESCENE_H__
#define __SCORESCENE_H__

#include "BSScene\BaseScene.h"
#include "BSScene\StartScene.h"
#include "cocos2d.h"

class ScoreScene :public BaseScene
{
public:
	static ScoreScene* create(int rank);

	
private:
     bool virtual init() override;

	 int m_Rank;

	
};

#endif // !__SCORESCENE_H__


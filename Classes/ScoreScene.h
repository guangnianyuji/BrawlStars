#ifndef __SCORESCENE_H__
#define __SCORESCENE_H__

#include "BSScene\BaseScene.h"

class ScoreScene :public BaseScene
{
public:
	static ScoreScene* create(int rank);

	bool virtual init() override;
private:
	
};

#endif // !__SCORESCENE_H__


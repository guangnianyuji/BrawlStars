#include "AnimationUtils.h"
#include "cocos2d.h"

using namespace cocos2d;

Animate* AnimationUtils::createAnimation(const std::string& name, const std::string& direction)
{
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();

	std::string strPlistName = name +"/"+ name + ".plist";
	std::string strPhotoName = name + "/"+ name + ".png";

	cache->addSpriteFramesWithFile(strPlistName,strPhotoName);

	Vector<SpriteFrame*> frameVec;
	SpriteFrame* frame = NULL;
	for (int ix = 1; ix <= 4; ix++)
	{
		frame = cache->getSpriteFrameByName(name+direction+Value(ix).asString()+".png");
		if (frame == NULL)
			break;

		frameVec.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(frameVec, 1.0f / 60);
	Animate* animate = Animate::create(animation);
	return animate;
};
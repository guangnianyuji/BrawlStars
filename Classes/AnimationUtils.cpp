#include "AnimationUtils.h"
#include "cocos2d.h"

using namespace cocos2d;

/* 创建角色F四向行走时的动画 */
Animate* AnimationUtils::createAnimation(const std::string& name, const std::string& direction)
{
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();

	std::string strPlistName = name +"/"+ name + ".plist";
	std::string strPhotoName = name + "/"+ name + ".png";

	cache->addSpriteFramesWithFile(strPlistName,strPhotoName);

	Vector<SpriteFrame*> frameVec;
	SpriteFrame* frame = nullptr;
	for (int ix = 1; ix <= 4; ix++)
	{
		frame = cache->getSpriteFrameByName(name+direction+Value(ix).asString()+".png");
		if (frame == nullptr)
			break;

		frameVec.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(frameVec, 1.0f / 5,-1);
	Animate* animate = Animate::create(animation);
	return animate;
}

/* 创建普通攻击动画 */
Animate* AnimationUtils::createNormalAttackAnimation(const std::string& name)
{
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();

	std::string strPlistName = name + "/" + "Normal_Attack" +"/"+"Normal_Attack"+".plist";
	std::string strPhotoName = name + "/" + "Normal_Attack" + "/" + "Normal_Attack" + ".png";

	cache->addSpriteFramesWithFile(strPlistName, strPhotoName);

	Vector<SpriteFrame*> frameVec;
	SpriteFrame* frame = nullptr;
	for (int ix = 0; ix <= 14; ix++)
	{
		frame = cache->getSpriteFrameByName("1_" + Value(ix).asString() + ".png");
		if (frame == nullptr)
			break;

		frameVec.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(frameVec, 1.0f / 5, -1);
	Animate* animate = Animate::create(animation);
	return animate;
}

Animate* AnimationUtils::createSkillAnimation(const std::string& name)
{
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();

	std::string strPlistName = name + "/" + "Skill" + "/" + "Skill" + ".plist";
	std::string strPhotoName = name + "/" + "Skill" + "/" + "Skill" + ".png";

	cache->addSpriteFramesWithFile(strPlistName, strPhotoName);

	Vector<SpriteFrame*> frameVec;
	SpriteFrame* frame = nullptr;
	for (int ix = 0; ix <= 60; ix++)
	{
		frame = cache->getSpriteFrameByName( Value(ix).asString() + ".png");
		if (frame == nullptr)
			break;

		frameVec.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(frameVec, 1.0f / 5, -1);
	Animate* animate = Animate::create(animation);
	return animate;
}

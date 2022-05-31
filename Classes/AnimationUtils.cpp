#include "AnimationUtils.h"
#include "cocos2d.h"

using namespace cocos2d;

/* ������ɫF��������ʱ�Ķ��� */
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

/* ������ͨ�������� */
Animate* AnimationUtils::createNormalAttackAnimation(const std::string& name,const int loops)
{
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();

	std::string strPlistName = name + "/Normal_Attack/" + "Normal_Attack" + ".plist";
	std::string strPhotoName = name + "/Normal_Attack/" + "Normal_Attack" + ".png";

	cache->addSpriteFramesWithFile(strPlistName, strPhotoName);

	Vector<SpriteFrame*> frameVec;
	SpriteFrame* frame = nullptr;
	for (int ix = 1; ix <= 16; ix++)
	{
		if (ix <= 9)
		{
			frame = cache->getSpriteFrameByName(name + "_0" + Value(ix).asString() + ".png");
		}
		else
		{
			frame = cache->getSpriteFrameByName(name + "_" + Value(ix).asString() + ".png");
		}
		if (frame == nullptr)
			break;

		frameVec.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(frameVec, 1.0f/20, loops);
	Animate* animate = Animate::create(animation);
	return animate;
}


Animate* AnimationUtils::createSkillAnimation(const std::string& name)
{
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();

	std::string strPlistName = name + "/Skill/" + "Skill" + ".plist";
	std::string strPhotoName = name + "/Skill/" + "Skill" + ".png";

	cache->addSpriteFramesWithFile(strPlistName, strPhotoName);

	Vector<SpriteFrame*> frameVec;
	SpriteFrame* frame = nullptr;
	for (int ix = 1; ix <= 60; ix++)
	{
		frame = cache->getSpriteFrameByName( Value(ix).asString() + ".png");
		if (frame == nullptr)
			break;

		frameVec.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(frameVec, 1.0f / 60, -1);
	Animate* animate = Animate::create(animation);
	return animate;
}

Animate* AnimationUtils::createAceAnimation(const std::string& name)
{
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();

	std::string strPlistName = name + "/Ace/" + "Ace" + ".plist";
	std::string strPhotoName = name + "/Ace/" + "Ace" + ".png";

	cache->addSpriteFramesWithFile(strPlistName, strPhotoName);

	Vector<SpriteFrame*> frameVec;
	SpriteFrame* frame = nullptr;
	for (int ix = 1; ix <= 60; ix++)
	{
		frame = cache->getSpriteFrameByName(Value(ix).asString() + ".png");
		if (frame == nullptr)
			break;

		frameVec.pushBack(frame);
	}
	Animation* animation = Animation::createWithSpriteFrames(frameVec, 1.0f / 60, -1);
	Animate* animate = Animate::create(animation);
	return animate;

	return animate;
}

#ifndef __PROGRESS_VIEW__
#define __PROGRESS_VIEW__

#include "cocos2d.h"
#include "Character.h"

class ProgressView:public cocos2d::Node
{
public:

	virtual bool init() override;

	/* 设置血条背景 */
	void setBackgroundTexture(const char* fileName);

	/* 设置血条背景 */
	void setForegroundTexture(const char* fileName);

	/* 设置总血量 */
	void setBloodVolume(float total);

	/* 设置当前血量 */
	void setRealTimeBlood(float progress);

	/* 得到当前血量 */
	float getRealTimeBlood() const;

	/* 得到总血量 */
	float getBloodVolume() const;

	CREATE_FUNC(ProgressView);

private:

	/* 设置前景血条显示的长度 */
	void setForegroundTectureRect(const cocos2d::Rect& rect);

private:

	cocos2d::Sprite* m_BloodBackground;

	cocos2d::Sprite* m_BloodForeground;

	float m_BloodVolume;

	float m_RealTimeVolume;

	float m_Scale;
};

#endif


#ifndef __PROGRESS_VIEW__
#define __PROGRESS_VIEW__

#include "cocos2d.h"
#include "Character.h"

class ProgressView:public cocos2d::Node
{
public:

	virtual bool init() override;

	/* ����Ѫ������ */
	void setBackgroundTexture(const char* fileName);

	/* ����Ѫ������ */
	void setForegroundTexture(const char* fileName);

	/* ������Ѫ�� */
	void setBloodVolume(float total);

	/* ���õ�ǰѪ�� */
	void setRealTimeBlood(float progress);

	/* �õ���ǰѪ�� */
	float getRealTimeBlood() const;

	/* �õ���Ѫ�� */
	float getBloodVolume() const;

	CREATE_FUNC(ProgressView);

private:

	/* ����ǰ��Ѫ����ʾ�ĳ��� */
	void setForegroundTectureRect(const cocos2d::Rect& rect);

private:

	cocos2d::Sprite* m_BloodBackground;

	cocos2d::Sprite* m_BloodForeground;

	float m_BloodVolume;

	float m_RealTimeVolume;

	float m_Scale;
};

#endif


#include "ProgressView.h"

bool ProgressView::init()
{
	setBackgroundTexture("ui/Blood_Background.png");

	setForegroundTexture("ui/Blood_Foreground.png");

	return true;
}

void ProgressView::setBackgroundTexture(const char* fileName)
{
	m_BloodBackground = cocos2d::Sprite::create(fileName);

	this->addChild(m_BloodBackground);
}

void ProgressView::setForegroundTexture(const char* fileName)
{
	m_BloodForeground = cocos2d::Sprite::create(fileName);

	this->addChild(m_BloodForeground);

	m_BloodForeground->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));

	m_BloodForeground->setPosition(Vec2(m_BloodBackground->getContentSize().width / 2, 0));

	this->addChild(m_BloodForeground);
}

void ProgressView::setBloodVolume(float total)
{
	if (m_BloodForeground == nullptr)
	{
		return;
	}
	m_Scale = m_BloodForeground->getContentSize().width / total;

	m_BloodVolume = total;

	m_RealTimeVolume = total;
}

void ProgressView::setRealTimeBlood(float progress)
{
	if (m_BloodForeground == nullptr)
	{
		return;
	}
	if (progress < 0.0f) { progress = 0.0f; }
	else if (progress > m_BloodVolume) { progress = m_BloodVolume; }
	
	m_RealTimeVolume = progress;

	float rectWidth = progress * m_Scale;

	const cocos2d::Point from= m_BloodForeground->getTextureRect().origin;

	const cocos2d::Rect rect = CCRectMake(from.x, from.y, rectWidth, m_BloodForeground->getContentSize().height);

	setForegroundTectureRect(rect);
}

void ProgressView::setForegroundTectureRect(const cocos2d::Rect& rect)
{
	m_BloodForeground->setTextureRect(rect);
}

float ProgressView::getRealTimeBlood() const
{
	return m_RealTimeVolume;
}

float ProgressView::getBloodVolume() const
{
	return m_BloodVolume;
}


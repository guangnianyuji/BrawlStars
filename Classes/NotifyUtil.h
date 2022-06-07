#ifndef __NOTIFY_UTIL__
#define __NOTIFY_UTIL__

#include "cocos2d.h"

/* ʵ�ּ򵥵Ĺ۲��ߣ��������� */
class NotifyUtil:public cocos2d::Ref
{
private:

	NotifyUtil();
	~NotifyUtil();

public:
	static NotifyUtil* getInstance();

	CREATE_FUNC(NotifyUtil);

	virtual bool init();

	/* ������Ϣ */
	void addObserver(const std::string& sMsgName, std::function<void(cocos2d::Point)> func);

	/* ������Ϣ */
	void addObserver(const std::string& sMsgName, std::function<void(cocos2d::Ref*)> func);

	/* ������Ϣ */
	void postNotification(const std::string& sMsgName, cocos2d::Point entityPosition);

	/* ������Ϣ */
	void postNotification(const std::string& sMsgName, cocos2d::Ref* data);

	/* ȡ������ */
	void removeObserver(const std::string& sMsgName, std::function<void(cocos2d::Point)> func);

	/* ȡ������ */
	void removeObserver(const std::string& sMsgName, std::function<void(cocos2d::Ref*)> func);

private:
	static NotifyUtil* m_Instance;

	std::map<std::string, std::vector<std::function<void(cocos2d::Point)>>> m_funcMap1;

	std::map < std::string, std::vector < std::function<void(cocos2d::Ref*)>> > m_funcMap2;


};

#endif
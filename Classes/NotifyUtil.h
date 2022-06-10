#ifndef __NOTIFY_UTIL__
#define __NOTIFY_UTIL__

#include "cocos2d.h"


class Hero;
class Box;

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
	void addObserver(const std::string& sMsgName, std::function<void(Hero*)> func);

	/* ������Ϣ */
	void addObserver(const std::string& sMsgName, std::function<void(cocos2d::Ref*)> func);

	/* ������Ϣ */
	void addObserver(const std::string& sMsgName, std::function<void(Box*)> func);

	/* ������Ϣ */
	void postNotification(const std::string& sMsgName, Hero*);

	/* ������Ϣ */
	void postNotification(const std::string& sMsgName, Box*);

	/* ������Ϣ */
	void postNotification(const std::string& sMsgName, cocos2d::Ref* data);

	/* ȡ������ */
	void removeObserver(const std::string& sMsgName, std::function<void(Hero*)> func);

	/* ȡ������ */
	void removeObserver(const std::string& sMsgName, std::function<void(cocos2d::Ref*)> func);

	/* ȡ������ */
	void removeObserver(const std::string& sMsgName, std::function<void(cocos2d::Point)> func);

private:
	static NotifyUtil* m_Instance;

	std::map < std::string, std::vector<std::function<void(Hero*)>> > m_funcMap1;

	std::map < std::string, std::vector < std::function<void(cocos2d::Ref*)>> > m_funcMap2;

	std::map < std::string, std::vector < std::function<void(Box*)>> >m_funcMap3;
};

#endif
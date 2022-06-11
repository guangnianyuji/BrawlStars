#ifndef __NOTIFY_UTIL__
#define __NOTIFY_UTIL__

#include "cocos2d.h"


class Hero;
class Box;

/* 实现简单的观察者，满足需求 */
class NotifyUtil:public cocos2d::Ref
{
private:

	NotifyUtil();
	~NotifyUtil();

public:
	static NotifyUtil* getInstance();

	CREATE_FUNC(NotifyUtil);

	virtual bool init();

	/* 订阅消息 */
	void addObserver(const std::string& sMsgName, std::function<void(Hero*)> func);

	/* 订阅消息 */
	void addObserver(const std::string& sMsgName, std::function<void(cocos2d::Ref*)> func);

	/* 订阅消息 */
	void addObserver(const std::string& sMsgName, std::function<void(Box*)> func);

	/* 发布消息 */
	void postNotification(const std::string& sMsgName, Hero*);

	/* 发布消息 */
	void postNotification(const std::string& sMsgName, Box*);

	/* 发布消息 */
	void postNotification(const std::string& sMsgName, cocos2d::Ref* data);

	/* 取消订阅 */
	void removeObserver(const std::string& sMsgName, std::function<void(Hero*)> func);

	/* 取消订阅 */
	void removeObserver(const std::string& sMsgName, std::function<void(cocos2d::Ref*)> func);

	/* 取消订阅 */
	void removeObserver(const std::string& sMsgName, std::function<void(cocos2d::Point)> func);

private:
	static NotifyUtil* m_Instance;

	std::map < std::string, std::vector<std::function<void(Hero*)>> > m_funcMap1;

	std::map < std::string, std::vector < std::function<void(cocos2d::Ref*)>> > m_funcMap2;

	std::map < std::string, std::vector < std::function<void(Box*)>> >m_funcMap3;
};

#endif
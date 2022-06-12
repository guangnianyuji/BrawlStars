#include "Util/NotifyUtil.h"

NotifyUtil* NotifyUtil::m_Instance = nullptr;

NotifyUtil::NotifyUtil()
{

}

NotifyUtil::~NotifyUtil()
{
}

NotifyUtil* NotifyUtil::getInstance()
{
	if (m_Instance == nullptr)
	{
		m_Instance = NotifyUtil::create();
		m_Instance->retain();
	}
	return m_Instance;
}

bool NotifyUtil::init()
{
	return true;
}

void NotifyUtil::addObserver(const std::string& sMsgName, std::function<void(Hero*)> func)
{
	if (m_funcMap1.find(sMsgName) != m_funcMap1.end())
	{
		std::vector<std::function<void(Hero*)>>  &funcList = m_funcMap1.at(sMsgName);
		funcList.push_back(func);

	}
	else
	{
		std::vector<std::function<void(Hero*)>> funcList;

		funcList.push_back(func);

		m_funcMap1[sMsgName] = funcList;
	}
}
void NotifyUtil::addObserver(const std::string& sMsgName, std::function<void(cocos2d::Ref*)> func)
{
	if (m_funcMap2.find(sMsgName) != m_funcMap2.end())
	{
		std::vector<std::function<void(cocos2d::Ref*)>>& funcList = m_funcMap2.at(sMsgName);
		funcList.push_back(func);

	}
	else
	{
		std::vector<std::function<void(cocos2d::Ref*)>> funcList;

		funcList.push_back(func);

		m_funcMap2[sMsgName] = funcList;
	}
}

void NotifyUtil::addObserver(const std::string& sMsgName, std::function<void(Box*)> func)
{
	if (m_funcMap3.find(sMsgName) !=m_funcMap3.end())
	{
		std::vector<std::function<void(Box*)>>& funcList =m_funcMap3.at(sMsgName);
		funcList.push_back(func);

	}
	else
	{
		std::vector<std::function<void(Box*)>> funcList;

		funcList.push_back(func);

		m_funcMap3[sMsgName] = funcList;
	}
}

void NotifyUtil::postNotification(const std::string& sMsgName, Hero* target)
{
	if (m_funcMap1.find(sMsgName) != m_funcMap1.end())
	{
		std::vector<std::function<void(Hero*)>> funcList = m_funcMap1.at(sMsgName);

		for (auto& func : funcList)
		{
			func(target);
		}
	}
}

void NotifyUtil::postNotification(const std::string& sMsgName, cocos2d::Ref* data)
{
	if (m_funcMap2.find(sMsgName) != m_funcMap2.end())
	{
		std::vector<std::function<void(cocos2d::Ref*)>> funcList = m_funcMap2.at(sMsgName);

		for (auto& func : funcList)
		{
			func(data);
		}
	}
}

void NotifyUtil::postNotification(const std::string& sMsgName, Box* box)
{
	if (m_funcMap3.find(sMsgName) !=m_funcMap3.end())
	{
		std::vector<std::function<void(Box*)>> funcList =m_funcMap3.at(sMsgName);

		for (auto& func : funcList)
		{
			func(box);
		}
	}
}

void NotifyUtil::removeObserver(const std::string& sMsgName, std::function<void(Hero*)> func)
{
	if (m_funcMap1.find(sMsgName) != m_funcMap1.end())
	{
		std::vector<std::function<void(Hero*)>> funcList = m_funcMap1.at(sMsgName);

		
	}
}

void NotifyUtil::removeObserver(const std::string& sMsgName, std::function<void(cocos2d::Ref*)> func)
{

}


#include "SocketDataManager.h"

SocketDataManager* SocketDataManager::bsSocketDataManager = nullptr;

SocketDataManager::SocketDataManager()
{
}
SocketDataManager::~SocketDataManager()
{
}

SocketDataManager* SocketDataManager::getInstance()
{
	if (bsSocketDataManager == nullptr)
	{
		bsSocketDataManager = SocketDataManager::create();
		bsSocketDataManager->retain();
	}

	return bsSocketDataManager;
}

bool SocketDataManager::init()
{
	Director::getInstance()->getScheduler()->schedule(
		schedule_selector(SocketDataManager::update),
		this, 0.108f, false);
	return true;
}

void SocketDataManager::update(float dt)
{
	bsMutex.lock();

	for (auto value : bsMsgList)
	{
		log("rev: %s", value.asString().c_str());
	}

	bsMsgList.clear();

	bsMutex.unlock();
}

void SocketDataManager::pushMsg(const char* msg)
{
	bsMutex.lock();

	bsMsgList.push_back(Value(msg));

	bsMutex.unlock();
}
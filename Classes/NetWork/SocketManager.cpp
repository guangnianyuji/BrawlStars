#include "SocketManager.h"
//???
SocketManager* SocketManager::bsSocketManager = nullptr;

SocketManager::SocketManager()
{
}

SocketManager::~SocketManager()
{
}

SocketManager* SocketManager::getInstance()
{
	if (bsSocketManager == nullptr)
	{
		bsSocketManager = SocketManager::create();
		bsSocketManager->retain();
	}

	return bsSocketManager;
}

bool SocketManager::init()
{
	return false;
}

void SocketManager::startConnectSever()
{
	if (connectServer() == true)
	{
		std::thread receiveThread = std::thread(&SocketManager::receiveData, this);
		receiveThread.detach();
	}
}

bool SocketManager::connectServer()
{
	return true;
}




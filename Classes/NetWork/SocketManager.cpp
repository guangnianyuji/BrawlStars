#include "SocketManager.h"

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
	return true;
}

void SocketManager::start()
{
	if (connectServer() == true)
	{
		/* �������̣߳��������� */
		std::thread receiveThread = std::thread(&SocketManager::receiveData, this);
		receiveThread.detach();
	}
}

bool SocketManager::connectServer()
{
	/* ����һ��Socket */

	/* ע��������Ҫ��Ӱ�ȫ����*/
	/* Init��Ҫ�ǽ����ƽ̨����*/
	bsSocket.Init();

	bsSocket.Create(AF_INET, SOCK_STREAM, 0);

	const char* ip = "127.0.0.1";
	int port = 8888;

	bool result = bsSocket.Connect(ip, port);

	int retryTimes = 0;
	while (result == false && retryTimes < 7)
	{
		log("retry connecting...");
		result = bsSocket.Connect(ip, port);
		retryTimes++;

#if (CC_TARGET_PLATFORM==CC_PLATFORM_WIN32)
		Sleep(500);
#else
		usleep(500);
#endif
	}
	if (result)
	{
		log("connect to server suc!");
	}
	else
	{
		log("can not connect to server");
	}
	return result;
}

void SocketManager::receiveData()
{
	while (true)
	{
		char recvBuf[MAX_LEN] = "";
		int iResult = bsSocket.Recv(recvBuf, MAX_LEN, 0);
		if (iResult <= 0)
		{
			break;
		}

		/* ����Ϣ�ŵ������У��ȴ����� */
		SocketDataManager::getInstance()->pushMsg(recvBuf);

#if (CC_TARGET_PLATFORM==CC_PLATFORM_WIN32)
		Sleep(20);
#else
		usleep(20);
#endif
	}
	
}
/* ��������Ҳ�����������̣߳�
	�ȽϺõ������ǰ�Ҫ���͵����ݱ��浽һ���б��
	Ȼ�������߳����������͡�*/
void SocketManager::sendMsg(const char* msg)
{
	if (bsSocket.Send(msg, sizeof(msg)) == -1)
	{
		log("����ʧ�ܣ�");
	}
}




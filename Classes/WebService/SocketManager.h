#include "cocos2d.h"
#include<ODSocket/ODSocket.h>
USING_NS_CC;

class SocketManager:public Ref
{
public:
	SocketManager();
	~SocketManager();
	static SocketManager* getInstance();
	CREATE_FUNC(SocketManager);
	virtual bool init();

	void startConnectSever();
	void sendMsg(const char* msg);
private:

	static SocketManager* bsSocketManager;

	ODSocket bsSocket;

	bool connectServer();
	void receiveData();
};

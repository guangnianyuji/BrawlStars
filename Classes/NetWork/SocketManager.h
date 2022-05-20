
#include "cocos2d.h"
#include<ODSocket/ODSocket.h>
#include "SocketDataManager.h"

USING_NS_CC;

#define MAX_LEN 512

class SocketManager:public Ref
{
public:
	SocketManager();
	~SocketManager();
	static SocketManager* getInstance();
	CREATE_FUNC(SocketManager);
	virtual bool init();

	void start();
	void sendMsg(const char* msg);

private:

	static SocketManager* bsSocketManager;

	ODSocket bsSocket;

	bool connectServer();
	void receiveData();
};

/* 主要用来保存接收到的数据，然后在主线程里处理这些数据 */
#include "cocos2d.h"
#include<ODSocket/ODSocket.h>

USING_NS_CC;

class SocketDataManager :public Ref
{
public:
	SocketDataManager();
	~SocketDataManager();
	static SocketDataManager* getInstance();
	CREATE_FUNC(SocketDataManager);
	virtual bool init();

	virtual void update(float dt);

	void pushMsg(const char* msg);

private:
	static SocketDataManager* bsSocketDataManager;

	std::mutex bsMutex;

	ValueVector bsMsgList;

};
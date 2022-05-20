/* ��Ҫ����������յ������ݣ�Ȼ�������߳��ﴦ����Щ���� */
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
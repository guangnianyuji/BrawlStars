#include "Box.h"


Box* Box::create()
{
	Box* pRet = new(std::nothrow)Box();

	if (pRet && pRet->init()) {
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = nullptr;
		return nullptr;
	}
}
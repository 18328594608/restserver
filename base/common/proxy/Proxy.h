#pragma once
#include "msg/Msg.h"
#include <list>
class CProxy
{
public:
	CProxy();
	virtual ~CProxy();
public:
	static void sendToPraseServer(CMsgPtr spMsg);
	static void sendToWsServer(CMsgPtr spMsg);
	static void sendToWsServer(std::shared_ptr<std::list<CMsgPtr>> spMsgList);
	static void sendToCoreServer(CMsgPtr spMsg);
	static void sendToCoreServer(std::shared_ptr<std::list<CMsgPtr>> spMsgList);
};


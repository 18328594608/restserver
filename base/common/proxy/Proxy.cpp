#include "Proxy.h"
#include "server/wsServer.h"
#include "server/PraseServer.h"
#include "server/CoreServer.h"

CProxy::CProxy()
{
}


CProxy::~CProxy()
{
}


void CProxy::sendToPraseServer(CMsgPtr spMsg)
{
	Instance(CPraseServer)->receive(spMsg);
}

void CProxy::sendToWsServer(CMsgPtr spMsg)
{
	Instance(CWsServer)->receive(spMsg);
}

void CProxy::sendToWsServer(std::shared_ptr<std::list<CMsgPtr>> spMsgList)
{
	Instance(CWsServer)->receive(spMsgList);
}

void CProxy::sendToCoreServer(CMsgPtr spMsg)
{
	Instance(CCoreServer)->receive(spMsg);
}

void CProxy::sendToCoreServer(std::shared_ptr<std::list<CMsgPtr>> spMsgList)
{
	Instance(CCoreServer)->receive(spMsgList);
}


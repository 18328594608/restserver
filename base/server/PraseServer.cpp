#include "PraseServer.h"
#include "msg/ReqMsg.h"
//#include "base/common/protocolHdl/ProtocolHdl.h"
#include "common/proxy/Proxy.h"
CPraseServer::CPraseServer()
{
}


CPraseServer::~CPraseServer()
{
}

bool CPraseServer::_init()
{
	return true;
}

void CPraseServer::_run(void * param, int nPos)
{
	CReqMsgPtr spMsg = std::dynamic_pointer_cast<CReqMsg>(_msgPop(nPos));
	if (!spMsg)
	{
		return;
	}

	//CProtocolHdl ptclHdl(spMsg);
	//CProtocolPtr pctl = ptclHdl.handle();
	//_sendMsg(std::static_pointer_cast<CMsg>(pctl));
}

void CPraseServer::_pre_end()
{
}

void CPraseServer::_end()
{
}

bool CPraseServer::_sendMsg(CMsgPtr spMsg)
{
	CProxy::sendToCoreServer(spMsg);
	return true;
}

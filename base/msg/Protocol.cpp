#include "Protocol.h"
#include "base/common/log/log.h"
#include "admin\WsAdmin.h"
#include "base/common/tool\Tool.h"
CProtocol::CProtocol():_m_bEcho(false),_m_sendtoClient(true)
{
}


CProtocol::~CProtocol()
{
}

CRspMsgPtr CProtocol::todo(void* pParam)
{
	FUNLOG;
	deal(pParam);
	//组包一个JSOn
	Json::Value rspValue;
	Json::FastWriter writer;
	std::string rsp;

	if (_m_code == 2)
	{
		_m_msg = "Common error";
	}

	rspValue["code"] = _m_code;
	rspValue["message"] = _m_msg;
	rspValue["cmd"] = _m_cmd;
	rspValue["comment"] = _m_comment;
	if (rspValue["code"] == 0)
	{
		rspValue["data"] = _m_rspJson;
	}
	if (_m_bEcho)
	{
		rspValue["request"] = *(_m_spReqJson);
	}

	rsp = writer.write(rspValue);

	CRspMsgPtr spRspMsg = std::make_shared<CRspMsg>();
	spRspMsg->setWebsocketHdl(_m_hdl);
	spRspMsg->setUuid(_m_uuid);
	spRspMsg->setMsg(rsp);

	return spRspMsg;
}

bool CProtocol::_tokenIsValid(std::string token)
{
	FUNLOG;
	std::string hex16 =token.substr(17, 8);
	int login = strtol(hex16.c_str(), NULL, 16);
	return verifyToken(token, login);
}

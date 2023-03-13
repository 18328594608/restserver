#pragma once
#include "Msg.h"
#include "..\common\jsoncpp\jsonRead.h"
#include "base\msg\RspMsg.h"
#include "base/common/log/log.h"
class CProtocol :
	public CMsg
{
public:
	CProtocol();
	virtual ~CProtocol();
	CRspMsgPtr todo(void* pParam);

	void setReqJson(JsonPtr spJson) { 
		FUNLOG;
		_m_spReqJson = spJson; }
	JsonPtr getReqJson() {
		FUNLOG;
		return _m_spReqJson; }

	virtual bool prase() { return true; }
	virtual void deal(void* pParam) {}

	void setCmd(std::string cmd) {
		FUNLOG;
		_m_cmd = cmd; }
	std::string getCmd() {
		FUNLOG;
		return _m_cmd; }

	Json::Value& getRspJson() {
		FUNLOG;
		return _m_rspJson;}

	void setEcho(bool echo) {
		FUNLOG;
		_m_bEcho = echo; }
	bool getEcho() {
		FUNLOG;
		return _m_bEcho; }

	void setComment(std::string comment) {
		FUNLOG;
		_m_comment = comment; }
	std::string getComment() {
		FUNLOG;
		return _m_comment; }
	
	void setSendtoClient(bool sendtoClient) {
		FUNLOG;
		_m_sendtoClient = sendtoClient;}
	bool getSendtoClient() { 
		FUNLOG;
		return _m_sendtoClient; }

protected:
	bool _tokenIsValid(std::string token);
protected:
	JsonPtr _m_spReqJson;
	Json::Value _m_rspJson;
	std::string _m_cmd;
	bool _m_bEcho;
	bool _m_sendtoClient;//�Ƿ���Ҫ��ͻ��˽��лر���־
	std::string _m_comment;
};

typedef std::shared_ptr<CProtocol> CProtocolPtr;
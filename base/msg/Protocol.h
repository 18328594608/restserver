#pragma once
#include "Msg.h"
#include "wfrest/Json.h"
#include "msg/RspMsg.h"
#include "Log.h"
class CProtocol :
	public CMsg
{
public:
	CProtocol();
	virtual ~CProtocol();
	CRspMsgPtr todo(void* pParam);

	void setReqJson(Json spJson) {
		_m_spReqJson = spJson; }

    Json getReqJson() {
		return _m_spReqJson; }

	virtual bool prase() { return true; }
	virtual void deal(void* pParam) {}

	void setCmd(std::string cmd) {
		_m_cmd = cmd; }
	std::string getCmd() {
		return _m_cmd; }

    Json::Object& getRspJson() {
		return _m_rspJson;}

	void setEcho(bool echo) {
		_m_bEcho = echo; }
	bool getEcho() {
		return _m_bEcho; }

	void setComment(std::string comment) {
		_m_comment = comment; }
	std::string getComment() {
		return _m_comment; }
	
	void setSendtoClient(bool sendtoClient) {
		_m_sendtoClient = sendtoClient;}
	bool getSendtoClient() { 
		return _m_sendtoClient; }

protected:
	bool _tokenIsValid(std::string token);
protected:
    Json::Object _m_spReqJson;
    Json::Object _m_rspJson;
	std::string _m_cmd;
	bool _m_bEcho;
	bool _m_sendtoClient;//是否进行服务端回包
	std::string _m_comment;
};

typedef std::shared_ptr<CProtocol> CProtocolPtr;
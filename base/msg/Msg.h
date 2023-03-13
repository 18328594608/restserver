#pragma once
#include <string>
#include <memory>
#include "wfrest/Json.h"
typedef std::weak_ptr<void> websocket_hdl;
typedef std::shared_ptr<void> websocket_spHdl;
using namespace wfrest;
enum msg_errcode
{
	ok = 0,
	prase_err = 1001, // ��������
	protocol_err, // Э�����
	login_err, // --
	open_err, // �ҵ�ʧ��
	close_err, // ƽ��ʧ�ܣ�����
	symbol_err, // Ʒ�ֲ�����
	chart_err, // --
	close_time_err, // ����ʱ�䣬���ܽ���
	position_err, // �ֲ�������������
	token_err, // ��Чtoken
	mt4_conn_err, // mt4����ʧ��
	volume_err, // ��������ȷ
	balance_err, // ��������
	prohibit_err, // ��ֹ����
	follow_err, // ���¸����б�ʧ��
	operator_err, // ��������Ƶ��
	sign_err, // ��ǩʧ��
	sltp_err, // ֹӯֹ�����ô���
	order_err // ����������
};


class CMsg
{
public:
	CMsg();
	virtual ~CMsg();
public:
	virtual std::string getMsg() { return _m_msg;}
	virtual int getErrCode() {  return _m_code; }
	void setErrCode(int errCode) {  _m_code = errCode; }
	void setMsg(std::string str) { _m_msg = str; }

	void setWebsocketHdl(websocket_hdl hdl) {  _m_hdl = hdl; }
	websocket_hdl getWebsocketHdl() {  return _m_hdl; }

	void setUuid(std::string uuid) {  _m_uuid = uuid; }
	std::string getUuid() {  return _m_uuid; }

	virtual void putIntoDb() {}

	void setLogPrint(bool bLogPrint) {  _m_logPrint = bLogPrint; }
	bool getLogPrint() {  return _m_logPrint; }

	void setJson(Json::Object json) { _m_json = json; }
    Json::Object getJson() {  return _m_json; }
protected:
	std::string _m_msg;
	int _m_code;
	std::string _m_uuid;
	websocket_hdl _m_hdl;
	bool _m_logPrint;
	Json _m_json;
};

typedef std::shared_ptr<CMsg> CMsgPtr;
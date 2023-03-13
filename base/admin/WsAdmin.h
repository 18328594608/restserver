#pragma once
#include "Admin.h"
#include "../msg/Msg.h"
#include <unordered_map>
class CWsClientInfo
{
public:
	CWsClientInfo();
	~CWsClientInfo() {}
public:
	void setLogin(int login) { __m_login = login; }
	int getLogin() {  return __m_login; }

	void setToken(std::string token) { __m_token = token; }
	std::string getToken() {  return __m_token; }

	int who() {  return __m_login; }

	bool getSubTick() {  return __m_bSubTick; }
	int getSpectick(std::string tickstring);//判断是否行情推送
	void setSubTick(bool bSubTick) {  __m_bSubTick = bSubTick; }
	void SetSpectick(std::string Spectick) { __m_fork = true; __m_spectick = Spectick; }
	void setIntervalTicks(std::string symbols) { __m_fork = true; __m_intervalTicks = symbols; }
	void setSubscribeTick(std::string symbol) { __m_fork = true; __m_subscribeTick = symbol; }

	void setPump(bool bPump){  __m_bPump = bPump; }
	bool getPump() {  return __m_bPump; }

	void setGroup(std::string group) { __m_group = group; }
	std::string getGroup() {  return __m_group; }
	
private:
	int __m_login;
	std::string __m_token;
	bool __m_bPump;
	std::string __m_group;

	bool __m_bSubTick;
	std::string __m_spectick;
	std::string __m_intervalTicks;
	std::string __m_subscribeTick;
	bool __m_fork;
};

class CWsAdmin:
	public CAdmin<websocket_spHdl, CWsClientInfo>
{
public:
	CWsAdmin();
	virtual ~CWsAdmin();
public:
	bool controlTradeInterval(int login);//false表示间隔小于0.5s，不允许下单
	void setSubTick(websocket_spHdl sphdl, bool bSubTick); // 行情订阅开关
	void SetSpectick(websocket_spHdl sphdl, std::string Spectick); // 列表行情订阅
	void setIntervalTicks(websocket_spHdl sphdl, std::string symbol); // 列表行情订阅
	void setSubscribeTick(websocket_spHdl sphdl, std::string symbol); // 单个行情订阅
	void setUnsubscribeTick(websocket_spHdl sphdl); // 单个行情取消订阅
	void addSubOpenClient(websocket_spHdl sphdl, std::string symbol); // 订阅开平仓订单
	void removeSubOpenClient(websocket_spHdl sphdl); // 取消订阅开平仓订单
	std::map<websocket_spHdl, std::string> getSubOpenClients() { return __m_subOpenOrderClients; }
private:
	std::mutex __m_lastTradeTimeMtx;
	std::unordered_map<int, time_t> __m_lastTradeTime;//login的最后交易时间
	std::map<websocket_spHdl, std::string> __m_subOpenOrderClients; // 订阅开平仓的客户端连接
};

extern CWsAdmin gWsAdmin;
typedef std::map< websocket_spHdl, CWsClientInfo > WsClientInfos;
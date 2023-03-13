#include "WsAdmin.h"

CWsAdmin gWsAdmin;

unsigned long GetTickCount()
{
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    return now.tv_sec * 1000 + now.tv_nsec / 1000000;
}

CWsAdmin::CWsAdmin()
{
}

CWsAdmin::~CWsAdmin()
{
}

bool CWsAdmin::controlTradeInterval(int login)
{
	time_t lastTime = 0;
	{
		std::lock_guard<std::mutex> guard(__m_lastTradeTimeMtx);
		lastTime = __m_lastTradeTime[login];
	}
	time_t now = GetTickCount();
	if (abs(now - lastTime) > 500)
	{
		{
			std::lock_guard<std::mutex> guard(__m_lastTradeTimeMtx);
			__m_lastTradeTime[login] = now;
		}
		return true;
	}
	return false;
}

void CWsAdmin::setSubTick(websocket_spHdl sphdl, bool bSubTick)
{
	{
		std::lock_guard<std::mutex> guard(_m_Mtx);
		auto itor = _m_TMap.find(sphdl);
		if (itor != _m_TMap.end())
		{
			itor->second.setSubTick(bSubTick);

		}
		else
		{
		}
	}
}

// ���鶩�ĵ������ж�
int CWsClientInfo::getSpectick(std::string symbol)
{
	if (!__m_bSubTick && !__m_fork)
	{
		return 0; // ģ����,������
	}
	if (__m_subscribeTick.find(symbol) != std::string::npos)
	{
		return 3; // ��Ʒ������,ͬʱ�����ڵ�Ʒ�ֺ��б�İ���Ʒ�ֵ�Ƶ������ subTick
	}
	if (__m_intervalTicks.find(symbol) != std::string::npos)
	{
		return 1; // �б����� intervalTicks
	}
	if (__m_spectick.find(symbol) != std::string::npos && __m_intervalTicks.empty())
	{
		return 4; // �б����� spectick
	}
	if (__m_subscribeTick.empty() && __m_intervalTicks.empty() && __m_spectick.empty() && !__m_fork)
	{
		return 2; // ȫ�� tick
	}
	return 0; // ������
}

void CWsAdmin::SetSpectick(websocket_spHdl sphdl, std::string Spectick)
{
	{
		std::lock_guard<std::mutex> guard(_m_Mtx);
		auto itor = _m_TMap.find(sphdl);
		if (itor != _m_TMap.end())
		{
			itor->second.SetSpectick(Spectick);
		}
		else
		{
			//LOG_ERROR("{},û���ҵ����Ӿ��", __FUNCTION__);
		}
	}
}

void CWsAdmin::setIntervalTicks(websocket_spHdl sphdl, std::string symbol)
{
	{
		std::lock_guard<std::mutex> guard(_m_Mtx);
		auto itor = _m_TMap.find(sphdl);
		if (itor != _m_TMap.end())
		{
			itor->second.setIntervalTicks(symbol);
		}
		else
		{
			//LOG_ERROR("{},û���ҵ����Ӿ��", __FUNCTION__);
		}
	}
}

void CWsAdmin::setSubscribeTick(websocket_spHdl sphdl, std::string symbol)
{
	{
		std::lock_guard<std::mutex> guard(_m_Mtx);
		auto itor = _m_TMap.find(sphdl);
		if (itor != _m_TMap.end())
		{
			itor->second.setSubscribeTick(symbol);
		}
		else
		{
			//LOG_ERROR("{},û���ҵ����Ӿ��", __FUNCTION__);
		}
	}
}

void CWsAdmin::setUnsubscribeTick(websocket_spHdl sphdl)
{
	{
		std::lock_guard<std::mutex> guard(_m_Mtx);
		auto itor = _m_TMap.find(sphdl);
		if (itor != _m_TMap.end())
		{
			itor->second.setSubscribeTick("");
		}
		else
		{
			//LOG_ERROR("{},û���ҵ����Ӿ��", __FUNCTION__);
		}
	}
}

void CWsAdmin::addSubOpenClient(websocket_spHdl sphdl, std::string symbol)
{
	std::lock_guard<std::mutex> guard(_m_Mtx);
	__m_subOpenOrderClients[sphdl] = symbol;
}

void CWsAdmin::removeSubOpenClient(websocket_spHdl sphdl)
{
	std::lock_guard<std::mutex> guard(_m_Mtx);
	__m_subOpenOrderClients.erase(sphdl);
}

CWsClientInfo::CWsClientInfo() :__m_login(0),__m_bSubTick(false), __m_bPump(true), __m_fork(false)
{

}

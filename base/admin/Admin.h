#pragma once
#include <list>
#include <mutex>
#include <map>
#include "../Log.h"

template<class mapKey,class mapVal>
class CAdmin
{
public:
	CAdmin();
	virtual ~CAdmin();
public:
	virtual void push(mapKey key);

	virtual void push(mapKey key, mapVal val);
	virtual void pull(mapKey key);
	virtual mapVal get(mapKey key);
	virtual std::map<mapKey, mapVal> getall();
	virtual void clear();
	virtual mapKey whokey(int who);
	virtual void clearWho(mapKey key);
	virtual std::pair<int,int> size();
	virtual std::mutex * getmutex(); //需要同步时候用的2020.07.25添加
protected:
	std::mutex _m_Mtx;
	std::map<mapKey, mapVal> _m_TMap;
	std::map<int, mapKey> _m_TKey;
};

template<class mapKey, class mapVal>
inline CAdmin<mapKey, mapVal>::CAdmin()
{
}

template<class mapKey, class mapVal>
inline CAdmin<mapKey, mapVal>::~CAdmin()
{
}

template<class mapKey, class mapVal>
inline std::mutex * CAdmin<mapKey, mapVal>::getmutex()
{
	return &_m_Mtx;
}
template<class mapKey, class mapVal>
inline void CAdmin<mapKey, mapVal>::push(mapKey key)
{
	if (key)
	{
		std::lock_guard<std::mutex> guard(_m_Mtx);
		_m_TMap[key] = mapVal();
	}
}

template<class mapKey, class mapVal>
inline void CAdmin<mapKey, mapVal>::push(mapKey key, mapVal val)
{
	if (key)
	{
		std::lock_guard<std::mutex> guard(_m_Mtx);
		_m_TMap[key] = val;
		if (val.who())
		{
			_m_TKey[val.who()] = key;
		}
		LOG_INFO("a conn[{}|login:{}] is logined", key.get(),val.who());
	}
}

template<class mapKey, class mapVal>
inline void CAdmin<mapKey, mapVal>::pull(mapKey key)
{
	if (!key)
	{
		return;
	}
	std::lock_guard<std::mutex> guard(_m_Mtx);
	{
		int who = 0;
		auto itor = _m_TMap.find(key);
		if (itor != _m_TMap.end())
		{
			who = itor->second.who();
			LOG_INFO("a conn[{}|login:{}] is closed", key.get(),itor->second.who());
			_m_TMap.erase(itor);
		}
		_m_TKey.erase(who);
	}
}

template<class mapKey, class mapVal>
inline mapVal CAdmin<mapKey, mapVal>::get(mapKey key)
{
	if (!key)
	{
		return mapVal();
	}
	std::lock_guard<std::mutex> guard(_m_Mtx);
	{
		auto itor = _m_TMap.find(key);
		if (itor != _m_TMap.end())
		{
			return itor->second;
		}
		return mapVal();
	}
}

template<class mapKey, class mapVal>
inline std::map<mapKey, mapVal> CAdmin<mapKey, mapVal>::getall()
{
	std::lock_guard<std::mutex> guard(_m_Mtx);
	return _m_TMap;
}

template<class mapKey, class mapVal>
inline void CAdmin<mapKey, mapVal>::clear()
{
	std::lock_guard<std::mutex> guard(_m_Mtx);
	_m_TMap.clear();
	_m_TKey.clear();
}

template<class mapKey, class mapVal>
inline mapKey CAdmin<mapKey, mapVal>::whokey(int who)
{
	std::lock_guard<std::mutex> guard(_m_Mtx);
	auto it = _m_TKey.find(who);
	if (it != _m_TKey.end())
	{
		return it->second;
	}
	return mapKey();
}

template<class mapKey, class mapVal>
inline void CAdmin<mapKey, mapVal>::clearWho(mapKey key)
{
	std::lock_guard<std::mutex> guard(_m_Mtx);
	auto it = _m_TMap.find(key);
	if (it != _m_TMap.end())
	{
		it->second = mapVal();
	}
	for (auto it = _m_TKey.begin(); it != _m_TKey.end(); it++)
	{
		if (it->second == key)
		{
			_m_TKey.erase(it);
			break;
		}
	}
}

template<class mapKey, class mapVal>
inline std::pair<int, int> CAdmin<mapKey, mapVal>::size()
{
	std::lock_guard<std::mutex> guard(_m_Mtx);
	int first = (int)_m_TMap.size();
	int second = (int)_m_TKey.size();
	return std::pair<int, int>(first, second);
}

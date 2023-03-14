#include "Server.h"
#include <assert.h>

CServer::CServer():__m_nThread(0), _m_loopTime(1000), __m_bMaintain(false),__m_maintainLoopTime(5000)
{

}


CServer::~CServer()
{
}


bool CServer::start(void* param)
{
	__m_nThread = 1;
	if (!_init())
	{
		return false;
	}

    _m_exitFlag[0] = false;
	__m_spRunThread[0] = std::make_shared<std::thread>(&CServer::__go, this, param, 0);
	if (!__m_spRunThread[0])
	{
		return false;
	}
	return true;
}

void CServer::stop()
{
	_pre_end();

	if (__m_bMaintain)
	{
        _m_maintainexitFlag[0].exchange(true);
        pthread_mutex_lock(&_m_maintainexit_mutex[0]);
        pthread_cond_signal(&_m_maintainexit_cond[0]);
        pthread_mutex_unlock(&_m_maintainexit_mutex[0]);

		__m_spMaintainThread->join();
		__m_spMaintainThread = NULL;

        pthread_mutex_destroy(&_m_maintainexit_mutex[0]);
        pthread_cond_destroy(&_m_maintainexit_cond[0]);
	}

    for (int i = 0; i < __m_nThread; i++)
    {
        if (_m_exitFlag[i].exchange(true))
        {
            continue;
        }

        pthread_mutex_lock(&_m_exit_mutex[i]);
        pthread_cond_signal(&_m_exit_cond[i]);
        pthread_mutex_unlock(&_m_exit_mutex[i]);
    }

	for (int i = 0; i < __m_nThread; i++)
	{
		if (__m_spRunThread[i])
		{
			__m_spRunThread[i]->join();
		}
        pthread_mutex_destroy(&_m_exit_mutex[i]);
        pthread_cond_destroy(&_m_exit_cond[i]);
	}

	for (int i = 0; i < __m_nThread; i++)
	{
		__m_spRunThread[i] = NULL;
	}

	_end();
}

void CServer::__go(void* param, int nTreadPos)
{
    while (!_m_exitFlag[nTreadPos])
    {
        _run(param, nTreadPos);

        struct timespec abstime;
        clock_gettime(CLOCK_REALTIME, &abstime);
        abstime.tv_sec += 1;

        pthread_mutex_lock(&_m_exit_mutex[nTreadPos]);
        pthread_cond_timedwait(&_m_exit_cond[nTreadPos], &_m_exit_mutex[nTreadPos], &abstime);
        pthread_mutex_unlock(&_m_exit_mutex[nTreadPos]);
    }
}

void CServer::__go_maintain()
{
	int loopTime = 0;
	while (!_m_maintainexitFlag[0])
	{
		loopTime = __m_maintainLoopTime;
		_maintain();
	}
}

bool CServer::receive(CMsgPtr spMsg)
{
	static u_int64_t n = 0;
	n++;
	int i = n%__m_nThread;

	{
		std::lock_guard<std::mutex> guard(_m_listLock[i]);
		_m_msgList[i].push_back(spMsg);
	}
	_m_cond[i].notify_one();
	return true;
}

bool CServer::receive(CMsgPtr spMsg, int nPos)
{
	if (nPos >= __m_nThread)
	{
		nPos = 0;
	}
	{
		std::lock_guard<std::mutex> guard(_m_listLock[nPos]);
		_m_msgList[nPos].push_back(spMsg);
	}
	_m_cond[nPos].notify_one();
	return true;
}

bool CServer::receive(std::shared_ptr<std::list<CMsgPtr>> v_spMsg)
{
	static uint64_t n = 0;
	n++;
	int i = n%__m_nThread;
	{
		std::lock_guard<std::mutex> guard(_m_listLock[i]);
		_m_msgList[i].splice(_m_msgList[i].end(), *v_spMsg);
	}
	_m_cond[i].notify_one();
	return true;
}

CMsgPtr CServer::_msgPop(int nPos)
{
	std::unique_lock<std::mutex> lock(_m_listLock[nPos]);

	while (_m_msgList[nPos].empty()) {
		_m_cond[nPos].wait_for(lock, std::chrono::milliseconds(_m_loopTime));
		if (_m_msgList[nPos].empty())
		{
			return CMsgPtr();
		}
		else
		{
			break;
		}
	}
	CMsgPtr spMsg = _m_msgList[nPos].front();
	_m_msgList[nPos].pop_front();
	return spMsg;
}

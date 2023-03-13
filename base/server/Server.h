#pragma once
#include <thread>
#include <memory>
#include "../msg/Msg.h"
#include <mutex>
#include <list>
#include "../common/pool/Pool.h"

#define MAXTHREADSIZE 32
#define Instance(T) (CServer::instance<T>())
class CServer
{
protected:
	CServer();
	virtual ~CServer();
public:
	template<class T>
	static T* instance()
	{
		static T instance;
		return dynamic_cast<T*>(&instance);
	}
public:
	bool start( void* param = NULL);

	template<class T = int>
	bool start(int nThread,bool bMaintain = false,T* param = NULL)
	{
		__m_nThread = nThread;
		if (!_init())
		{
			return false;
		}
		T* temp = NULL;
		for (int i = 0; i < nThread; i++)
		{
            if (pthread_mutex_init(&_m_exit_mutex[i], NULL) != 0)
            {
                return false;
            }
            if (pthread_cond_init(&_m_exit_cond[i], NULL) != 0)
            {
                pthread_mutex_destroy(&_m_exit_mutex[i]);
                return false;
            }

            if (param)
			{
				temp = param + i;
			}
			else
			{
				temp = NULL;
			}
			__m_spRunThread[i] = std::make_shared<std::thread>(&CServer::__go, this, temp, i);
			if (!__m_spRunThread[i])
			{
                pthread_mutex_destroy(&_m_exit_mutex[i]);
                pthread_cond_destroy(&_m_exit_cond[i]);
				return false;
			}
		}
		if (bMaintain)
		{
			__m_bMaintain = bMaintain;
            _m_maintainexitFlag[0] = false;
            if (pthread_mutex_init(&_m_maintainexit_mutex[0], NULL) != 0)
            {
                return false;
            }
            if (pthread_cond_init(&_m_maintainexit_cond[0], NULL) != 0)
            {
                pthread_mutex_destroy(&_m_exit_mutex[0]);
                return false;
            }
			__m_spMaintainThread = std::make_shared<std::thread>(&CServer::__go_maintain, this);
		}
		return true;
	}

	void stop();
private:
	virtual void __go(void* param,int nTreadPos);
	virtual void __go_maintain();
protected:
	virtual bool _init() = 0;
	virtual void _pre_end() = 0;

	virtual void _end() = 0;

	virtual void _run(void* param,int nPos = 0) = 0;
	virtual void _maintain() {};
	virtual bool _sendMsg(CMsgPtr spMsg) { return true; }
	virtual bool _sendMsg(std::shared_ptr<std::list<CMsgPtr>> l_spMsg) { return true; }
public:
	virtual bool receive(CMsgPtr spMsg);
	virtual bool receive(CMsgPtr spMsg,int nPos);
	virtual bool receive(std::shared_ptr<std::list<CMsgPtr>> l_spMsg);
protected:
	virtual CMsgPtr _msgPop(int nPos);
private:
	std::shared_ptr<std::thread> __m_spRunThread[MAXTHREADSIZE];
	int __m_nThread;
	std::shared_ptr<std::thread> __m_spMaintainThread;

protected:
    pthread_mutex_t _m_exit_mutex[MAXTHREADSIZE];
    pthread_cond_t _m_exit_cond[MAXTHREADSIZE];
    std::atomic<bool> _m_exitFlag[MAXTHREADSIZE];

    pthread_mutex_t _m_maintainexit_mutex[MAXTHREADSIZE];
    pthread_cond_t _m_maintainexit_cond[MAXTHREADSIZE];
    std::atomic<bool> _m_maintainexitFlag[MAXTHREADSIZE];
protected:
	std::condition_variable _m_cond[MAXTHREADSIZE];
	std::mutex _m_listLock[MAXTHREADSIZE];
	std::list<CMsgPtr> _m_msgList[MAXTHREADSIZE];

	std::string _m_serverName;
	int _m_loopTime;
	bool __m_bMaintain;
	int __m_maintainLoopTime;
};


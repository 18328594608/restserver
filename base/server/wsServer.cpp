#include "wsServer.h"
#include "msg/RspMsg.h"
#include "msg/ReqMsg.h"
#include "admin/Admin.h"
#include "admin/WsAdmin.h"
#include "common/proxy/Proxy.h"
//#include "base/common/protocolHdl/ProtocolHdl.h"
#include "tool/Tool.h"

#define IOCP_SIZE 8
CWsServer::CWsServer()
{
	__m_maintainLoopTime = 30 * 1000;
	__m_port = 9900;
	__m_websocktServer.set_access_channels(websocketpp::log::alevel::none);
	__m_websocktServer.clear_access_channels(websocketpp::log::alevel::frame_payload);

	__m_websocktServer.init_asio();

	__m_websocktServer.set_open_handler(bind(&CWsServer::onOpen, this, ::_1));
	__m_websocktServer.set_close_handler(bind(&CWsServer::onClose, this, ::_1));
	__m_websocktServer.set_fail_handler(bind(&CWsServer::onFail, this, ::_1));
	__m_websocktServer.set_message_handler(bind(&CWsServer::onMessage, this, ::_1, ::_2));
	__m_websocktServer.set_http_handler(bind(&CWsServer::onHttp, this, ::_1));
	__m_websocktServer.set_socket_init_handler(bind(&CWsServer::onSocketInit, this, ::_1, ::_2));
	__m_websocktServer.set_pong_handler(bind(&CWsServer::onPong, this, ::_1, ::_2));
}


CWsServer::~CWsServer()
{
	for (size_t i = 0; i < __m_ts.size(); i++) {
		if (__m_ts[i])
		{
			__m_ts[i]->join();
		}
	}
}

bool CWsServer::_init()
{
	__m_maintainLoopTime = 30 * 1000;
	__m_websocktServer.set_reuse_addr(true);
	__m_websocktServer.set_listen_backlog(SOMAXCONN);

	__m_websocktServer.listen(__m_port);

	__m_websocktServer.start_accept();

	// Start the ASIO io_service run loop
	try {
		for (size_t i = 0; i < IOCP_SIZE; i++) {
			__m_ts.push_back(std::make_shared<std::thread>(&websocketppserver::run, &__m_websocktServer));
		}
	}
	catch (const std::exception & e) {

        //TODO err
		//LOG_ERROR(e.what());
	}

	return true;
}

void CWsServer::_run(void * param, int nPos)
{
	std::shared_ptr<CRspMsg> spMsg = std::dynamic_pointer_cast<CRspMsg>(_msgPop(nPos));
	if (!spMsg)
	{
		return;
	}
	if (spMsg->getWebsocketHdl().lock())
	{
		try
		{
            /*
			__m_websocktServer.send(spMsg->getWebsocketHdl(),spMsg->getUuid()+CMarkup::AToUTF8(spMsg->getMsg()), websocketpp::frame::opcode::value::text);
			if (spMsg->getLogPrint())
			{
				std::string msg = spMsg->getMsg();

				if (msg.find("tick") == msg.npos && msg.find("subOpenOrder") == msg.npos)
				{
					if (msg.find("userInfo") != msg.npos)
					    USER_INFO("[{}][{}]:{}", spMsg->getWebsocketHdl().lock().get(), spMsg->getUuid(), msg);
					else if (msg.find("chart") != msg.npos)
					    CHART_INFO("[{}][{}]:{}", spMsg->getWebsocketHdl().lock().get(), spMsg->getUuid(), msg.length() > 510 ? msg.substr(0, 500) : msg);
					else
					    LOG_INFO("[{}][{}]:{}", spMsg->getWebsocketHdl().lock().get(), spMsg->getUuid(), msg);
				}
			}*/
		}
		catch (std::exception& e)
		{
			//LOG_ERROR("wsHdl [{}] send failed,{}:[{}]{}", spMsg->getWebsocketHdl().lock().get(), e.what(), spMsg->getUuid(),spMsg->getMsg());
		}
	}
}

void CWsServer::_pre_end()
{
}

void CWsServer::_end()
{
	__m_websocktServer.stop();
}

void CWsServer::_maintain()
{
	std::map<websocket_spHdl, CWsClientInfo> m = gWsAdmin.getall();
	for (auto it : m)
	{
		try
		{
			__m_websocktServer.ping(it.first, "ping");
		}
		catch (const std::exception& e)
		{
			LOG_ERROR("{},{}|[{}|{}]", __FUNCTION__, e.what(),it.first.get(),it.second.getLogin());

			//socket������ʧЧ������kill���������������Ϣ
			killWsConn(it.first);
			gWsAdmin.pull(it.first);
		}
	}
}

void CWsServer::onOpen(connection_hdl hdl)
{
	gWsAdmin.push(hdl.lock());
	std::string ip = getClientIp(hdl);
	LOG_INFO("a new conn[{}|{}] is connected", ip, hdl.lock().get());

}

void CWsServer::onClose(connection_hdl hdl)
{
	gWsAdmin.pull(hdl.lock());
	gWsAdmin.removeSubOpenClient(hdl.lock());
}

void CWsServer::onFail(connection_hdl hdl)
{
	gWsAdmin.pull(hdl.lock());
}

void CWsServer::onMessage(connection_hdl hdl, websocketppserver::message_ptr msgPtr)
{
	std::string msg = msgPtr->get_payload();
	if (msg.size() <= 32)
	{
		return;
	}

	CReqMsgPtr spReqMsg = std::make_shared<CReqMsg>();
	spReqMsg->setMsg(msg.substr(32));
	spReqMsg->setWebsocketHdl(hdl);
	spReqMsg->setUuid(msg.substr(0, 32));
	CProxy::sendToPraseServer(std::static_pointer_cast<CMsg>(spReqMsg));
}

void CWsServer::onHttp(connection_hdl hdl)
{

}

void CWsServer::onSocketInit(connection_hdl, boost::asio::ip::tcp::socket & s)
{
    boost::asio::ip::tcp::no_delay option(true);
	s.set_option(option);
}

void CWsServer::onPong(connection_hdl hdl, std::string pangStr)
{
}

void CWsServer::killWsConn(connection_hdl hdl)
{
	std::string reason;
	try
	{
		__m_websocktServer.close(hdl, websocketpp::close::status::normal, reason);
	}
	catch (const std::exception&e)
	{
		LOG_ERROR("{},{}",__FUNCTION__,e.what());
	}
}

std::string CWsServer::getClientIp(connection_hdl hdl)
{
	conn_ptr conn_ptr = __m_websocktServer.get_con_from_hdl(hdl);
	std::string ip = conn_ptr->get_request_header("X-Forwarded-For");
	return ip;
}

std::string CWsServer::getAuth(connection_hdl hdl)
{
	conn_ptr conn_ptr = __m_websocktServer.get_con_from_hdl(hdl);
	std::string res = conn_ptr->get_resource();
	if (res.size() < 8 || res.find("uuid") == res.npos)
		return "";
	else
		return res.substr(7);
}
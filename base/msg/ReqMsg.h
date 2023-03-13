#pragma once
#include "Msg.h"
#include <memory>

class CReqMsg :
	public CMsg
{
public:
	CReqMsg();
	virtual ~CReqMsg();
};

typedef std::shared_ptr<CReqMsg> CReqMsgPtr;
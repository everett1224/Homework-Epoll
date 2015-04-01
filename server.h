////
// @file server.h
// @brief
// the server class
//
// @author wangbb
// @email 598428034@qq.com
//

#ifndef _SERVER_H_
#define _SERVER_H_

#include "serverbusiness.h"
#include "engine.h"

class Server 
{
  public:
	EpollEngine* myEngine;
	ServerBusiness* myBusiness;
	
	Server();
	~Server();
	
	bool getReady();
	void run();
	
};

#endif //_SERVER_H_

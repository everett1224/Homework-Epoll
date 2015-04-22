////
// @file acceptorhandler.h
// @brief
// the listen fd business class 
//
// @author wangbb
// @email edelweiss1224@gmail.com
//

#ifndef _ACCEPTORHANDLER_H_
#define _ACCEPTORHANDLER_H_

#include "eventhandler.h"
#include "handler.h"
#include "engine.h"

class AcceptorHandler : public EventHandler
{
  public:
	AcceptorHandler(EpollEngine* engine);
	~AcceptorHandler();
	  
	virtual bool handle();  
	virtual Handler getHandler();
	  
	bool getSeverReady();
	
  private:  
	//the handler contains the listen fd and the fd event
	Handler acceptor_;
	EpollEngine* engine_;
};

#endif //_ACCEPTORHANDLER_H_

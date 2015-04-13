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

class AcceptorHandler : public EventHandler
{
  public:
	AcceptorHandler();
	~AcceptorHandler();
	  
	virtual bool handle();  
	virtual Handler getHandler();
	  
	bool getSeverReady();
	
  private:  
	//the handler contains the listen fd and the fd event
	Handler acceptor_;
};

#endif //_ACCEPTORHANDLER_H_

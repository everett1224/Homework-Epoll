////
// @file eventhandler.h 
// @brief 
// the base class of all event handler 
// 
// @author wangbb
// @email edelweiss1224@gmail.com
//

#ifndef _EVENTHANDLER_H_
#define _EVENTHANDLER_H_

#include "handler.h"

class EventHandler
{
  public:
	//handle the event called by the engine
	virtual bool handle() = 0;
	
	//get the handler
	virtual Handler getHandler() = 0;

	//modify the fd 
	bool modifyFd(int fd);
};

#endif //_EVENTHANDLER_H_

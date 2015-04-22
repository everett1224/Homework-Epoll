////
// @file businesshandler.h
// @brief
// the accepted fd class 
//
// @author wangbb
// @email edelweiss1224@gmail.com
//


#ifndef _BUSINESSHANDLER_H_
#define _BUSINESSHANDLER_H_

#include "handler.h"
#include "eventhandler.h"
#include "engine.h"

class BusinessHandler : public EventHandler
{
  public:
	BusinessHandler(EpollEngine* engine, Handler& handler);
	~BusinessHandler();

	virtual bool handle(); 
	virtual Handler getHandler();
	
  private:
	//suicide 
	void suicide();
	
	//the working is done or not,if working is done, object will suicide
    bool done_;
	//the handler contains the accepted fd and the fd event
	Handler streamer_;
	EpollEngine* engine_;
};

#endif //_BUSINESSHANDLER_H_

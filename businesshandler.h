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

class BusinessHandler : public EventHandler
{
  public:
	BusinessHandler(Handler& handler);
	~BusinessHandler();

	virtual bool handleEvent(); 
	virtual Handler getHandler();
	
  private:
	//suicide 
	void suicide();
	
	//the working is done or not,if working is done, object will suicide
    bool done_;
	//the handler contains the accepted fd and the fd event
	Handler streamer_;
};

#endif //_BUSINESSHANDLER_H_

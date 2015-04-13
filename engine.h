////
// @file engine.h
// @brief
// the epoll engine class with the singleton pattern
//
// @author wangbb
// @email edelweiss1224@gmail.com
//

#ifndef _ENGINE_H_
#define _ENGINE_H_

#include "eventhandler.h"

class EpollEngine
{
  private:
    //the epoll fd
	int epollfd_;
	//the one and the only
	static EpollEngine *instance_;
	
	EpollEngine();
	//init the epollfd_, epoll_createl is here
	bool initialize();
	//analysis the event
	unsigned int getEvent(int eventype);
	
  public:
	~EpollEngine();
	
	//get the object addr
	static EpollEngine* getInstance();
	
	//the epoll_wait is here
	void run();
	//epoll_ctr is here
	bool addEvent(EventHandler* myitem);
	bool delEvent(EventHandler* myitem);
	bool modifyEvent(EventHandler* myitem);

};

#endif//_ENGINE_H_

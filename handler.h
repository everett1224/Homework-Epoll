////
// @file handler.h 
// @brief 
// the base class of all handler 
// 
// @author wangbb
// @email edelweiss1224@gmail.com
//

#ifndef _HANDLER_H_
#define _HANDLER_H_

//the event type for the epoll
enum EVENT_TYPE
{
    READ_EVENT = 0x01,
    WRITE_EVENT = 0x02,
};

struct Handler
{
	//the socket or file fd
	int myfd;
	
	//the event type for the epoll
	EVENT_TYPE myevent;
};

#endif //_HANDLER_H_
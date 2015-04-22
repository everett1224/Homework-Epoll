////
// @file engine.cc
// @brief
// the epoll engine class 
//
// @author wangbb
// @email edelweiss1224@gmail.com
//

#include <sys/epoll.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "engine.h"
#include "eventhandler.h"
#include "handler.h"

EpollEngine::EpollEngine()
{
	if (false == initialize())
		perror("Epollfd false");
}

EpollEngine::~EpollEngine()
{
	close(epollfd_);
}


bool EpollEngine::addEvent(EventHandler* myitem)
{
	Handler item = myitem->getHandler();
	struct epoll_event event;
	event.data.ptr = myitem;
	event.events = getEvent(item.myevent);

	int s;
	s = epoll_ctl(epollfd_, EPOLL_CTL_ADD, item.myfd, &event);
	if (s == -1) {
		perror("epoll_ctl error");
		return false;
	}

	return true;
}

bool EpollEngine::delEvent(EventHandler* myitem)
{
	Handler item = myitem->getHandler();
	struct epoll_event event;
	event.data.ptr = myitem;
	event.events = getEvent(item.myevent);

	int s;
	s = epoll_ctl(epollfd_, EPOLL_CTL_DEL, item.myfd, &event);
	if (s == -1) {
		perror("epoll_ctl error");
		return false;
	}

	return true;
}

bool EpollEngine::modifyEvent(EventHandler* myitem)
{
	Handler item = myitem->getHandler();
	struct epoll_event event;
	event.data.ptr = myitem;
	event.events = getEvent(item.myevent);

	int s;
	s = epoll_ctl(epollfd_, EPOLL_CTL_MOD, item.myfd, &event);
	if (s == -1) {
		perror("epoll_ctl error");
		return false;
	}

	return true;
}

bool EpollEngine::initialize()
{
	epollfd_ = epoll_create1(0);
	if (epollfd_ == -1){
		perror("epoll_create1");
		return false;
	}
	return true;
}

unsigned int EpollEngine::getEvent(int eventype)
{
	if (eventype < 0){
		printf("event error");
		exit(0);
	}
	switch(eventype)
	{
		case 0x01:
			return EPOLLIN | EPOLLET;
		case 0x02:
			return EPOLLOUT | EPOLLET;
		//	default
	}
	return 0x00000000;
}

void EpollEngine::run()
{
	int n ,i;
	struct epoll_event events[64];

	n = epoll_wait(epollfd_ , events, 64 , -1);
	if (-1 == n) {
		perror("epoll_wait error");
		exit(0);
	}

	for (i = 0; i < n; ++i) {
		void *p = events[i].data.ptr;
		((EventHandler*)p)->handle();	// ??? !!!
	}
}

#if 0
//the singleton instance
EpollEngine* EpollEngine::instance_ = NULL;

EpollEngine* EpollEngine::getInstance()
{
	if(instance_ == NULL)
		instance_ = new EpollEngine();
	return instance_;
}
#endif
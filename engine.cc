////
// @file engine.cc
// @brief
// the epoll engine class 
//
// @author wangbb
// @email 598428034@qq.com
//

#include <sys/epoll.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include "engine.h"

EpollEngine::EpollEngine()
{
	epollfd_ = epoll_create1(0);
	if (epollfd_ == -1)
		perror("epoll_create1");
//	events = (struct epoll_event*)calloc(64 , sizeof(struct epoll_event));
}

EpollEngine::~EpollEngine()
{
	close(epollfd_);
//	free(events);
}


bool EpollEngine::addToTheEngine(Business* item, int action)
{
	struct epoll_event event;
	event.data.ptr = item;
	event.events = item->myevent;
	int s;
	
	if (action == 0)
		s = epoll_ctl(epollfd_, EPOLL_CTL_ADD, item->fd, &event);
	else
		s = epoll_ctl(epollfd_, EPOLL_CTL_MOD, item->fd, &event);

	if (s == -1) {
		perror("epoll_ctl error");
		return false;
	}

	return true;
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
		((Business*)p)->run();	// ???
	}
}

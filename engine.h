////
// @file engine.h
// @brief
// the epoll engine class
//
// @author wangbb
// @email 598428034@qq.com
//

#ifndef _ENGINE_H_
#define _ENGINE_H_

#include "business.h"

class EpollEngine
{
  private:
	int epollfd_;

  public:
	EpollEngine();
	~EpollEngine();
	
	void run();
	bool addToTheEngine(Business* item,int action);
	Business* ifFind(int fd);
};

#endif//_ENGINE_H_

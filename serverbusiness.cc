////
// @file serverbusiness.cc
// @brief
// the listen fd business class 
//
// @author wangbb
// @email 59428034@qq.com
//

#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/epoll.h>
#include "serverbusiness.h"

ServerBusiness::ServerBusiness(EpollEngine* engine)
{
	pmasterEngine = engine;
}

bool ServerBusiness::run()
{
	while(1)
	{
		struct sockaddr_in cltaddr;
		socklen_t socklen;
		
		socklen = sizeof(cltaddr);
		
		int confd = accept(fd, (struct sockaddr*)&cltaddr, &socklen);
		if(confd == -1)
		{
			if(errno == EAGAIN)
				break;
			else{
				perror("accept error");
				return false;
			}
		}
		
		ConnectReadBusiness* pconReadBusiness = new ConnectReadBusiness(pmasterEngine);
		pconReadBusiness->fd = confd;
		pconReadBusiness->modifyFd();
		pconReadBusiness->myevent = EPOLLIN | EPOLLET;
		
		pmasterEngine->addToTheEngine(pconReadBusiness, 0);
	}
	
	return true;
}

ServerBusiness::~ServerBusiness()
{
	close(fd);
}

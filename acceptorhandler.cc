////
// @file acceptorhandler.cc
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
#include <strings.h>
//#include "eventhandler.h"
#include "engine.h"
#include "handler.h"
#include "acceptorhandler.h"
#include "businesshandler.h"

AcceptorHandler::AcceptorHandler()
{
	getSeverReady();
}

Handler AcceptorHandler::getHandler()
{
	return acceptor_;
}

bool AcceptorHandler::getSeverReady()
{
	int sfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sfd == -1){
		perror("create socket error");
		return false;
	}
	
	int on = 1;
	setsockopt( sfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on) );
	
	struct sockaddr_in servaddr;
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(10240);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	bzero(&(servaddr.sin_zero),8);

	if (bind (sfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) == -1)
	{
		perror("bind error");
		close(sfd);
		return false;
	}
	
	acceptor_.myfd = sfd;
	modifyFd(acceptor_.myfd);
	acceptor_.myevent = READ_EVENT;
	EpollEngine::getInstance()->addEvent(this);
	
	int s = listen(sfd, 20);
	if(-1 == s){
		perror("listen error");
		close(sfd);
	}
	
	return true;
}



bool AcceptorHandler::handleEvent()
{
	while(1)
	{
		struct sockaddr_in cltaddr;
		socklen_t socklen;
		
		socklen = sizeof(cltaddr);
		
		int confd = accept(acceptor_.myfd, (struct sockaddr*)&cltaddr, &socklen);
		if(confd == -1)
		{
			if(errno == EAGAIN)
				break;
			else{
				perror("accept error");
				return false;
			}
		}
		
		Handler streamer_;
		streamer_.myfd = confd;
		streamer_.myevent = READ_EVENT;
		new BusinessHandler(streamer_);
		
//		pmasterEngine->addToTheEngine(pconReadBusiness, 0);
	}
	
	return true;
}

AcceptorHandler::~AcceptorHandler()
{
	close(acceptor_.myfd);
}

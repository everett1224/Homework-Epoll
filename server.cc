////
// @file server.cc
// @brief
// the server class
//
// @author wangbb
// @email 598428034@qq.com
//

#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <strings.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include "server.h"

Server::Server()
{
	myEngine = new EpollEngine;
	myBusiness = new ServerBusiness(myEngine);
}

bool Server::getReady()
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
	
	myBusiness->fd = sfd;
	myBusiness->modifyFd();
	myBusiness->myevent = EPOLLIN | EPOLLET;
	myEngine->addToTheEngine(myBusiness, 0);
	
	int s = listen(sfd, 20);
	if(-1 == s){
		perror("listen error");
		close(sfd);
	}
	
	return true;
}

void Server::run()
{
	getReady();
	
	while(1)
		myEngine->run();

}

Server::~Server()
{
	delete myBusiness;
	delete myEngine;
}

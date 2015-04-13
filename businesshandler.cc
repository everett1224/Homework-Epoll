////
// @file businesshandler.cc
// @brief
// the accepted fd class 
//
// @author wangbb
// @email edelweiss1224@gmail.com
//

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include "businesshandler.h"
#include "handler.h"
#include "engine.h"
#include "factory.h"

BusinessHandler::BusinessHandler(Handler& handler)
{
	streamer_ = handler;
	
	modifyFd(streamer_.myfd);
	//get the factory instance
	Factory* pFactory = Factory::getInstance();
	//register to the engine
	(pFactory->getTheEngine())->addEvent(this);
	//init the done_ as false ,this is important!!!
	done_ = false;
}

Handler BusinessHandler::getHandler()
{
	return streamer_;
}

bool BusinessHandler::handle()
{
	printf("OK got a connetion @ fd %d\n", streamer_.myfd);
	char buf[512];
	while (1)
	{
		int count;
		bzero(buf,512);
		
		count = read (streamer_.myfd, buf, 512);
		
		if (count == -1)
		{
			if(EAGAIN != errno){
				perror ("read");
				exit(0);
			}		
			break;
		}
		else if (count == 0)
		{
			// End of file. The remote has closed the connection. 
			printf("this count == 0  fd %d\n", streamer_.myfd);
			done_ = true;
			break;
		}

		// write the buffer to remote output 
		write(streamer_.myfd, "this is echo:", sizeof("this is echo:"));
		write(streamer_.myfd, buf, count); 

		//pwt->fd = fd;
		//pwt->modifyFd();
		//pwt->myevent = EPOLLOUT | EPOLLET;
		//pmasterEngine->addToTheEngine(pwt, 1);

		int s = printf("the buff is %s\n", buf);
		if (s == -1){
			perror ("write");
			return false;
		}
	}

	if (done_){
		printf ("Closed connection on descriptor %d\n", streamer_.myfd);
		suicide();
	}
	
	return true;
}

void BusinessHandler::suicide()
{
	printf("this is sucide by fd %d\n", streamer_.myfd);
	close(streamer_.myfd);
	delete this;
}

BusinessHandler::~BusinessHandler()
{
	printf("farewell\n");
}

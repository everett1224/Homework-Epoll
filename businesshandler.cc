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

BusinessHandler::BusinessHandler(EpollEngine* engine, Handler& handler):engine_(engine)
{
	streamer_ = handler;
	
	modifyFd(streamer_.myfd);
	//register to the engine
	engine_->addEvent(this);
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
			if(EAGAIN != errno)
			{
				printf ("errno %d : %s\n", errno, strerror(errno));
				if(ECONNRESET == errno) // errno 104
				{
					printf("CLIENT ECONNRESET\n");
					done_ = true;
					break;
				}
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
		write(streamer_.myfd, "this is echo:", sizeof("this is echo:")-1);//sizeof() - 1 will delete the string charictor /0 
		write(streamer_.myfd, buf, count); 

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

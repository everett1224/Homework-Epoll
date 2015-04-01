////
// @file writebusiness.cc
// @brief
// the write business class
//
// @author wamgbb
// @email 598428034@qq.com
//

#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include "writebusiness.h"

ConnectWriteBusiness::ConnectWriteBusiness(EpollEngine *p, char *str, ConnectReadBusiness *rd)
{
	pmasterEngine = p;
	buf_ = str ;
	prd_ = rd;
	done = false;
}

bool ConnectWriteBusiness::run()
{
	while(1)
	{
		write(fd, "this is echo:", sizeof("this is echo:"));
		int s = write(fd, buf_, getBufSize());
		if (s == -1)
		{
			if(EAGAIN != s){
				perror("write error");
				exit(0);
			}	
		}
		
		done = true;
		break;
	}
	
	if(done){
		prd_->myevent = EPOLLIN | EPOLLET;
		pmasterEngine->addToTheEngine(prd_, 1);
	}
	
	return true;
}

int ConnectWriteBusiness::getBufSize()
{
	int i = 0;
	while(buf_[i])
		i++;
		
	return i;
}

ConnectWriteBusiness::~ConnectWriteBusiness()
{
	printf("write finished farewell my friend\n");	
}

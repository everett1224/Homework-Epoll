////
// @file conread.cc
// @brief
// the accepted fd class 
//
// @author wangbb
// @email 598428034@qq.com
//

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/epoll.h>
#include "conread.h"

ConnectReadBusiness::ConnectReadBusiness(EpollEngine* p)
{
	pmasterEngine = p;
	buf = (char*)malloc(sizeof(char)*512);
	memset(buf, 0, 512);
	
//	ConnectWriteBusiness* pwt =	new ConnectWriteBusiness(pmasterEngine,buf,count,this);
	pwt =	new ConnectWriteBusiness(pmasterEngine,buf,this);
	done = false;
}

bool ConnectReadBusiness::run()
{
	printf("OK got a connetion @ fd %d\n", fd);

	while (1)
	{
		int count;
//		bzero(buf,512);
		
//		count = read (fd, buf, sizeof(buf));
		count = read (fd, buf, 512);
		
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
			printf("this count == 0  fd %d\n",fd);
			done = true;
			break;
		}

		// write the buffer to remote output 
//		write(fd,"this is echo:",sizeof("this is echo:"));
//		write(fd,buf,count); 

		pwt->fd = fd;
//		pwt->modifyFd();
		pwt->myevent = EPOLLOUT | EPOLLET;
		pmasterEngine->addToTheEngine(pwt, 1);

		int s = printf("the buff is %s\n",buf);
		if (s == -1){
			perror ("write");
			return false;
		}
	}

	if (done){
		printf ("Closed connection on descriptor %d\n", fd);
		suicide();
	}
	
	return true;
}

void ConnectReadBusiness::suicide()
{
	printf("this is sucide by fd %d\n",fd);
	close(fd);
	delete this;
}

ConnectReadBusiness::~ConnectReadBusiness()
{
	delete pwt;
	printf("farewell my friends !\n");
}

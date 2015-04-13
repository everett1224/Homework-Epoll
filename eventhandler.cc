////
// @file eventhandler.cc
// @brief 
// the base class of all event handler class
//
// @author wangbb
// @email edelweiss1224@gmail.com
//

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <unistd.h>
#include <fcntl.h>
#include "eventhandler.h"

bool EventHandler::modifyFd(int fd)
{
	int flags, s;

	flags = fcntl (fd, F_GETFL, 0);
	if (flags == -1){
		perror ("fcntl");
		return false;
	}

	flags |= O_NONBLOCK;
	
	s = fcntl (fd, F_SETFL, flags);
	if (s == -1){
		perror ("fcntl");
		return false;
	}

	return true;

}


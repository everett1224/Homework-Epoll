////
// @file business.cc
// @brief 
// the base class of all business class
//
// @author wangbb
// @email 598428034@qq.com
//

#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <unistd.h>
#include <fcntl.h>
#include"business.h"

bool Business::modifyFd()
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


////
// @file business.h 
// @brief 
// the base class of all business 
// 
// @author wangbb
// @email 598428034@qq.com
//


#ifndef __BUSINESS__H__
#define __BUSINESS__H__

class Business
{
  public:
	int fd;
	unsigned int myevent;
	
	virtual bool run()=0;
	bool modifyFd();
};

#endif //__BUSINESS__H__

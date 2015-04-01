////
// @file writebusiness.h
// @brief
// the write business class
//
// @author wamgbb
// @email 598428034@qq.com
//


#ifndef _WRITEBUSINESS_H_
#define _WRITEBUSINESS_H_

#include "conread.h"
#include "business.h"
#include "engine.h"

class ConnectReadBusiness;

class ConnectWriteBusiness : public Business
{
  private:
	ConnectReadBusiness* prd_;
	char* buf_;

  public:
	EpollEngine* pmasterEngine;
	bool done;
	
	ConnectWriteBusiness(EpollEngine* p,char* str,ConnectReadBusiness* rd);
	~ConnectWriteBusiness();
	
	virtual bool run();
	int getBufSize();
};

#endif //_WRITEBUSINESS_H_

////
// @file conread.h
// @brief
// the accepted fd class 
//
// @author wangbb
// @email 598428034@qq.com
//


#ifndef _CONREAD_H_
#define _CONREAD_H_

#include "business.h"
#include "engine.h"
#include "writebusiness.h"

class ConnectWriteBusiness;

class ConnectReadBusiness : public Business
{
  private:
	ConnectWriteBusiness* pwt;
	char* buf;
	
  public:
	EpollEngine* pmasterEngine;
	
	ConnectReadBusiness(EpollEngine* p);
	~ConnectReadBusiness();
	
	bool done;
	virtual bool run(); 
	void suicide();
};

#endif //_CONREAD_H_

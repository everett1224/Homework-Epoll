////
// @file serverbusiness.h
// @brief
// the listen fd business class 
//
// @author wangbb
// @email 59428034@qq.com
//

#ifndef _SERVERBUSINESS_H_
#define _SERVERBUSINESS_H_


#include "conread.h"
#include "engine.h"
#include "business.h"

class ServerBusiness : public Business
{
  public:
	  EpollEngine* pmasterEngine;
	  
	  ServerBusiness(EpollEngine* engine);
	  ~ServerBusiness();
	  
	  virtual bool run();
};

#endif //_SERVERBUSNIESS_H_

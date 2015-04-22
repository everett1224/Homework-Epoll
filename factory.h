////
// @file factory.h
// @brief 
// the factory of the engine, the factory is singleton with Iversion of Control;
// (Dependency Injection | Service Locator better?)
//
// @auther wangbb
// @email edelweiss1224@gmail.com
//

#ifndef _FACTORY_H_
#define _FACTORY_H_

#include "engine.h"
#include "businesshandler.h"
#include "handler.h"

class Factory
{
  private:
	Factory();
	
	// the one and the only
	static Factory *instance_;
	// the engine point
	EpollEngine* pEngine_;

  public:
	~Factory();
	
	void deleteEngine();
	// get the object of the Factory
	static Factory* getInstance();
	// create a new engine
	EpollEngine* createEngine();
	// get the engine
	EpollEngine* getTheEngine();
	// create a new businesshandler
	BusinessHandler* createBusinessHandler(Handler& handler);
};

#endif//_FACTORY_H_

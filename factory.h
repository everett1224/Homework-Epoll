////
// @file factory.h
// @brief 
// the factory of the engine, the factory is singleton.
// (Dependency Injection better?)
//
// @auther wangbb
// @email edelweiss1224@gmail.com
//

#ifndef _FACTORY_H_
#define _FACTORY_H_

#include "engine.h"

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

	// get the object of the Factory
	static Factory* getInstance();
	// create the new engine
	EpollEngine* createEngine();
	// get the engine
	EpollEngine* getTheEngine();
};

#endif//_FACTORY_H_

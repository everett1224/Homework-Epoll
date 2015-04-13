////
// @file factory.cc
// @brief 
// the factory of the engine, the factory is singleton.
// (Dependency Injection better?)
// 
// @auther wangbb
// @email edelweiss1224@gmail.com
//

#include "factory.h"
#include <stdio.h>

Factory::Factory():pEngine_(NULL){}

EpollEngine* Factory::createEngine()
{
	pEngine_ = new EpollEngine();
	return pEngine_;
}

EpollEngine* Factory::getTheEngine()
{
	return pEngine_;
}

//the singleton instance
Factory* Factory::instance_ = NULL;

Factory* Factory::getInstance()
{
	if (instance_ == NULL)
		instance_ = new Factory();
	return instance_;
}

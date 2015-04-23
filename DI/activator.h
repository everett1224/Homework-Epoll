////
// @file acitvator.h 
// @brief 
// the factory of the object 
// 
// @author wangbb
// @email edelweiss1224@gmail.com
//

#ifndef _CPPINJECT_ACTIVATOR_H_
#define _CPPINJECT_ACTIVATOR_H_

#include "zone.h"

namespace CppInject
{

template <class T>
T* default_factory(Zone& f)
{
	return new T;
};

template <class T>
void default_cleaner(T* t)
{
	delete t;
};

template <class T>
class activator
{
  public:
	typedef T* (*factoryFunction)(Zone& f) ;
	typedef void (*cleanupFunction)(T*) ;

	activator()
	  : mFactory(0), mCleanup(0)
	{
	}

	void operator=(const activator& other)
	{
		mFactory = other.mFactory;
		mCleanup = other.mCleanup;
	}

	activator(factoryFunction f, cleanupFunction c)
	  : mFactory(f), mCleanup(c)
	{
	}

	activator(const activator& a)
	  : mFactory(a.mFactory), mCleanup(a.mCleanup)
	{}

	factoryFunction factory() const
	{
		return mFactory;
	}

	cleanupFunction cleanup() const
	{
		return mCleanup;
	}

  private:
	factoryFunction mFactory;
	cleanupFunction mCleanup;
};
	
}

#endif //_CPPINJECT_ACTIVATOR_H_

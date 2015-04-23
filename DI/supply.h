////
// @file supply.h 
// @brief 
// the agent of the factory
// 
// @author wangbb
// @email edelweiss1224@gmail.com
//

#ifndef _CPPINJECT_SUPPLY_H_
#define _CPPINJECT_SUPPLY_H_

#include "activator.h"
#include "destroyer.h"
#include "zone.h"
#include <string>
#include <map>
#include <stdexcept>
#include <sstream>
#include "globalobject.h"


namespace CppInject
{

/**
 *
 */
template <typename T, int Which=0> 
class supply
{
	class TDestroyer : public destroyer
	{
		Zone* zone_;
	  public:
		TDestroyer(Zone* zone)
		{
			zone_ = zone;
		}
		
		void operator()()
		{
			supply<T>::release(zone_);
		}
	};
	
  public:
	typedef T* (*factory)(Zone& f) ;
	typedef void (*cleanup)(T*) ;

	supply()
	{
	}

	virtual ~supply()
	{
	}
	
  private:
	static std::map< const Zone* , activator<T> > activator_map; 
	static std::map< Zone* , T* > object_map;

  public:
	static void configure(const Zone& zone)
	{
		configure (zone, activator<T>(default_factory<T>, default_cleaner<T>));
	}
	
	static void configure(const Zone& zone, activator<T> act)
	{
		activator_map[&zone] = act;
	}
	

	static void configure()
	{
		configure (globalZone, activator<T>(default_factory<T>, default_cleaner<T>));
	}

	static void configure ( const Zone& zone, factory factfunct,cleanup cleanfunct)
	{
		activator_map[&zone] = activator<T>(factfunct, cleanfunct);
	}
	
	static void configure ( factory factfunct )
	{
		configure(globalZone, factfunct, default_cleaner<T>);
	}
	
	static T* fetch(Zone& zone = globalZone)
	{
		Zone* zonep = &zone;
		T * val = object_map[zonep];
		
		if (!val)
		{
			activator<T> act = activator_map[&zone];

			if (0 == act.factory())
			{
				if (zone.parent())
				{
					return fetch(*zone.parent());
				}
				else
				{
					std::string message("No factory function registered and no parent for ");
					std::stringstream ss;
					ss<<Which;

					throw std::logic_error(message + ss.str());
				}
			}
			
			//This needs a lock in order to be thread safe.
			{
			  val = (*act.factory())(zone);
			  object_map[&zone] = val;

			  destroyer* d = new TDestroyer(&zone);
			  zone.push_destroyer(d);
			}
		}
		
		return val;
	}

	static void release(Zone* zone)
	{
		T * val = object_map[zone];
		
		if ( 0 == val){
			return;
		}

		(activator_map[zone].cleanup())(object_map[zone]);
		object_map.erase(zone);
	}
};


template<typename T, int Which>
std::map< const Zone*, activator<T> > supply<T,Which>::activator_map;


template<typename T, int Which>
std::map< Zone*, T* > supply<T,Which>::object_map;

#define REGISTER(CLASS)					\
  bool register##CLASS(){				\
    supply<CLASS>::configure();				\
    return true;					\
  }							\
  static bool __registered##CLASS = register##CLASS()

#define REGISTER_FACTORY(CLASS,FACTORY)			\
  bool register##CLASS(){				\
    supply<CLASS>::configure(FACTORY);			\
    return true;					\
  }							\
  static bool __registered##CLASS = register##CLASS()

#define REGISTER_FACTORY_CLEANER(CLASS,FACTORY,CLEANER)	\
  bool register##CLASS(){				\
    supply<CLASS>::configure(FACTORY,CLEANER);		\
    return true;					\
  }							\
  static bool __registered##CLASS = register##CLASS()
}

#endif //_CPPINJECT_SUPPLY_H_

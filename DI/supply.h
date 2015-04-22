// Copyright 2009 Michaël Larouche <larouche@kde.org>
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
#ifndef _CPPINJECT_SUPPLY_H_
#define _CPPINJECT_SUPPLY_H_

#include "activator.h"
#include "destroyer.h"
#include "Zone.h"
//#include "ZoneType.h"

#include <string>
#include <map>
#include <stdexcept>
//#include <stdio.h>
//#include <iostream>
#include <sstream>
#include "GlobalObject.h"


namespace CppInject
{

/**
 *
 */
template <typename T, int Which=0> class supply
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
//	static std::map< const ZoneType *, activator<T> > activator_map; 
	static std::map< const Zone* , activator<T> > activator_map; 
	static std::map< Zone* , T* > object_map;

public:
	//add by me
	static void configure(const Zone& zone)
	{
		configure (zone, activator<T>(default_factory<T>, default_cleaner<T>));
	}
	
	static void configure(const Zone& zone, activator<T> act)
	{
		activator_map[&zone] = act;
	}
	
/*	static void configure(const ZoneType& zoneType, activator<T> act)
	{
		activator_map[&zoneType] = act;
	}

	static void configure(const ZoneType& zoneType, factory factfunct,cleanup cleanfunct)
	{
		activator_map[&zoneType] = activator<T>(factfunct, cleanfunct);
	}
*/

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
#if 0
	static void configure(factory factfunct,cleanup cleanfunct)
	{
		configure(GlobalZoneType::instance, factfunct,cleanfunct);
	}

	

	static void configure(cleanup cleanfunct)
	{
		configure (GlobalZoneType::instance, default_factory<T>, cleanfunct);
	}

	static void configure()
	{
		configure (GlobalZoneType::instance,activator<T>(default_factory<T>, default_cleaner<T>));
	}
#endif
	static T* fetch(Zone& zone = globalZone)
	{
		Zone* zonep = &zone;
		T * val = object_map[zonep];
		
		if (!val)
		{
	//		activator<T> act = activator_map[zone.zoneType()];
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
					//char buf[4];
					//sprintf(buf, "%d", Which);
					std::stringstream ss;
					ss<<Which;
					//message.push_back( ss.str() );

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
		#if 0
		if (!val)
		{
			if (zone->parent())
			{
				release(zone->parent());
			}
	
			//We may want to put an assert failure here.
			return;
		}
		#endif
		if ( 0 == val)
		{
			return;
		}
//		(activator_map[zone->zoneType()].cleanup())(object_map[zone]);
		(activator_map[zone].cleanup())(object_map[zone]);
		object_map.erase(zone);
	}
};

//template<typename T, int Which>
//std::map< const ZoneType *, activator<T> > supply<T,Which>::activator_map;

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

#endif

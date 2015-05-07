////
// @file bindings.cc 
// @brief 
// step1:
// add your own "constructor" function.if none, just ignore it. 
// add your own "destructor" funtion.if none, just ignore it. 
// step2:
// bind the class and the class factory with function : supply<CLASSNAME>::configure(ZONE, CONSTRUCTOR, CLEANER)
// CLASSNAME : you class intended to bind
// ZONE : the zone that you want you object alive in. default zone is global zone.
// CONSTRUCTOR : the function which at step1, default function is the CLASSNAME default constructor.
// CLEANER : the function which at step1, default function is the CLASSNAME default destructor.
// 
// @author wangbb
// @email edelweiss1224@gmail.com
//

#include "DI/cppinject.h"
#include <stdio.h>
#include "engine.h"
#include "acceptorhandler.h"

using namespace CppInject;

AcceptorHandler* createAcceptorHandler(Zone& zone)
{
	return new AcceptorHandler(supply<EpollEngine>::fetch(zone));
}


extern "C"
{
	void __attribute__ ((constructor)) register_all_bindings()
	{
		static bool not_yet_run = true;	
		//this is just a test string
		printf("start of main %s\n", __FUNCTION__);
		
		if (not_yet_run)
		{
			printf(":Registering\n");
			
			//bind the factory and the class
			supply<EpollEngine>::configure();
			supply<AcceptorHandler>::configure(createAcceptorHandler);

			not_yet_run = false;
		}
	}
	
	void __attribute__ ((destructor)) binding_fini(void)
	{
		//this is just a test string 
		printf("end of main %s\n", __FUNCTION__);
	}
}

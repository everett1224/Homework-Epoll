#include "DI/CppInject.h"
//#include "sample_classes.h"
#include <iostream>
#include "engine.h"
#include "acceptorhandler.h"
//#include "businesshandler.h"
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
	//	std::cout << __FUNCTION__;

		if (not_yet_run){
	//		std::cout << ":Registering";
			supply<EpollEngine>::configure();
			supply<AcceptorHandler>::configure(createAcceptorHandler);

			not_yet_run = false;
		}
	//	std::cout << std::endl;
	}
	void __attribute__ ((destructor)) binding_fini(void)
	{
	//	std::cout << __FUNCTION__ << std::endl;
	}
}

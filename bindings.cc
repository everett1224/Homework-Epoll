#include "DI/cppinject.h"
#include <stdio.h>
#include "engine.h"
#include "acceptorhandler.h"
#include <signal.h>
#include "string.h"


using namespace CppInject;

AcceptorHandler* createAcceptorHandler(Zone& zone)
{
	return new AcceptorHandler(supply<EpollEngine>::fetch(zone));
}

typedef void (*func)(int);

void signalINTConfg(func foo)
{
	struct sigaction sa;
	memset( &sa, 0, sizeof(sa) );
	sa.sa_handler = foo;
	sigfillset( &sa.sa_mask );
	sigaction( SIGINT, &sa, NULL );
}

extern "C"
{
	void __attribute__ ((constructor)) register_all_bindings()
	{
		static bool not_yet_run = true;	
	
		printf("start of main %s\n", __FUNCTION__);
		
		if (not_yet_run){
			printf(":Registering\n");
			supply<EpollEngine>::configure();
			supply<AcceptorHandler>::configure(createAcceptorHandler);

			not_yet_run = false;
		}
	//	std::cout << std::endl;
	}
	void __attribute__ ((destructor)) binding_fini(void)
	{
		printf("end of main %s\n", __FUNCTION__);
	}
}

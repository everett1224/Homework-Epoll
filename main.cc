#include "DI/cppinject.h"
#include "acceptorhandler.h"
#include "engine.h"
#include "sigfunc.h"


static bool quit = false; 

void got_signal(int no)
{
    quit = true;
}

typedef void (*func)(int);

int main()
{
	signalINTConfg(got_signal);
	
	CppInject::supply<AcceptorHandler>::fetch();
	
	EpollEngine* engine = CppInject::supply<EpollEngine>::fetch();
	
	while(!quit){
		engine->run();
	}
	
	return 0;
}

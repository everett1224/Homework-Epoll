#include "DI/cppinject.h"
#include "acceptorhandler.h"
#include "engine.h"

extern void signalINTConfg(void(*func)(int));

bool quit = false; 

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
	
	while(1){
		engine->run();
		if(quit) break;
	}
	
	return 0;
}
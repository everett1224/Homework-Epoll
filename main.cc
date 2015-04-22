#include "DI/CppInject.h"
#include "acceptorhandler.h"
#include "engine.h"

int main()
{
	CppInject::supply<AcceptorHandler>::fetch();
	
	EpollEngine* engine = CppInject::supply<EpollEngine>::fetch();
	
//	AcceptorHandler sever(engine);
	
	while(1){
		engine->run();
	}
}
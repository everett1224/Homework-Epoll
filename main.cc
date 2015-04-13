#include "acceptorhandler.h"
#include "engine.h"
#include "factory.h"

int main()
{
	Factory* pFactory = Factory::getInstance();
	pFactory->createEngine();
	
	AcceptorHandler server;
	
	while(1){
		(pFactory->getTheEngine())->run();
	}
}
#include "acceptorhandler.h"
#include "engine.h"
#include "factory.h"

int main()
{
	//get the factory 
	Factory* pFactory = Factory::getInstance();
	pFactory->createEngine();
	
	//the server is here
	AcceptorHandler server;
	
	while(1){
		(pFactory->getTheEngine())->run();
	}
	
	pFactory->deleteEngine();
	delete pFactory;
}
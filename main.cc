#include "acceptorhandler.h"
#include "engine.h"

int main()
{
	AcceptorHandler server;
	
	while(1){
		EpollEngine::getInstance()->run();
	}
}
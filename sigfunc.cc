#include "sigfunc.h"
#include <signal.h>
#include <string.h>

void signalINTConfg(void (*foo)(int))
{
	struct sigaction sa;
	memset( &sa, 0, sizeof(sa) );
	sa.sa_handler = foo;
	sigfillset( &sa.sa_mask );
	sigaction( SIGINT, &sa, NULL );
}

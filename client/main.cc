#include "client.h"
#include "tcpClient.h"
#include <string.h>

#define MAXLINE 512

void web_business(int C_socket)
{
	char bb[MAXLINE];
	bzero (bb, sizeof(bb));
	send (C_socket, "hello world this is a test", strlen("hello world this is a test"),0);
	
	int size = 0;
	while ( size != 39 )
	{
		size += recv(C_socket,bb,sizeof(bb),0);
		printf("%s", bb);
	}
	printf("\n");
}

int main(int argc, char **argv)
{
	if(argc != 2)
	{
		printf("input the client num\n");
		exit(0);
	}
	int i,num;
	num = atoi(argv[1]);

	for(i=0;i<num;i++)
	{ 
		if(vfork()==0)//here vfork is better than fork to print to the screen
		{
			Client<Tcp> myClient("127.0.0.1", 10240, web_business);
			myClient.run();
		}
		else  // if keyword else is forget this will the run() will only called once
			  // because of the child and parent both will call exit. ELSE can make the child not call the exit.
		exit(0);	//!!! this is important see man vfork. if forget it will causer coredump 
			    	//a.out: cxa_atexit.c:100: __new_exitfn: Assertion `l != ((void *)0)' failed. Aborted (core dumped)
					//If you have a look at the man page for vfork(), you should see it tells you that you should never return from the function in the child, or call exit() - call either _exit() or one of the exec() functions.
	}
//	exit(0);
	
	return 0;
}	
#include "client.h"
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
			Client<TCP> myClient("127.0.0.1", 10240, web_business);
			myClient.run();
		}
		else 
			exit(0);
	}
	
	return 0;
}	
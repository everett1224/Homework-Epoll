#include"unp.h"

//#define CLIENT_NUM 100
int main(int argc, char **argv)
{
	if(argc != 2)
	{
		printf("input the client num\n");
		exit(0);
	}
	int i,num;
	num = atoi(argv[1]);
	void web_business(int);
	for(i=0;i<num;i++)
	{ 
		if(vfork()==0)//here vfork is better than fork to print to the screen
		{
			printf("%d is working\n",getpid());
			int C_socket = socket(AF_INET,SOCK_STREAM,0);
			if(C_socket == -1)
			{
				printf("socket error\n");
				exit(1);
			}
			struct sockaddr_in ser;
			ser.sin_family = AF_INET;
			ser.sin_port = htons(SERV_PORT);
			ser.sin_addr.s_addr = inet_addr("192.168.96.169");
			if(connect(C_socket,(struct sockaddr*)&ser,sizeof(ser)) == -1)
			{
				perror("connect error:");
				exit(1);
			}
			
//			bool modifyFd(int fd);
//			if(!modifyFd(C_socket))
//			{
//				perror("modifyFd error:");
//				exit(1);
//			}
			
			web_business(C_socket);
			close(C_socket);
		}
		else exit(0);//this is important or see the picture
	}
	return 0;
}
void web_business(int C_socket)
{
	char bb[MAXLINE];
	bzero(bb,sizeof(bb));
	send(C_socket,"hello world this is a test",strlen("hello world this is a test"),0);
	//if process is killed here the server will be killd--read: Connection reset by peer	
	int size = 0;
/*
	while(1)
	{
		size = recv(C_socket,bb,sizeof(bb),0);
		
		//if(-1 == size)
		//	break;
	
		
		if (size == -1)
		{
			if(EAGAIN != errno){
				perror ("read");
				exit(0);
			}		
			break;
		}
		else if (size == 0)
		{
			// End of file. The remote has closed the connection. 
			printf("this count == 0  fd %d\n", C_socket);
//			done_ = true;
			break;
		}

		// write the buffer to remote output 
//		write(streamer_.myfd, "this is echo:", sizeof("this is echo:")-1);//sizeof() - 1 will delete the string charictor /0 
//		write(streamer_.myfd, buf, count); 

		int s = printf("the buff is %s\n", bb);
		if (s == -1){
			perror ("write");
//			return false;
		}
		
	}
*/	
//	printf("the size is %d", size);
//	printf("%s\n",bb);
//	int i = 0;
	while(size != 39)
	{
		size += recv(C_socket,bb,sizeof(bb),0);
		printf("%s", bb);
//		printf("in loop %s", bb);		
	}
	printf("\n");
//	recv(C_socket,bb,39,0);
//	recv(C_socket,bb,512,0);
//	printf("\n");
//	printf("ID %d echo is: %s\n",getpid(),bb);
//	std::cout<<bb<<std::endl;

}

/*
bool modifyFd(int fd)
{
	int flags, s;

	flags = fcntl (fd, F_GETFL, 0);
	if (flags == -1){
		perror ("fcntl");
		return false;
	}

	flags |= O_NONBLOCK;
	
	s = fcntl (fd, F_SETFL, flags);
	if (s == -1){
		perror ("fcntl");
		return false;
	}

	return true;

}
*/

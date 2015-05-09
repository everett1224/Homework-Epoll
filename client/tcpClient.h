////
// @file tcpClient.h
// @brief
// the TCP class get the socket ready
//
// @auther wangbb
// @email edelweiss1224@gmail.com
//

#ifndef _TCP_CLIENT_H_
#define _TCP_CLIENT_H_

#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include "client.h"
#include <netinet/in.h>
#include <arpa/inet.h>

class Tcp : public Client<Tcp>
{
  public:
	int getReady(char*, int);
};

int Tcp::getReady(char *ip, int port)
{
	int C_socket = socket(AF_INET,SOCK_STREAM,0);
	if(C_socket == -1)
	{
		printf("socket error\n");
		exit(1);
	}
	struct sockaddr_in ser;
	ser.sin_family = AF_INET;
	ser.sin_port = htons(port);
	ser.sin_addr.s_addr = inet_addr(ip);
	if(connect(C_socket,(struct sockaddr*)&ser,sizeof(ser)) == -1)
	{
		perror("connect error:");
		exit(1);
	}

	return C_socket;
}

#endif //_TCP_CLIENT_H_

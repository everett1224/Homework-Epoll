////
// @file client.h
// @brief
// the client Template class  
//
// @auther wangbb
// @email edelweiss1224@gmail.com
//

#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>

typedef void (*business_)(int);

class TCP;
class UDP;

template <class T>
class Client
{
  private:
	const char *serverIp_; 
	int connectSocket_;
	int serverPort_;
	//the business function
	business_ func_;

  public:
	Client();
	Client(const char* ip, int port, business_ callback);
	~Client();
	//connect the server
	void run();
	bool createSocket();
	bool getReady();
};

template <class T>
Client<T>::Client() : serverIp_(NULL), connectSocket_(0), serverPort_(0), func_(NULL){}

template <class T>
Client<T>::Client(const char* ip, int port, business_ callback) : serverIp_(ip), connectSocket_(0), serverPort_(port), func_(callback){}

template <>
bool Client<TCP>::createSocket()
{
	connectSocket_ = socket( AF_INET, SOCK_STREAM, 0);
	if ( connectSocket_ == -1 )
	{
		printf("socket error\n");
		return false;
	}
	return true;
} 

template <>
bool Client<UDP>::createSocket()
{
	connectSocket_ = socket( AF_INET, SOCK_DGRAM, 0);
	if ( connectSocket_ == -1 )
	{
		printf("socket error\n");
		return false;
	}
	return true;
} 

template <class T>
bool Client<T>::getReady()
{
	struct sockaddr_in ser;
	ser.sin_family = AF_INET;
	ser.sin_port = htons(serverPort_);
	ser.sin_addr.s_addr = inet_addr(serverIp_);
	if ( connect( connectSocket_,(struct sockaddr*)&ser,sizeof(ser) ) == -1 )
	{
		perror("connect error:");
		return false;
	}

	return true;
}


template <class T>
void Client<T>::run()
{
	if( ! createSocket() ){
		perror("socket create error");
		exit(0);
	}
	
	if( ! getReady() ){
		perror("connect error");
		exit(0);
	}
	
	func_(connectSocket_);
}

template <class T>
Client<T>::~Client()
{
	close(connectSocket_);
}

#endif //_CLIENT_H_

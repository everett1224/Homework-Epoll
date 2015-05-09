////
// @file client.h
// @brief
// the client class  
// ******************************
//
// Client design with CRTP pattern
//
// ******************************
//
// @auther wangbb
// @email edelweiss1224@gmail.com
//

#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef void (*business_)(int);

template <class T>
class Client
{
  private:
	char *serverIp_;
	int connectSocket_;
	int serverPort_;
	//the business function
	business_ func_;

  public:
	Client();
	Client(char* ip, int port, business_ callback);
	~Client();
	//connect the server
	void run();
};

template <class T>
Client<T>::Client() : serverIp_(NULL), connectSocket_(0), serverPort_(0), func_(NULL){}

template <class T>
Client<T>::Client(char* ip, int port, business_ callback) : serverIp_(ip), connectSocket_(0), serverPort_(port), func_(callback){}

template <class T>
void Client<T>::run()
{
	//get the connect socket
	connectSocket_ = static_cast<T*>(this) -> getReady(serverIp_, serverPort_); 
	
	if ( 0 == connectSocket_){
		printf("connect error\n");
		exit(0);
	}
	//static_cast<T*>(this) -> startup();
	func_(connectSocket_);
}

template <class T>
Client<T>::~Client()
{
	close(connectSocket_);
}

#endif //_CLIENT_H_

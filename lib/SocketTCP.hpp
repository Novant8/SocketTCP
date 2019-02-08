#ifndef __SOCKETTCP_HPP
#define __SOCKETTCP_HPP

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Address.hpp"
#include "mylib.h"

class SocketTCP {
protected:
	int sockfd;
public:
	SocketTCP();
	~SocketTCP();
};

SocketTCP::SocketTCP() {
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd<0)
        	error("socket()", -2);
}

SocketTCP::~SocketTCP() {
	close(sockfd);
}

#endif

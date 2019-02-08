#ifndef __CLIENTTCP_HPP
#define __CLIENTTCP_HPP

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Address.hpp"
#include "Connection.hpp"
#include "SocketTCP.hpp"

#define MAX_MSG 4096

class ClientTCP : public SocketTCP {
private:
	ClientConn* conn;
public: 
        ClientTCP();
        ~ClientTCP();
        bool    connetti(Address);
        bool    invia(char*);
        char*   ricevi();
};

ClientTCP::ClientTCP() : SocketTCP() {}

ClientTCP::~ClientTCP() {
	delete conn;
}

bool ClientTCP::connetti(Address server) {
    struct sockaddr_in server_addr = server.getSockaddr_in();
    int ret = connect(sockfd,
                    (struct sockaddr*)&server_addr,
                    sizeof(struct sockaddr_in));

    if (ret<0)
	return true;

    this->conn = new ClientConn(sockfd);

    return false;
}

bool ClientTCP::invia(char* msg) {
    conn->invia(msg);
}

char* ClientTCP::ricevi() {
    return conn->ricevi();
}

#endif //__CLIENTTCP_HPP

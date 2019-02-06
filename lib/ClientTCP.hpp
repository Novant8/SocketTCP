#ifndef __CLIENTTCP_HPP
#define __CLIENTTCP_HPP

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Address.hpp"

#define MAX_MSG 4096

class ClientTCP {
    private: 
        int     sockfd;
    
    public: 
        ClientTCP();
        ~ClientTCP();
        bool    connetti(Address);
        bool    invia(char*);
        char*   ricevi();
};

ClientTCP::ClientTCP() {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
}

ClientTCP::~ClientTCP() {
    close(sockfd);
}

bool ClientTCP::connetti(Address server) {
    struct sockaddr_in server_addr = server.getSockaddr_in();
    int ret= connect(sockfd,
                    (struct sockaddr*)&server_addr,
                    sizeof(struct sockaddr_in));
    return (ret!=0);
}

bool ClientTCP::invia(char* msg) {
    int msg_len = strlen(msg);
    int ret = send(sockfd, msg, msg_len, 0);
    return (ret!=msg_len);
}

char* ClientTCP::ricevi() {
    char buffer[MAX_MSG+1];
    int msg_len = recv(sockfd,
                       buffer,
                       MAX_MSG, 0);
    if(msg_len == 0) return NULL;
    buffer[msg_len] = '\0';
    return strdup(buffer);
}

#endif //__CLIENTTCP_HPP

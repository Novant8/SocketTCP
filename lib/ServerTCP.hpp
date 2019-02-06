#ifndef __SERVERTCP_HPP
#define __SERVERTCP_HPP

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Address.hpp"
#include "mylib.h"

#define MAX_MSG 4096
#define MAX_CONN 50
#define IP_LO "127.0.0.1"

class Connessione {
private:
    int conn_id;
    Address client;
    
public:
    Connessione(int, Address);
    ~Connessione();
    bool    invia(char*);
    char*   ricevi();
    Address getClient();
};

class ServerTCP {
private:
    int sockfd;
    
public:
    ServerTCP(int);
    ServerTCP(int, int);
    ~ServerTCP();
    Connessione accetta();
};

ServerTCP::ServerTCP(int port, int max_connections) {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd<0)
        error("socket()", -2);
    
    Address myself(IP_LO, port);
    struct sockaddr_in myself_binary = myself.getSockaddr_in();
    myself_binary.sin_family = AF_INET;
    for(int i=0; i<8; i++)
        myself_binary.sin_zero[i] = 0;
    int ret = bind(sockfd,
                   (struct sockaddr*)&myself_binary,
                   (socklen_t)sizeof(struct sockaddr));
    if(ret!=0)
        error("bind()", -3);
    
    
    listen(sockfd, max_connections);
    if(ret!=0)
        error("listen()", -4);
}

ServerTCP::ServerTCP(int port) : ServerTCP(port, MAX_CONN) {}

ServerTCP::~ServerTCP() {
    close(sockfd);
}

Connessione ServerTCP::accetta() {
    struct sockaddr_in src;
    int len_client_addr = sizeof(struct sockaddr_in);
    int conn_id = accept(sockfd,
                         (struct sockaddr*)&src,
                         (socklen_t*)&len_client_addr);
    if(conn_id<0)
        error("accept()", -4);
    
    Address client(src);
    Connessione conn(conn_id, client);
    
    return conn;
}

Connessione::Connessione(int conn_id, Address client) {
    this->conn_id = conn_id;
    this->client = client;
}

Connessione::~Connessione() {
    shutdown(conn_id, SHUT_RDWR);
}

bool Connessione::invia(char* msg) {
    int msg_len = strlen(msg);
    int ret = send(conn_id, msg, msg_len, 0);
    return (ret!=msg_len);
}

char* Connessione::ricevi() {
    char buffer[MAX_MSG+1];
    int msg_len = recv(conn_id,
                       buffer,
                       MAX_MSG, 0);
    if(msg_len == 0) return NULL;
    buffer[msg_len] = '\0';
    return strdup(buffer);
}

Address Connessione::getClient() {
    return client;
}

#endif //__SERVERTCP_HPP

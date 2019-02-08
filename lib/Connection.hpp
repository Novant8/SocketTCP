#ifndef __CONNECTION_HPP
#define __CONNECTION_HPP

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Address.hpp"
#include "mylib.h"

#define MAX_MSG 4096

class Connection {
protected:
    int conn_id;
    
public:
    Connection(int, Address*);
    Connection(int);
    ~Connection();
    bool    invia(char*);
    char*   ricevi();
    Address getClient();
};

class ClientConn : public Connection {
public:
	ClientConn(int conn_id);
	~ClientConn();
};

class ServerConn : public Connection {
private:
	Address* client;
public:
	ServerConn(int conn_id, Address* client);
	~ServerConn();
	Address* getClient();
};

Connection::Connection(int conn_id) {
	this->conn_id = conn_id;
}

Connection::~Connection() {}

bool Connection::invia(char* msg) {
    int msg_len = strlen(msg);
    int ret = send(conn_id, msg, msg_len, 0);
    return (ret!=msg_len);
}

char* Connection::ricevi() {
    char buffer[MAX_MSG+1];
    int msg_len = recv(conn_id,
                       buffer,
                       MAX_MSG, 0);
    if(msg_len == 0) return NULL;
    buffer[msg_len] = '\0';
    return strdup(buffer);
}

ClientConn::ClientConn(int conn_id) : Connection(conn_id) {}

ClientConn::~ClientConn() {
	close(conn_id);
}

ServerConn::ServerConn(int conn_id, Address* client) : Connection(conn_id) {
	this->client = client;
}

ServerConn::~ServerConn() {
    delete client;
    shutdown(conn_id, SHUT_RDWR);
}

Address* ServerConn::getClient() {
    return client;
}

#endif //__SERVERTCP_HPP

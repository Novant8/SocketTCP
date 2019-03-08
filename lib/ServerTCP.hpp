#ifndef __SERVERTCP_HPP
#define __SERVERTCP_HPP

#include "SocketTCP.hpp"
#include "Connection.hpp"
#include <list>


#define MAX_CONN 50
#define IP_LO "127.0.0.1"

class ServerTCP : SocketTCP {
private:
    std::list<ServerConn*> conns;
    void chiudiConnessioni();
public:
    ServerTCP(int);
    ServerTCP(int, int);
    ServerConn* accetta();
    void inviaBroadcast(char*);
    void inviaRawBroadcast(void*, int);
    void chiudiConnessione(ServerConn*);
    ~ServerTCP();
};

ServerTCP::ServerTCP(int port, int max_connections) : SocketTCP() {  
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

ServerConn* ServerTCP::accetta() {

    struct sockaddr_in src;
    int len_client_addr = sizeof(struct sockaddr_in);
    int conn_id = accept(sockfd,
                         (struct sockaddr*)&src,
                         (socklen_t*)&len_client_addr);
    if(conn_id<0)
        error("accept()", -4);
    

    ServerConn* conn = (ServerConn*)malloc(sizeof(ServerConn));
    conn = new ServerConn(conn_id, new Address(src));
    conns.push_front(conn);
    
    return conn;
}

void ServerTCP::inviaBroadcast(char* msg) {
    std::list<ServerConn*>::iterator it;
    for(it = conns.begin(); it!=conns.end(); it++) {
        (*it)->invia(msg);
	delete *it;
    }
}

void ServerTCP::inviaRawBroadcast(void* msg, int length) {
    //Aggiungere prima inviaRaw nella classe Connessione
}

void ServerTCP::chiudiConnessione(ServerConn* conn) {
    conns.remove(conn);
    delete conn;
}

void ServerTCP::chiudiConnessioni() {
    //TOGLIERE FOR, METTERE WHILE
    inviaBroadcast("Sto chiudendo la connessione...");
    std::list<ServerConn*>::iterator it;
    for(it = conns.begin(); it!=conns.end(); it++) {
        chiudiConnessione(*it);
	delete *it;
    }
}

ServerTCP::~ServerTCP() {
    chiudiConnessioni();
}

#endif //__SERVERTCP_HPP

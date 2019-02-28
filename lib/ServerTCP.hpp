#ifndef __SERVERTCP_HPP
#define __SERVERTCP_HPP

#include "SocketTCP.hpp"
#include "Connection.hpp"
<<<<<<< HEAD
#include <list>
=======
>>>>>>> aad6f342e07178444779ce215a08129506509632

#define MAX_CONN 50
#define IP_LO "127.0.0.1"

<<<<<<< HEAD
class ServerTCP : SocketTCP {
private:
    std::list<ServerConn*> conns;
public:
    ServerTCP(int);
    ServerTCP(int, int);
    ServerConn* accetta();
    void inviaBroadcast(char*);
    void cancellaConnessione(ServerConn*);
    ~ServerTCP();
=======
class ServerTCP : SocketTCP {    
public:
    ServerTCP(int);
    ServerTCP(int, int);
    ServerConn accetta();
>>>>>>> aad6f342e07178444779ce215a08129506509632
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

<<<<<<< HEAD
ServerConn* ServerTCP::accetta() {
=======
ServerConn ServerTCP::accetta() {
>>>>>>> aad6f342e07178444779ce215a08129506509632
    struct sockaddr_in src;
    int len_client_addr = sizeof(struct sockaddr_in);
    int conn_id = accept(sockfd,
                         (struct sockaddr*)&src,
                         (socklen_t*)&len_client_addr);
    if(conn_id<0)
        error("accept()", -4);
    
<<<<<<< HEAD
    ServerConn* conn = (ServerConn*)malloc(sizeof(ServerConn));
    
    conn = new ServerConn(conn_id, new Address(src));
        
    conns.push_front(conn);
=======
    ServerConn conn(conn_id, new Address(src));
>>>>>>> aad6f342e07178444779ce215a08129506509632
    
    return conn;
}

<<<<<<< HEAD
void ServerTCP::inviaBroadcast(char* msg) {
    std::list<ServerConn*>::iterator it;
    for(it = conns.begin(); it!=conns.end(); it++) {
        (*it)->invia(msg);
    }
}

void ServerTCP::cancellaConnessione(ServerConn* conn) {
    conns.remove(conn);
}

ServerTCP::~ServerTCP() {
    inviaBroadcast("Sto chiudendo la connessione...");
    std::list<ServerConn*>::iterator it;
    for(it = conns.begin(); it!=conns.end(); it++) {
        delete *it;
    }
    conns.clear();
}

=======
>>>>>>> aad6f342e07178444779ce215a08129506509632
#endif //__SERVERTCP_HPP

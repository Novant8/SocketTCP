#include "lib/ServerTCP.hpp"

int main(int argc, char** argv) {
    
    if(argc != 3) {
        printf("USAGE: %s PORT RESPONSE_MSG\n", *argv);
        return -1;
    }
    
    int port = atoi(argv[1]);
    char* msg = argv[2];
    
    printf("Creating server and listening...\n");
    ServerTCP myself(port);
    printf("OK!\n");
    
    printf("Accepting connection...\n");
<<<<<<< HEAD
    ServerConn* conn = myself.accetta();
    Address* client = conn->getClient();
    printf("Connection inbound from [%s]\n", client->toString());
    
    printf("Waiting for messages...\n");
    char* answer = conn->ricevi();
=======
    ServerConn conn = myself.accetta();
    Address* client = conn.getClient();
    printf("Connection inbound from [%s]\n", client->toString());
    
    printf("Waiting for messages...\n");
    char* answer = conn.ricevi();
>>>>>>> aad6f342e07178444779ce215a08129506509632
    if(msg == NULL)
        error("recv()", -5);
    printf("Message recieved from [%s]: %s\n", client->toString(), answer);
    
    printf("Sending response...\n");
<<<<<<< HEAD
    if(conn->invia(msg)) {
=======
    if(conn.invia(msg)) {
>>>>>>> aad6f342e07178444779ce215a08129506509632
        error("send()", -6);
    }
    
    
    return 0;
    
}

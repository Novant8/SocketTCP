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
    ServerConn conn = myself.accetta();
    Address* client = conn.getClient();
    printf("Connection inbound from [%s]\n", client->toString());
    
    printf("Waiting for messages...\n");
    char* answer = conn.ricevi();
    if(msg == NULL)
        error("recv()", -5);
    printf("Message recieved from [%s]: %s\n", client->toString(), answer);
    
    printf("Sending response...\n");
    if(conn.invia(msg)) {
        error("send()", -6);
    }
    
    
    return 0;
    
}

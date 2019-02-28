#include "lib/ClientTCP.hpp"
#include "lib/mylib.h"

int main(int argc, char** argv) {
    
    if (argc != 4) {
        printf("USAGE: %s IP PORT MSG\n", *argv);
        return -1;
    }
    
    char* ip = argv[1];
    int port = atoi(argv[2]);
    char* msg = argv[3];
<<<<<<< HEAD

=======
    
>>>>>>> aad6f342e07178444779ce215a08129506509632
    printf("Creating socket...\n");
    ClientTCP myself;
    printf("OK!\n");
    
    Address dest(ip, port);
    printf("Connecting to address %s...\n", dest.toString());
    if(myself.connetti(dest))
        error("connect()", -2);
    printf("Connected!\n");
    
    printf("Sending message to server...\n");
    if(myself.invia(msg))
        error("send()", -3);
    printf("Message sent!\n");
    
    printf("Waiting for response from server...\n");
    char* answer = myself.ricevi();
    if(answer == NULL) 
        error("recieve()", -4);
    printf("Message recieved from server: %s\n", answer);
    
    return 0;
}

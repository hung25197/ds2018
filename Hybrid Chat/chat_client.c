#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <signal.h>
#include <netinet/in.h>

void *get_in_addr(struct sockaddr *sv_address)
{
    return &(((struct sockaddr_in*)sv_address)->sin_addr);
}

int main(int argc, char* argv[]) {
//----------------------------------INIT CLIENT Connection to SERVER----------------------------------
    int serv;
    struct sockaddr_in sv_address;

    socklen_t ad_length = sizeof(sv_address);
    struct hostent *hostend_ip;

    // create socket
    serv = socket(AF_INET, SOCK_STREAM, 0);

    // init address
    hostend_ip = gethostbyname(argv[1]);
    memset(&sv_address, 0, sizeof(sv_address));
    sv_address.sin_family = AF_INET;
    sv_address.sin_addr = *(struct in_addr *)hostend_ip->h_addr_list[0];
    sv_address.sin_port = htons(12345);

    // connect to server
    connect(serv, (struct sockaddr *)&sv_address, ad_length);
    // after connected, make client thread to send mess to server


//----------------------------------INIT CLIENT wait for incomming peer----------------------------------    

    int mysocket,peer,pid_write,pid_read;
    struct sockaddr_in incomming_addr;
    char peer_ip[100];
    socklen_t inaddr_length = sizeof(incomming_addr);
    
    // create the socket
    mysocket = socket(AF_INET, SOCK_STREAM, 0);

    // bind the socket to port 12355 (10 port from 12345)
    memset(&incomming_addr, 0, sizeof(incomming_addr));
    incomming_addr.sin_family = AF_INET;    
    incomming_addr.sin_addr.s_addr = INADDR_ANY;
    incomming_addr.sin_port = htons(12355);
    bind(mysocket, (struct sockaddr *)&incomming_addr, inaddr_length);

    // then listen
    listen(mysocket, 5);
    printf("Client as server initilize successfully\n");
    
    while (1) {
        peer = accept(mysocket, (struct sockaddr *)&incomming_addr, &inaddr_length);
        printf("peer %d connected\n",peer);    

        inet_ntop(AF_INET, &(incomming_addr.sin_addr), peer_ip, sizeof(peer_ip));
        printf("Me: got connection from %s\n", peer_ip);
    }



    // pid_write = fork();

    // inet_ntop(AF_INET, get_in_addr((struct sockaddr *)&incomming_addr), s1, sizeof(s1));
    // printf("client as server: got connection from %s\n", so);

    // if (pid_write == 0) {
    //     // I'm the son, I'll serve send to this client
    //     while (1) {
    //         // now it's my (server) turn
    //         // keep read mess and send to client
    //         fgets(s, 95, stdin);
    //         int numwrite = write(peer, s, strlen(s) + 1);
    //     }

        
    // } else {
    //     // If the father, create thread to receive from client
    //     pid_read = fork();
    //     if (pid_read == 0)
    //     {   
    //         // I'm the son, I'll serve receive from this client
    //         // but I have the writing thread PID from father
    //         while (1) {
    //             // I wait and read message from client
    //             int numread = read(peer, s, sizeof(s));
    //             if (numread != 0)
    //             {
    //                 // read success, print mess
    //                 printf("client %d says: %s\n",peer,s);    
    //             } else {
    //                 // read fail, disconnected, kill the writing thread.
    //                 printf("client %d disconnected\n", peer);
    //                 kill(pid_write,SIGKILL);
    //                 // break out to close socket and end reading thread.
    //                 break;
    //             }
                
    //         }
    //         close(peer);
    //         return 0;
    //     } else {
    //         // I'm the father, continue the loop to accept more clients
    //         continue;    
    //     }
    // } 
    // }  


  
    
    


    // pid_write = fork();

    // if (pid_write == 0)
    // {   
    // // I'm the son, I'm keep reading and sending mess
    //     while (1) {
    //         // read line and send data to server
    //         fgets(s, 95, stdin);
    //         int numwrite = write, s, strlen(s) + 1);
    //     }
    
    // }
    // // I'm the father, I handle reading
    // while(1){
    //     // keep reading
    //     int numread = read, s, sizeof(s));
    //     if (numread != 0)
    //     {
    //         // if numread > 0, read success, print mess
    //         printf("server says: %s\n", s);    
    //     } else {
    //         // read fail, disconnect
    //         printf("server disconnected\n");
    //         // kill the son writing thread
    //         kill(pid_write,SIGKILL);
    //         // break to end
    //         break;
    //     }
    
    // }
        

    // close);
    // return 0;
}
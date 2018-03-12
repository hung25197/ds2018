#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <signal.h>
#include <netinet/in.h>

int main() {
//----------------------------------INIT SERVER----------------------------------
    int mysocket, cli, pid_write, pid_read;
    struct sockaddr_in socket_address;
    char cli_ip[100];
    socklen_t skaddr_length = sizeof(socket_address);

    // create the socket
    mysocket = socket(AF_INET, SOCK_STREAM, 0);

    // bind the socket to port 12345
    memset(&socket_address, 0, sizeof(socket_address));
    socket_address.sin_family = AF_INET;
    socket_address.sin_addr.s_addr = INADDR_ANY;
    socket_address.sin_port = htons(12345);
    bind(mysocket, (struct sockaddr *)&socket_address, skaddr_length);

    // then listen
    listen(mysocket, 0);
    printf("Server init complete\n");

    char mess[100];

//----------------------------------STANDBY FOR CONNECTION----------------------------------
    while (1) {
        // an incoming connection
        cli = accept(mysocket, (struct sockaddr *)&socket_address, &skaddr_length);
        printf("client %d connected\n",cli);

        inet_ntop(AF_INET, &(socket_address.sin_addr), cli_ip, sizeof(cli_ip));
        printf("server: got connection from %s\n", cli_ip);

        // create process to serve this client
        pid_client = fork()

        if (pid_client == 0)
        {
            // I'm the son, I'll serve this client

            // do login checking, searching, trading info
            // bla bla bla

            // after doing stuff, just put this checking client status here
            while (1) {
                // I wait and read message from client
                int numread = read(cli, mess, sizeof(mess));
                if (numread != 0)
                {
                    // read success, print mess
                    printf("client %d says: %s\n",cli,mess);    
                } else {
                    // read fail, client disconnected.
                    printf("client %d disconnected\n", cli);
                    // break out to close socket and end reading thread.
                    break;
                }
            }
            close(cli);
            return 0;

        } else {
            // I'm the father, I continue to accept more client
            continue;
        }

        /*
        // // create process to send from server to client
        // pid_write = fork();


        // if (pid_write == 0) {
        //     // I'm the son, I'll serve send to this client
        //     while (1) {
        //         // now it's my (server) turn
        //         // keep read mess and send to client
        //         fgets(mess, 95, stdin);
        //         int numwrite = write(cli, mess, strlen(mess) + 1);
        //     }
        // } else {
        //     // If the father, create process to receive from client
        //     pid_read = fork();
        //     if (pid_read == 0)
        //     {   
        //         // I'm the son, I'll serve receive from this client
        //         // but I have the writing process PID from father
        //         while (1) {
        //             // I wait and read message from client
        //             int numread = read(cli, mess, sizeof(mess));
        //             if (numread != 0)
        //             {
        //                 // read success, print mess
        //                 printf("client %d says: %s\n",cli,mess);    
        //             } else {
        //                 // read fail, disconnected, kill the writing thread.
        //                 printf("client %d disconnected\n", cli);
        //                 kill(pid_write,SIGKILL);
        //                 // break out to close socket and end reading thread.
        //                 break;
        //             }
        //         }
        //         close(cli);
        //         return 0;
        //     } else {
        //         // I'm the father, continue the loop to accept more clients
        //         continue;    
        //     }
        // }   
        */
    }
    return 0;
}





#include<stdio.h>       // Standard input-output functions
#include<stdlib.h>      // Standard library functions
#include<string.h>      // String manipulation functions
#include<sys/socket.h>  // Socket programming functions
#include<sys/types.h>   // Data types for sockets
#include<netinet/in.h>  // Structures for internet operations
#include<arpa/inet.h>   // Functions for IP address operations

#define port 5000  // Defining the port number for communication

int main()
{
    struct sockaddr_in serveraddr;  // Structure to store server address details
    int clisocket;                  // Client socket descriptor
    char IPaddr[100];                // Buffer to store the client's IP address

    // Creating a TCP socket (SOCK_STREAM indicates TCP)
    clisocket = socket(PF_INET, SOCK_STREAM, 0);
    if (clisocket > 0)  // Checking if the socket was successfully created
        printf("\nClient socket created");

    // Defining server details
    serveraddr.sin_family = PF_INET;             // Address family: Internet Protocol (IPv4)
    serveraddr.sin_port = htons(port);           // Setting port number, converting to network byte order
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");  // Converting IP string to binary form

    // Connecting to the server
    connect(clisocket, (struct sockaddr*)&serveraddr, sizeof(serveraddr));

    // Converting the server's IP address to a string format
    strcpy(IPaddr, inet_ntoa(serveraddr.sin_addr));

    // Sending the IP address of the client to the server
    send(clisocket, IPaddr, sizeof(IPaddr), 0);
    printf("\nIP address of client sent to server\n");

    // Closing the client socket
    close(clisocket);

    return 0;
}

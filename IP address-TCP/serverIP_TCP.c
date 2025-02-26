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
    struct sockaddr_in serveraddr, newaddr;  // Structures to store server and client addresses
    int sersocket, newsocket, s, size;
    char buffer[100];  // Buffer to store the received data (IP address)

    // Creating a TCP socket
    sersocket = socket(PF_INET, SOCK_STREAM, 0);
    if (sersocket > 0)  // Checking if the socket was successfully created
        printf("\nServer socket is created");

    // Defining server details
    serveraddr.sin_family = PF_INET;          // Address family: Internet Protocol (IPv4)
    serveraddr.sin_port = htons(port);        // Setting port number, converting to network byte order
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);  // Accept connections from any IP address

    // Binding the socket to the specified IP and port
    s = bind(sersocket, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    if (s == 0)  // Checking if bind was successful
        printf("\nBind success");

    // Listening for incoming client connections (maximum 1 in queue)
    listen(sersocket, 1);
    size = sizeof(newaddr);
    printf("\nServer ready, waiting for client...");

    // Accepting the connection from the client
    newsocket = accept(sersocket, (struct sockaddr *)&newaddr, &size);
    if (newsocket > 0)
        printf("\nClient connected");

    // Receiving the client's IP address
    recv(newsocket, buffer, sizeof(buffer), 0);
    printf("\nIP address received from client: %s\n", buffer);

    // Closing the server socket
    close(sersocket);

    return 0;
}

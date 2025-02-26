#include<stdio.h>       // Standard I/O functions
#include<stdlib.h>      // Standard library functions
#include<string.h>      // String manipulation functions
#include<sys/socket.h>  // Socket functions
#include<sys/types.h>   // Data types for sockets
#include<netinet/in.h>  // Internet address structures
#include<arpa/inet.h>   // Functions for IP address manipulation
#include<unistd.h>      // Close function for sockets

#define PORT 5000  // Defining the port number

int main()
{
    struct sockaddr_in serveraddr, newaddr; // Server and client address structures
    int sersocket, newsocket, s, size;
    char buffer[100];

    // Create a TCP socket
    sersocket = socket(PF_INET, SOCK_STREAM, 0);
    if (sersocket < 0) {
        perror("Socket creation failed");
        exit(1);
    }
    printf("\nServer socket created");

    // Define server details
    serveraddr.sin_family = PF_INET;
    serveraddr.sin_port = htons(PORT);
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

    // Bind the socket to the server address
    s = bind(sersocket, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    if (s < 0) {
        perror("Binding failed");
        close(sersocket);
        exit(1);
    }
    printf("\nBind successful");

    // Start listening for incoming connections (max queue: 1)
    listen(sersocket, 1);
    printf("\nServer ready, waiting for a client...");

    size = sizeof(newaddr);

    // Accept an incoming connection
    newsocket = accept(sersocket, (struct sockaddr*)&newaddr, (socklen_t*)&size);
    if (newsocket < 0) {
        perror("Connection acceptance failed");
        close(sersocket);
        exit(1);
    }
    printf("\nClient connected");

    // Receive IP address from client
    recv(newsocket, buffer, sizeof(buffer), 0);
    printf("\nIP address received: %s", buffer);

    // Receive MAC address from client
    recv(newsocket, buffer, sizeof(buffer), 0);
    printf("\nMAC address received: %s\n", buffer);

    // Close sockets
    close(newsocket);
    close(sersocket);

    return 0;
}

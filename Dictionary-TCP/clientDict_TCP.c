#include<stdio.h>       // Standard I/O functions
#include<stdlib.h>      // Standard library functions
#include<string.h>      // String manipulation functions
#include<sys/socket.h>  // Socket functions
#include<sys/types.h>   // Data types for sockets
#include<netinet/in.h>  // Internet address structures
#include<arpa/inet.h>   // Functions for IP address manipulation
#include<unistd.h>      // Close function for sockets

#define PORT 5000  // Define the port number

int main()
{
    struct sockaddr_in serveraddr;
    int clisocket;
    char buffer[100];

    // Create a TCP socket
    clisocket = socket(PF_INET, SOCK_STREAM, 0);
    if (clisocket < 0) {
        perror("Socket creation failed");
        exit(1);
    }
    printf("\nClient socket created");

    // Define server details
    serveraddr.sin_family = PF_INET;
    serveraddr.sin_port = htons(PORT);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to the server
    if (connect(clisocket, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) < 0) {
        perror("Connection to server failed");
        close(clisocket);
        exit(1);
    }
    printf("\nConnected to dictionary server");

    // Get word input from the user
    printf("\nEnter word to be searched in dictionary: ");
    scanf("%s", buffer);

    // Send the word to the server
    send(clisocket, buffer, sizeof(buffer), 0);

    // Receive meaning from the server
    recv(clisocket, buffer, sizeof(buffer), 0);
    printf("Meaning - %s\n", buffer);

    // Receive antonym from the server
    recv(clisocket, buffer, sizeof(buffer), 0);
    printf("Antonym - %s\n", buffer);

    // Close the client socket
    close(clisocket);

    return 0;
}

#include<stdio.h>      // Standard input-output library for printf, fgets, etc.
#include<arpa/inet.h>  // Contains functions and structures for internet operations (like sockaddr_in, inet_addr, etc.)

#define port 4000      // Defining the port number for communication

void main() {
    struct sockaddr_in serveraddr, newaddr;  // Structures to hold server and client address information
    int sersocket, size, s;  // Server socket descriptor, size of client address structure, and bind status
    char buffer[100];  // Buffer to store messages

    // Creating a UDP socket (SOCK_DGRAM for UDP communication)
    sersocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (sersocket > 0)  // If socket creation is successful
        printf("\nServer socket created");

    // Defining server details
    serveraddr.sin_family = AF_INET;  // Setting the address family to IPv4
    serveraddr.sin_port = htons(port);  // Setting the port number, converting it to network byte order
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);  // Accept connections from any IP address

    // Binding the socket to the specified IP address and port
    s = bind(sersocket, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    if (s == 0)  // If binding is successful
        printf("\nBind success");

    size = sizeof(newaddr);  // Storing the size of client address structure

    while (1) {  // Infinite loop for continuous chat until "bye" is received
        // Receiving message from the client using recvfrom()
        recvfrom(sersocket, buffer, sizeof(buffer), 0, (struct sockaddr*)&newaddr, &size);
        printf("\nFrom client: %s", buffer);  // Printing received message

        if (strcmp(buffer, "bye\n") == 0)  // If received message is "bye", exit the loop
            break;
        else
            printf("\tTo client: ");

        fgets(buffer, sizeof(buffer), stdin);  // Taking server's response as input

        // Sending message to the client using sendto()
        sendto(sersocket, buffer, sizeof(buffer), 0, (struct sockaddr*)&newaddr, sizeof(newaddr));
    }

    // Closing the server socket after chat ends
    close(sersocket);
}

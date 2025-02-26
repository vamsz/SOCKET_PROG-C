#include<stdio.h>      // Standard input-output library for printf, fgets, etc.
#include<arpa/inet.h>  // Contains functions and structures for internet operations (like sockaddr_in, inet_addr, etc.)

#define port 4000      // Defining the port number for communication

void main() {
    struct sockaddr_in serveraddr;  // Structure to hold server address information
    int clisocket, size;  // Client socket descriptor and variable to store server address size
    char buffer[100];  // Buffer to store messages

    // Creating a UDP socket (SOCK_DGRAM for UDP communication)
    clisocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (clisocket > 0)  // If socket creation is successful
        printf("\nClient socket created");

    // Defining server details
    serveraddr.sin_family = AF_INET;  // Setting the address family to IPv4
    serveraddr.sin_port = htons(port);  // Setting the port number, converting it to network byte order
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");  // Setting the IP address of the server (localhost)

    while (1) {  // Infinite loop for continuous chat until "bye" is sent
        printf("\nTo server: ");
        fgets(buffer, sizeof(buffer), stdin);  // Taking input from the user
        
        // Sending message to the server using sendto()
        sendto(clisocket, buffer, sizeof(buffer), 0, (struct sockaddr*)&serveraddr, sizeof(serveraddr));

        if (strcmp(buffer, "bye\n") == 0)  // If sent message is "bye", exit the loop
            break;

        size = sizeof(serveraddr);  // Storing the size of server address structure
        
        // Receiving message from the server using recvfrom()
        recvfrom(clisocket, buffer, sizeof(buffer), 0, (struct sockaddr*)&serveraddr, &size);
        printf("\tFrom server: %s", buffer);  // Printing the received message
    }

    // Closing the client socket after chat ends
    close(clisocket);
}

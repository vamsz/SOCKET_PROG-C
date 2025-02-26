#include<stdio.h>      // Standard input-output library for printf, fgets, etc.
#include<arpa/inet.h>  // Contains functions and structures for internet operations (like sockaddr_in, inet_addr, etc.)
#include<string.h>     // For string functions like strcmp()

#define port 5000      // Defining the port number for communication

// Function to handle chat communication between server and client
void chat(int clisocket) {
    char buffer[100];  // Buffer to store messages
    while(1) {         // Infinite loop for continuous chat until "bye" is received
        recv(clisocket, buffer, sizeof(buffer), 0);  // Receiving message from client
        printf("\nFrom client: %s", buffer);  // Printing received message
        
        if(strcmp(buffer, "bye\n") == 0)  // If received message is "bye", exit the loop
            break;

        printf("\tTo client: ");
        fgets(buffer, sizeof(buffer), stdin);  // Taking server's response as input

        send(clisocket, buffer, sizeof(buffer), 0);  // Sending message to the client
    }
}

void main() {
    int serversocket, clisocket;  // Variables to store server and client socket descriptors
    struct sockaddr_in serveraddr, clientaddr;  // Structures to hold server and client address information
    socklen_t len;  // Variable to store size of client address structure

    serversocket = socket(PF_INET, SOCK_STREAM, 0);  // Creating a socket for communication
    if (serversocket > 0)  // If socket creation is successful
        printf("Server socket created\n");

    serveraddr.sin_family = PF_INET;  // Setting the address family to IPv4
    serveraddr.sin_port = htons(port);  // Setting the port number, converting it to network byte order
    serveraddr.sin_addr.s_addr = INADDR_ANY;  // Accept connection from any IP address
    
    // Binding the socket to the specified IP address and port
    bind(serversocket, (struct sockaddr*)&serveraddr, sizeof(serveraddr));

    // Listening for incoming connections (maximum queue length set to 5)
    listen(serversocket, 5);
    printf("Waiting for client connection...\n");

    len = sizeof(clientaddr);  // Storing the size of client address structure
    // Accepting a connection from a client
    clisocket = accept(serversocket, (struct sockaddr*)&clientaddr, &len);
    printf("Client connected\n");

    // Start chatting with the client
    chat(clisocket);
    
    // Close the client socket after chat ends
    close(clisocket);
    // Close the server socket
    close(serversocket);
}

#include<stdio.h>      // Standard input-output library for printf, fgets, etc.
#include<arpa/inet.h>  // Contains functions and structures for internet operations (like sockaddr_in, inet_addr, etc.)

#define port 5000      // Defining the port number for communication

// Function to handle chat communication between client and server
void chat(int clisocket) {
    char buffer[100];  // Buffer to store messages
    while(1) {         // Infinite loop for continuous chat until "bye" is received
        printf("\nTo server:");  
        fgets(buffer, sizeof(buffer), stdin);  // Taking input from the user
        
        send(clisocket, buffer, sizeof(buffer), 0);  // Sending the message to the server
        
        recv(clisocket, buffer, sizeof(buffer), 0);  // Receiving the response from the server
        printf("\tFrom server:%s", buffer);  // Printing the received message
        
        if(strcmp(buffer, "bye\n") == 0) // If received message is "bye", exit the loop
            break;
    }
}

// Main function to establish a connection with the server
void main() {
    int clisocket;  // Variable to store the client socket descriptor
    struct sockaddr_in serveraddr;  // Structure to hold server address information

    clisocket = socket(PF_INET, SOCK_STREAM, 0);  // Creating a socket for communication
    if(clisocket > 0)  // If socket creation is successful
        printf("Client socket created\n");

    serveraddr.sin_family = PF_INET;  // Setting the address family to IPv4
    serveraddr.sin_port = htons(port);  // Setting the port number, converting it to network byte order
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");  // Setting the IP address of the server (localhost)
    
    // Connecting to the server
    connect(clisocket, (struct sockaddr*)&serveraddr, sizeof(serveraddr));

    // Start chatting with the server
    chat(clisocket);
    
    // Close the socket connection after chat ends
    close(clisocket);
}

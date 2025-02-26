#include<stdio.h>       // Standard input-output functions
#include<arpa/inet.h>   // Contains socket-related structures and functions
#include<string.h>      // For string operations like strcpy
#define port 5000       // Defining the port number for communication

int main() 
{
    struct sockaddr_in serveraddr;  // Structure to store server address details
    int clisocket;                  // Client socket descriptor
    char buffer[100];                // Buffer to store username, password, and responses

    // Creating a TCP socket (SOCK_STREAM indicates TCP)
    clisocket = socket(PF_INET, SOCK_STREAM, 0);
    if (clisocket > 0)  // Checking if the socket was successfully created
        printf("\nClient socket created");

    // Defining server details
    serveraddr.sin_family = PF_INET;            // Address family: Internet Protocol (IPv4)
    serveraddr.sin_port = htons(port);          // Setting port number, converting to network byte order
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");  // Setting server IP address (localhost)

    // Establishing connection to the server
    if (connect(clisocket, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) == 0)
        printf("\nConnected to the server\n");
    else {
        printf("\nConnection failed\n");
        return 1;  // Exit if connection fails
    }

    // Sending Username
    printf("\nUSERNAME: ");
    scanf("%s", buffer);        // Taking username input from the user
    send(clisocket, buffer, strlen(buffer) + 1, 0); // Sending username to the server

    // Sending Password
    printf("PASSWORD: ");
    scanf("%s", buffer);        // Taking password input from the user
    send(clisocket, buffer, strlen(buffer) + 1, 0); // Sending password to the server

    // Receiving authentication response from server
    recv(clisocket, buffer, sizeof(buffer), 0);
    printf("%s", buffer);  // Printing the server response (e.g., login success/failure)

    // Closing the client socket
    close(clisocket);
    
    return 0;
}

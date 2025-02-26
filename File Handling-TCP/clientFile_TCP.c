#include <stdio.h>      // Standard I/O functions
#include <string.h>     // String manipulation functions
#include <arpa/inet.h>  // Networking functions (inet_addr, socket, etc.)

#define PORT 5000  // Define the port number

void main()
{
    struct sockaddr_in serveraddr; // Structure to store server details
    int clisocket;                 // Socket file descriptor
    char buffer[100];               // Buffer to store input data

    // Step 1: Create a TCP socket
    clisocket = socket(PF_INET, SOCK_STREAM, 0);
    if (clisocket > 0)
        printf("Client socket created");

    // Step 2: Define server address properties
    serveraddr.sin_family = PF_INET;                // Address family (IPv4)
    serveraddr.sin_port = htons(PORT);              // Convert port to network byte order
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");  // Server IP address (localhost)

    // Step 3: Connect to the server
    connect(clisocket, (struct sockaddr*)&serveraddr, sizeof(serveraddr));

    // Step 4: Get user input
    printf("\nEnter data: ");
    fgets(buffer, 100, stdin);  // Read input from the user

    // Step 5: Send the data to the server
    write(clisocket, buffer, strlen(buffer) + 1);

    // Step 6: Close the client socket
    close(clisocket);
}

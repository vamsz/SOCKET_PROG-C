#include <stdio.h>      // Standard I/O functions
#include <arpa/inet.h>  // Networking functions (socket, connect, etc.)

#define PORT 5000  // Define the port number

void main() {
    struct sockaddr_in serveraddr;  // Structure to store server details
    int clisocket;                  // Client socket descriptor
    char buffer[100];                // Buffer to store user input

    // Step 1: Create a TCP socket
    clisocket = socket(PF_INET, SOCK_STREAM, 0);
    if (clisocket > 0)
        printf("\nClient socket created");

    // Step 2: Define server address properties
    serveraddr.sin_family = PF_INET;             // Use IPv4
    serveraddr.sin_port = htons(PORT);           // Convert port to network byte order
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");  // Server IP (localhost)

    // Step 3: Connect to the server
    connect(clisocket, (struct sockaddr*)&serveraddr, sizeof(serveraddr));

    // Step 4: Get input from the user
    printf("\nEnter string: ");
    scanf("%s", buffer);

    // Step 5: Send the user input to the server
    send(clisocket, buffer, sizeof(buffer), 0);

    // Step 6: Close the socket connection
    close(clisocket);
}

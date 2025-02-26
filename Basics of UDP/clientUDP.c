#include <stdio.h>      // Standard I/O functions
#include <arpa/inet.h>  // Networking functions (socket, sendto, etc.)

#define PORT 4000  // Define the port number

void main() {
    struct sockaddr_in serveraddr;  // Structure to store server details
    int clisocket;                  // Socket descriptor
    char buffer[100];                // Buffer to store user input

    // Step 1: Create a UDP socket
    clisocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (clisocket > 0)
        printf("\nClient socket created");

    // Step 2: Define server address properties
    serveraddr.sin_family = AF_INET;              // Use IPv4
    serveraddr.sin_port = htons(PORT);            // Convert port to network byte order
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");  // Set server IP address (localhost)

    // Step 3: Get user input
    printf("\nEnter string: ");
    scanf("%s", buffer);

    // Step 4: Send data to the server
    sendto(clisocket, buffer, sizeof(buffer), 0, (struct sockaddr *)&serveraddr, sizeof(serveraddr));

    // Step 5: Close the socket
    close(clisocket);
}

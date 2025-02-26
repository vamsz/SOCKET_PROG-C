#include <stdio.h>      // Standard I/O functions
#include <arpa/inet.h>  // Networking functions (socket, bind, recvfrom, etc.)

#define PORT 4000  // Define the port number

void main() {
    struct sockaddr_in serveraddr, newaddr;  // Structures for server and client address
    int sersocket, s, size;
    char buffer[100];  // Buffer to store received data

    // Step 1: Create a UDP socket
    sersocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (sersocket > 0)
        printf("\nServer socket created");

    // Step 2: Define server address properties
    serveraddr.sin_family = AF_INET;          // Use IPv4
    serveraddr.sin_port = htons(PORT);        // Convert port to network byte order
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);  // Allow any incoming address

    // Step 3: Bind the socket to the port
    s = bind(sersocket, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    if (s == 0)
        printf("\nBind success");

    size = sizeof(newaddr);

    // Step 4: Receive data from client
    recvfrom(sersocket, buffer, 1024, 0, (struct sockaddr*)&newaddr, &size);
    printf("\nString received: %s\n", buffer);

    // Step 5: Close the socket
    close(sersocket);
}

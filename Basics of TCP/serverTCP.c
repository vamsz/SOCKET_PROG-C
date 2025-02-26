#include <stdio.h>      // Standard I/O functions
#include <arpa/inet.h>  // Networking functions (socket, bind, listen, accept)

#define PORT 5000  // Define the port number

void main() {
    struct sockaddr_in serveraddr, newaddr;  // Structures to store server & client details
    int sersocket, newsocket, s, size;       // Socket descriptors and size variables
    char buffer[100];                        // Buffer to store received data

    // Step 1: Create a TCP socket
    sersocket = socket(PF_INET, SOCK_STREAM, 0);
    if (sersocket > 0)
        printf("\nServer socket is created");

    // Step 2: Define server address properties
    serveraddr.sin_family = PF_INET;            // Use IPv4
    serveraddr.sin_port = htons(PORT);          // Convert port to network byte order
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);  // Accept connections on any IP

    // Step 3: Bind the socket to the server address
    s = bind(sersocket, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    if (s == 0)
        printf("\nBind success");

    // Step 4: Listen for incoming connections (1 client at a time)
    listen(sersocket, 1);

    // Step 5: Accept a client connection
    size = sizeof(newaddr);
    printf("\nServer ready");
    newsocket = accept(sersocket, (struct sockaddr *)&newaddr, &size);
    if (newsocket > 0)
        printf("\nAccepted");

    // Step 6: Receive data from the client
    recv(newsocket, buffer, 1024, 0);
    printf("\nData received is: %s\n", buffer);

    // Step 7: Close the server socket
    close(sersocket);
}

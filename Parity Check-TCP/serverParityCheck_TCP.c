#include <stdio.h>      // Standard I/O functions
#include <string.h>     // String manipulation functions
#include <arpa/inet.h>  // Networking functions (socket, bind, listen, accept)

#define PORT 5000  // Define the port number

// Function to check parity of the received binary data
int parityCheck(char buffer[]) {
    int i, count = 0;

    // Count the number of '1's in the received data
    for (i = 0; i < strlen(buffer); i++)
        if (buffer[i] == '1')
            count++;

    // If the count of '1's is even, return '0' (No error)
    // If the count is odd, return '1' (Error detected)
    return (count % 2 == 0) ? '0' : '1';
}

void main() {
    struct sockaddr_in serveraddr, newaddr;  // Structures to store server and client details
    int sersocket, newsocket, s, size;      // Socket variables
    char buffer[100];                        // Buffer for data transfer

    // Step 1: Create a TCP socket
    // AF_INET -> IPv4
    // SOCK_STREAM -> TCP (connection-oriented)
    // 0 -> Default protocol (TCP)
    sersocket = socket(PF_INET, SOCK_STREAM, 0);
    if (sersocket > 0)
        printf("\nServer socket is created");

    // Step 2: Define server address properties
    serveraddr.sin_family = PF_INET;            // Use IPv4
    serveraddr.sin_port = htons(PORT);          // Convert port to network byte order
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY); // Accept connections from any IP

    // Step 3: Bind the socket to the specified port
    s = bind(sersocket, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    if (s == 0)
        printf("\nBind success");

    // Step 4: Listen for incoming client connections (max 1 client)
    listen(sersocket, 1);

    size = sizeof(newaddr);
    printf("\nServer ready");

    // Step 5: Accept connection from client
    newsocket = accept(sersocket, (struct sockaddr*)&newaddr, &size);
    if (newsocket > 0)
        printf("\nAccepted connection from client");

    // Step 6: Receive binary data from the client
    recv(newsocket, buffer, 1024, 0);

    // Step 7: Perform parity check on received data
    int parity = parityCheck(buffer);

    // Step 8: Send response to the client based on parity check result
    if (parity == '0')
        strcpy(buffer, "\nNo error in data\n"); // Even parity, no error
    else
        strcpy(buffer, "\nError in data\n");    // Odd parity, error detected

    send(newsocket, buffer, sizeof(buffer), 0);

    // Step 9: Close the server socket
    close(sersocket);
}

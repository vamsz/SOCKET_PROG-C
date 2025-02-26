#include <stdio.h>      // Standard I/O functions
#include <arpa/inet.h>  // Networking functions (socket, connect, send, recv)

#define PORT 5000  // Define the port number

void main() {
    struct sockaddr_in serveraddr;  // Structure to store server details
    int clisocket;                  // Variable to store client socket
    char buffer[100];                // Buffer for sending and receiving data

    // Step 1: Create a TCP socket
    // AF_INET -> IPv4
    // SOCK_STREAM -> TCP (connection-oriented)
    // 0 -> Default protocol (TCP)
    clisocket = socket(PF_INET, SOCK_STREAM, 0);
    if (clisocket > 0)
        printf("Client socket created");

    // Step 2: Define server address properties
    serveraddr.sin_family = PF_INET;            // Use IPv4
    serveraddr.sin_port = htons(PORT);          // Convert port to network byte order
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Server IP address (localhost)

    // Step 3: Connect to the server
    connect(clisocket, (struct sockaddr*)&serveraddr, sizeof(serveraddr));

    // Step 4: Take user input
    printf("\nDATA: ");
    scanf("%s", buffer);  // Read input from the user

    // Step 5: Send data to the server
    send(clisocket, buffer, sizeof(buffer), 0);

    // Step 6: Receive response from the server
    recv(clisocket, buffer, sizeof(buffer), 0);

    // Step 7: Print the received response
    printf("%s\n", buffer);

    // Step 8: Close the socket
    close(clisocket);
}

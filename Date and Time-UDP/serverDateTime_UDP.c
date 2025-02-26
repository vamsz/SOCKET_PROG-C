#include <stdio.h>       // Standard I/O functions
#include <string.h>      // String functions (strcpy, snprintf)
#include <time.h>        // Time functions (time, ctime)
#include <arpa/inet.h>   // Networking functions (socket, bind, sendto, recvfrom)

#define PORT 4000  // Define the port number

void main() {
    time_t ticks;  // Variable to store current time
    struct sockaddr_in serveraddr, newaddr;  // Structures to store server and client details
    int sersocket, s, size;
    char buffer[100], str[100];  // Buffers for storing messages

    // Step 1: Create a UDP socket
    // AF_INET -> IPv4
    // SOCK_DGRAM -> UDP (connectionless protocol)
    // 0 -> Default protocol (UDP)
    sersocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (sersocket > 0)
        printf("\nServer socket created");

    // Step 2: Define server address properties
    serveraddr.sin_family = AF_INET;          // Use IPv4
    serveraddr.sin_port = htons(PORT);        // Convert port to network byte order
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY); // Allow connection from any IP

    // Step 3: Bind the socket to the specified port and IP
    s = bind(sersocket, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    if (s == 0)
        printf("\nBind success");

    // Step 4: Receive data from the client
    size = sizeof(newaddr);
    recvfrom(sersocket, buffer, sizeof(buffer), 0, (struct sockaddr *)&newaddr, &size);
    printf("\nMessage received: %s", buffer); // Print received message

    // Step 5: Get the current system time
    ticks = time(NULL);
    strcpy(str, ctime(&ticks)); // Convert time to string format

    // Step 6: Send the current time as a response to the client
    snprintf(buffer, sizeof(buffer), "%s", str);
    sendto(sersocket, buffer, sizeof(buffer), 0, (struct sockaddr *)&newaddr, sizeof(newaddr));

    printf("\n"); // New line for better formatting

    // Step 7: Close the socket
    close(sersocket);
}

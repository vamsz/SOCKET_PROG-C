#include <stdio.h>       // Standard I/O functions
#include <arpa/inet.h>   // Networking functions (inet_addr, socket, etc.)

#define PORT 4000  // Define the port number

void main()
{
    struct sockaddr_in serveraddr, newaddr;  // Structures to store server details
    int clisocket, size;
    char buffer[100];  // Buffer to store sent/received data

    // Step 1: Create a UDP socket
    // AF_INET -> IPv4
    // SOCK_DGRAM -> UDP (connectionless protocol)
    // 0 -> Default protocol (UDP)
    clisocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (clisocket > 0)
        printf("\nClient socket created");

    // Step 2: Define server address properties
    serveraddr.sin_family = AF_INET;          // Use IPv4
    serveraddr.sin_port = htons(PORT);        // Convert port to network byte order
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Set server IP to localhost

    // Step 3: Get user input (word/message)
    printf("\nEnter message: ");
    scanf("%s", buffer); // Read input string from user

    // Step 4: Send data to the server
    // sendto() is used for UDP communication since there's no connection establishment
    size = sizeof(newaddr);
    sendto(clisocket, buffer, sizeof(buffer), 0, (struct sockaddr*)&serveraddr, sizeof(serveraddr));

    // Step 5: Receive response from the server
    // recvfrom() waits for data from the server and stores it in buffer
    recvfrom(clisocket, buffer, sizeof(buffer), 0, (struct sockaddr*)&newaddr, &size);
    printf("\nMessage from server: %s\n", buffer); // Print the received response

    // Step 6: Close the socket
    // Closes the UDP socket after communication is done
    close(clisocket);
}


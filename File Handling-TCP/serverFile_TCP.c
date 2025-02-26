#include <stdio.h>       // Standard I/O functions
#include <string.h>      // String manipulation functions
#include <stdlib.h>      // Exit function
#include <arpa/inet.h>   // Networking functions (inet_addr, socket, etc.)

#define PORT 5000  // Define the port number

void main()
{
    struct sockaddr_in serveraddr, newaddr; // Structures to store server & client details
    int sersocket, newsocket, s, size;
    char buffer[100];  // Buffer to store received data

    // Step 1: Create a TCP socket
    sersocket = socket(PF_INET, SOCK_STREAM, 0);
    if (sersocket > 0)
        printf("Server socket is created");

    // Step 2: Define server address properties
    serveraddr.sin_family = PF_INET;          // Address family (IPv4)
    serveraddr.sin_port = htons(PORT);        // Convert port to network byte order
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY); // Accept connections from any IP

    // Step 3: Bind the socket to the server address
    s = bind(sersocket, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    if (s == 0)
        printf("\nBind success");

    // Step 4: Start listening for client connections
    listen(sersocket, 1);
    printf("\nServer ready");

    // Step 5: Accept a client connection
    size = sizeof(newaddr);
    newsocket = accept(sersocket, (struct sockaddr *)&newaddr, &size);
    if (newsocket > 0)
        printf("\nAccepted connection");

    // Step 6: Open a file to store received data
    FILE *fp;
    fp = fopen("p.txt", "w");
    if (fp == NULL)
    {
        printf("\nFile cannot be opened");
        exit(0);
    }
    else
    {
        printf("\nFile opened successfully");

        // Step 7: Read data from client
        read(newsocket, buffer, 100);
        printf("\nData to be written on file: %s\n", buffer);

        // Step 8: Write received data to the file
        fprintf(fp, "%s\n", buffer);

        // Step 9: Send acknowledgment back to the client
        write(newsocket, buffer, strlen(buffer) + 1);

        // Step 10: Close the file
        fclose(fp);
    }

    // Step 11: Close the server socket
    close(sersocket);
}

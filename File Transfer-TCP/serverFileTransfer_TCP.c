#include <stdio.h>      // Standard I/O functions
#include <stdlib.h>     // For exit() function
#include <string.h>     // String manipulation functions
#include <arpa/inet.h>  // Networking functions (socket, bind, accept, etc.)

#define PORT 5000  // Define the port number

void main() {
    struct sockaddr_in serveraddr, newaddr;  // Structures for server and client addresses
    int sersocket, newsocket, s, size;
    char buffer[100];  // Buffer to store received data

    // Step 1: Create a TCP socket
    sersocket = socket(PF_INET, SOCK_STREAM, 0);
    if (sersocket > 0)
        printf("Server socket is created");

    // Step 2: Define server address properties
    serveraddr.sin_family = PF_INET;          // Use IPv4
    serveraddr.sin_port = htons(PORT);        // Convert port to network byte order
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);  // Accept connections from any IP

    // Step 3: Bind the socket to the defined address and port
    s = bind(sersocket, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    if (s == 0)
        printf("\nBind success");

    // Step 4: Listen for incoming connections
    listen(sersocket, 1);
    size = sizeof(newaddr);
    printf("\nServer ready");

    // Step 5: Accept a client connection
    newsocket = accept(sersocket, (struct sockaddr*)&newaddr, &size);
    if (newsocket > 0)
        printf("\nAccepted");

    // Step 6: Open file for writing
    FILE *fp;
    int ch = 0;
    int words;

    fp = fopen("write.txt", "w");  // Create a new file
    if (fp == NULL) {
        printf("\nFile cannot be opened");
        exit(0);
    } else {
        printf("\nFile opened successfully\n");

        // Step 7: Read the number of words from the client
        read(newsocket, &words, sizeof(int));

        // Step 8: Read the words from the client and write them to the file
        while (ch != words) {
            read(newsocket, buffer, 100);  // Receive a word
            fprintf(fp, "%s ", buffer);    // Write to file
            ch++;
        }

        printf("The new file created is write.txt\n");

        // Step 9: Close the file
        fclose(fp);
    }

    // Step 10: Close the server socket
    close(sersocket);
}

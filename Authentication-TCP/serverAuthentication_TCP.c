#include<stdio.h>       // Standard input-output functions
#include<arpa/inet.h>   // Contains socket-related structures and functions
#include<string.h>      // For string operations like strcmp and strcpy
#define port 5000       // Defining the port number for communication

int main()
{
    struct sockaddr_in serveraddr, newaddr;  // Structures to store server and client address details
    int sersocket, newsocket, s, size;      // Socket descriptors and variables
    char buffer1[100], buffer2[100], buffer[100];  // Buffers to store username, password, and response messages

    // Creating a TCP socket (SOCK_STREAM indicates TCP)
    sersocket = socket(PF_INET, SOCK_STREAM, 0);
    if (sersocket > 0)  // Checking if the socket was successfully created
        printf("\nServer socket is created");

    // Defining server details
    serveraddr.sin_family = PF_INET;            // Address family: Internet Protocol (IPv4)
    serveraddr.sin_port = htons(port);          // Setting port number, converting to network byte order
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);  // Accept connections from any available network interface

    // Binding the socket to the defined port and IP address
    s = bind(sersocket, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    if (s == 0)  // Checking if the bind was successful
        printf("\nBind success");

    // Listening for incoming connection requests (max 1 queued connection)
    listen(sersocket, 1);
    printf("\nServer ready");

    // Accepting an incoming connection request from a client
    size = sizeof(newaddr);
    newsocket = accept(sersocket, (struct sockaddr*)&newaddr, &size);
    if (newsocket > 0)
        printf("\nAccepted connection from client");

    // Receiving the username from the client
    recv(newsocket, buffer1, sizeof(buffer1), 0);
    printf("\nData received (username): %s\n", buffer1);

    // Checking if the username is "admin"
    if (strcmp(buffer1, "admin") == 0)
    {
        // Receiving the password from the client
        recv(newsocket, buffer2, sizeof(buffer2), 0);
        printf("Data received (password): %s\n", buffer2);

        // Checking if the password is "admin"
        if (strcmp(buffer2, "admin") == 0)
            strcpy(buffer, "\nCONFIRMED\n");  // Authentication successful
        else
            strcpy(buffer, "\nEnter valid password\n");  // Invalid password
    }
    else
    {
        strcpy(buffer, "\nEnter valid username\n");  // Invalid username
    }

    // Sending authentication response back to the client
    send(newsocket, buffer, sizeof(buffer), 0);

    // Closing the server socket
    close(sersocket);

    return 0;
}

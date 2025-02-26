#include <stdio.h>      // Standard I/O functions
#include <string.h>     // String manipulation functions
#include <stdlib.h>     // Memory allocation functions
#include <arpa/inet.h>  // Networking functions (socket, bind, listen, accept)

#define PORT 5000  // Define the port number

// Function to compute CRC (Cyclic Redundancy Check)
int* getCRC(char dividend[], char divisor[], int dataSize, int divisorSize) {
    int n1 = dataSize, n2 = divisorSize;
    int i, j, n[50], div[50], temp, q[20]; 
    int *f = (int*)malloc(sizeof(int) * 20);  // Allocate memory for remainder

    // Convert dividend (input data) from string to integer array (binary form)
    for (i = 0; i < n1 + n2 - 1; i++) {
        if (dividend[i] == '1')
            n[i] = 1;
        else
            n[i] = 0;
    }

    // Convert divisor (CRC polynomial) from string to integer array
    for (i = 0; i < n2; i++) {
        if (divisor[i] == '1')
            div[i] = 1;
        else
            div[i] = 0;
    }

    // Perform binary division using XOR (CRC algorithm)
    for (i = 0; i < n1; i++) {
        temp = i;
        if (n[i] == 1) {  // If leading bit is 1, perform XOR
            for (j = 0; j < n2; j++) {
                if (n[temp] == div[j]) {
                    n[temp] = 0;
                    f[j] = 0;
                } else {
                    n[temp] = 1;
                    f[j] = 1;
                }
                temp++;
            }
            q[i] = 1;  // Quotient bit
        } else {
            q[i] = 0;
        }
    }
    return f;  // Return remainder (CRC code)
}

void main() {
    int sersocket, s;
    struct sockaddr_in serveraddr;  // Structure to store server details
    struct sockaddr_in newaddr;     // Structure for incoming client connection
    int newsocket;
    int size;
    char buffer[100], msg[100];

    // Step 1: Create a TCP socket
    sersocket = socket(PF_INET, SOCK_STREAM, 0);
    if (sersocket > 0)
        printf("\nServer socket is created");

    // Step 2: Define server address properties
    serveraddr.sin_family = PF_INET;             // Use IPv4
    serveraddr.sin_port = htons(PORT);           // Convert port to network byte order
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY); // Accept connections from any IP

    // Step 3: Bind the socket to the specified IP and port
    s = bind(sersocket, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    if (s == 0)
        printf("\nBind success");

    // Step 4: Listen for incoming connections (queue size = 1)
    listen(sersocket, 1);
    size = sizeof(newaddr);
    printf("\nServer ready");

    // Step 5: Accept an incoming client connection
    newsocket = accept(sersocket, (struct sockaddr *)&newaddr, &size);
    if (newsocket > 0)
        printf("\nAccepted");

    // Step 6: Define the CRC divisor
    char divisor[4] = "1101";

    // Step 7: Receive the message (data with CRC check bits) from the client
    recv(newsocket, buffer, 1024, 0);

    // Step 8: Compute the CRC remainder
    int *remainder;
    int dataSize = strlen(buffer) - strlen(divisor) + 1, divisorSize = strlen(divisor);
    remainder = getCRC(buffer, divisor, dataSize, divisorSize);

    // Step 9: Check if any remainder bits are non-zero (indicating an error)
    int i;
    for (i = 1; i < divisorSize; i++) {
        if (remainder[i] != 0) {  // If any remainder bit is non-zero, error detected
            strcpy(msg, "Error\n");
            break;
        }
    }
    if (i == divisorSize)  // If all remainder bits are zero, data is correct
        strcpy(msg, "No error\n");

    // Step 10: Send the result (error or no error) back to the client
    send(newsocket, msg, sizeof(msg), 0);

    // Step 11: Close the server socket
    close(sersocket);
}

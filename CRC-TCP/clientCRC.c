#include <stdio.h>      // Standard I/O functions
#include <string.h>     // String manipulation functions
#include <stdlib.h>     // Memory allocation functions
#include <arpa/inet.h>  // Networking functions (socket, connect)

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
    struct sockaddr_in serveraddr;  // Structure to store server details
    int clisocket;                  // Socket variable
    char buffer[100], msg[100], divisor[4] = "1101"; // Buffer for data, CRC divisor
    int n = strlen(divisor);         // Length of divisor

    // Step 1: Create a TCP socket
    clisocket = socket(PF_INET, SOCK_STREAM, 0);
    if (clisocket > 0)
        printf("\nClient socket created");

    // Step 2: Define server address properties
    serveraddr.sin_family = PF_INET;             // Use IPv4
    serveraddr.sin_port = htons(PORT);           // Convert port to network byte order
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Connect to localhost

    // Step 3: Connect to the server
    connect(clisocket, (struct sockaddr*)&serveraddr, sizeof(serveraddr));

    // Step 4: Get user input (binary data)
    printf("\nData: ");
    scanf("%s", buffer);

    int dataSize = strlen(buffer); // Get length of input data
    int i;

    // Step 5: Append (n-1) zeros for CRC computation
    for (i = dataSize; i < dataSize + n - 2; i++)
        buffer[i] = '0';

    buffer[i] = '\0'; // Null-terminate the string

    // Step 6: Send the data with appended zeros to the server
    send(clisocket, buffer, sizeof(buffer), 0);

    // Step 7: Receive processed data (CRC check result) from the server
    recv(clisocket, msg, sizeof(msg), 0);
    printf("%s", msg);

    // Step 8: Close the socket connection
    close(clisocket);
}

#include <stdio.h>      // Standard I/O functions
#include <string.h>     // String manipulation functions
#include <arpa/inet.h>  // Networking functions (socket, connect, etc.)
#include <ctype.h>      // For isspace() function

#define PORT 5000  // Define the port number

void main() {
    struct sockaddr_in serveraddr;  // Structure for server address
    int clisocket;  // Client socket descriptor
    char buffer[100];  // Buffer to store file data

    // Step 1: Create a TCP socket
    clisocket = socket(PF_INET, SOCK_STREAM, 0);
    if (clisocket > 0)
        printf("Client socket created");

    // Step 2: Define server address properties
    serveraddr.sin_family = PF_INET;         // Use IPv4
    serveraddr.sin_port = htons(PORT);       // Convert port to network byte order
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");  // Connect to localhost

    // Step 3: Connect to the server
    connect(clisocket, (struct sockaddr*)&serveraddr, sizeof(serveraddr));

    // Step 4: Open the file for reading
    FILE *f;
    int words = 0;
    char c;
    f = fopen("read.txt", "r");  // Open file in read mode

    // Step 5: Count the number of words in the file
    while ((c = getc(f)) != EOF) {  // Read each character
        fscanf(f, "%s", buffer);    // Read word from file
        if (isspace(c) || c == '\t' || c == '.')  // Count spaces, tabs, and periods as word separators
            words++;
    }
    printf("\nWords = %d \n", words);

    // Step 6: Send word count to the server
    write(clisocket, &words, sizeof(int));

    // Step 7: Reset file pointer to beginning
    rewind(f);

    // Step 8: Read and send the file content word by word
    char ch;
    while ((ch = fgetc(f)) != EOF) {  // Read character by character
        fscanf(f, "%s", buffer);      // Read word
        write(clisocket, buffer, 100);  // Send word to server
    }

    printf("\nThe file was sent successfully\n");

    // Step 9: Close the socket
    close(clisocket);
}

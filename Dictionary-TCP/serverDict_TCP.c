#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>   // For close() function

#define PORT 5000  // Define the port number

int main()
{
    struct sockaddr_in serveraddr, newaddr;
    int sersocket, newsocket, s, size;
    int i, found = 0;
    char buffer[100], word[100], antonym[100];

    // Dictionary database (word, meaning, antonym)
    char dictionary[7][3][100] = {
        {"consider", "deem to be", "disregard"},
        {"minute", "infinitely or immeasurably small", "significant"},
        {"accord", "concurrence of opinion", "withhold"},
        {"commit", "perform an act, usually with a negative connotation", "abstain"},
        {"utter", "without qualification", "partial"},
        {"zealot", "a fervent and even militant proponent of something", "moderate"},
        {"wanton", "a lewd or lascivious person", "justifiable"}
    };

    // Create a TCP socket
    sersocket = socket(PF_INET, SOCK_STREAM, 0);
    if (sersocket < 0) {
        perror("Socket creation failed");
        exit(1);
    }
    printf("\nServer socket created");

    // Define server details
    serveraddr.sin_family = PF_INET;
    serveraddr.sin_port = htons(PORT);
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

    // Bind the socket to the port
    s = bind(sersocket, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    if (s < 0) {
        perror("Bind failed");
        close(sersocket);
        exit(1);
    }
    printf("\nBind success");

    // Listen for connections
    listen(sersocket, 1);
    printf("\nServer ready, waiting for connections...");

    // Accept incoming connection
    size = sizeof(newaddr);
    newsocket = accept(sersocket, (struct sockaddr *)&newaddr, (socklen_t*)&size);
    if (newsocket < 0) {
        perror("Accept failed");
        close(sersocket);
        exit(1);
    }
    printf("\nClient connected");

    // Receive word from client
    recv(newsocket, buffer, sizeof(buffer), 0);
    printf("\nWord to be searched: %s\n", buffer);

    // Search for the word in the dictionary
    for (i = 0; i < 7; i++) {
        if (strcmp(buffer, dictionary[i][0]) == 0) {
            strcpy(word, dictionary[i][1]);
            send(newsocket, word, sizeof(word), 0);

            strcpy(antonym, dictionary[i][2]);
            send(newsocket, antonym, sizeof(antonym), 0);

            found = 1;
            break;
        }
    }

    // If word not found
    if (!found) {
        strcpy(word, "Word not found in dictionary");
        send(newsocket, word, sizeof(word), 0);
    }

    // Close sockets
    close(newsocket);
    close(sersocket);

    return 0;
}

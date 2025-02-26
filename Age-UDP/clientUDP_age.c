#include<stdio.h>      // Standard input-output library for printf, scanf, etc.
#include<arpa/inet.h>  // Contains functions and structures for internet operations (like sockaddr_in, inet_addr, etc.)

#define port 4000      // Defining the port number for communication

int main() {
    int dd, mm, yy;  // Variables to store the day, month, and year
    struct sockaddr_in serveraddr;  // Structure to hold server address information
    int clisocket;  // Client socket descriptor

    // Creating a UDP socket (SOCK_DGRAM for UDP communication)
    clisocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (clisocket > 0)  // If socket creation is successful
        printf("\nClient socket created");

    // Defining server details
    serveraddr.sin_family = AF_INET;  // Setting the address family to IPv4
    serveraddr.sin_port = htons(port);  // Setting the port number, converting it to network byte order
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");  // Setting the IP address of the server (localhost)

    // Prompting the user to enter a date
    printf("\nEnter date (dd/mm/yyyy) format: ");
    scanf("%d/%d/%d", &dd, &mm, &yy);  // Taking input from the user

    // Sending the day (dd) to the server using sendto()
    sendto(clisocket, &dd, sizeof(dd), 0, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    // Sending the month (mm) to the server using sendto()
    sendto(clisocket, &mm, sizeof(mm), 0, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    // Sending the year (yy) to the server using sendto()
    sendto(clisocket, &yy, sizeof(yy), 0, (struct sockaddr*)&serveraddr, sizeof(serveraddr));

    // Closing the client socket after sending the data
    close(clisocket);

    return 0;  // Indicating successful execution
}

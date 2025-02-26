#include<stdio.h>       // Standard I/O functions
#include<string.h>      // String manipulation functions
#include<stdlib.h>      // Standard library functions
#include<sys/socket.h>  // Socket programming functions
#include<sys/types.h>   // Data types for sockets
#include<netinet/in.h>  // Structures for internet operations
#include<arpa/inet.h>   // Functions for IP address operations
#include<sys/ioctl.h>   // Input-output control for device-specific operations
#include<net/if.h>      // Interface structure for network device info
#include<unistd.h>      // Close function for sockets

#define PORT 5000  // Defining the port number for communication

int main()
{
    struct sockaddr_in serveraddr;  // Server address structure
    struct ifreq ifr;               // Interface request structure for MAC address
    char *iface = "eth0";           // Network interface to fetch the MAC address
    int clisocket;
    char IPaddr[100], mac_addr[32] = {0};
    
    // Create a TCP socket
    clisocket = socket(PF_INET, SOCK_STREAM, 0);
    if (clisocket < 0) {
        perror("Socket creation failed");
        exit(1);
    }
    printf("\nClient socket created");

    // Define server details
    serveraddr.sin_family = PF_INET;
    serveraddr.sin_port = htons(PORT);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to the server
    if (connect(clisocket, (struct sockaddr*)&serveraddr, sizeof(serveraddr)) < 0) {
        perror("Connection failed");
        close(clisocket);
        exit(1);
    }

    // Get the client's IP address (localhost in this case)
    strcpy(IPaddr, inet_ntoa(serveraddr.sin_addr));

    // Send IP address to the server
    send(clisocket, IPaddr, sizeof(IPaddr), 0);
    printf("\nIP address of client sent to server");

    // Get the MAC address of the client
    ifr.ifr_addr.sa_family = PF_INET;  // Set the address family to IPv4
    strncpy(ifr.ifr_name, iface, IFNAMSIZ - 1);  // Set the network interface name

    // Retrieve the MAC address using ioctl
    if (ioctl(clisocket, SIOCGIFHWADDR, &ifr) < 0) {
        perror("Failed to get MAC address");
        close(clisocket);
        exit(1);
    }

    // Format the MAC address
    sprintf(mac_addr, "%.2hhx:%.2hhx:%.2hhx:%.2hhx:%.2hhx:%.2hhx",
            (unsigned char)ifr.ifr_hwaddr.sa_data[0],
            (unsigned char)ifr.ifr_hwaddr.sa_data[1],
            (unsigned char)ifr.ifr_hwaddr.sa_data[2],
            (unsigned char)ifr.ifr_hwaddr.sa_data[3],
            (unsigned char)ifr.ifr_hwaddr.sa_data[4],
            (unsigned char)ifr.ifr_hwaddr.sa_data[5]);

    // Send MAC address to the server
    send(clisocket, mac_addr, sizeof(mac_addr), 0);
    printf("\nMAC address of client sent to server: %s\n", mac_addr);

    // Close the client socket
    close(clisocket);

    return 0;
}

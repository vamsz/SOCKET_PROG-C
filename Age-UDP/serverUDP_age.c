#include<stdio.h>      // Standard input-output library for printf, scanf, etc.
#include<arpa/inet.h>  // Contains functions and structures for internet operations (like sockaddr_in, inet_addr, etc.)
#include<time.h>       // Used for getting the current date and time
#include<stdlib.h>     // Used for converting strings to integers (atoi)

#define port 4000      // Defining the port number for communication

// Function to calculate the age based on the birth date and current date
void findAge(int current_date, int current_month, int current_year, 
             int birth_date, int birth_month, int birth_year) 
{
    // Array storing the number of days in each month
    int month[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    // Adjusting day and month if birth_date is greater than the current_date
    if (birth_date > current_date) {
        current_date = current_date + month[birth_month - 1]; // Borrow days from previous month
        current_month = current_month - 1;
    }
    
    // Adjusting year and month if birth_month is greater than the current_month
    if (birth_month > current_month) {
        current_year = current_year - 1; // Borrow a year
        current_month = current_month + 12;
    }

    // Calculating the age
    int calculated_date = current_date - birth_date;
    int calculated_month = current_month - birth_month;
    int calculated_year = current_year - birth_year;

    // Printing the calculated age
    printf("Present Age\nYears: %d  Months: %d  Days: %d\n", calculated_year, calculated_month, calculated_date);
}

int main()
{
    time_t timer;       // Variable to store time in seconds
    struct tm* tm_info; // Structure to hold time details
    int days, months, years; // Variables to store current date
    char day[3], month[3], year[5]; // Strings to store date parts temporarily
    int dd, mm, yy;  // Variables to store the received birth date

    // Getting the current time
    time(&timer);
    tm_info = localtime(&timer);

    // Extracting day, month, and year from current time
    strftime(day, 3, "%d", tm_info);   // Storing the day as a string
    strftime(month, 3, "%m", tm_info); // Storing the month as a string
    strftime(year, 5, "%Y", tm_info);  // Storing the year as a string

    // Converting the string values to integers
    days = atoi(day);
    months = atoi(month);
    years = atoi(year);

    // Printing the current date in MM/DD/YYYY format
    printf("%d/%d/%d\n", months, days, years);

    struct sockaddr_in serveraddr, newaddr; // Structures to hold server and client address information
    int sersocket, s, size; // Server socket descriptor and other variables

    // Creating a UDP socket (SOCK_DGRAM for UDP communication)
    sersocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (sersocket > 0)  // If socket creation is successful
        printf("\nServer socket created");

    // Defining server details
    serveraddr.sin_family = AF_INET;  // Setting the address family to IPv4
    serveraddr.sin_port = htons(port);  // Setting the port number, converting it to network byte order
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);  // Accept connections from any IP address

    // Binding the socket to the specified IP address and port
    s = bind(sersocket, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    if (s == 0)  // If binding is successful
        printf("\nBind success");

    size = sizeof(newaddr);  // Storing the size of client address structure

    // Receiving birth date details from client
    recvfrom(sersocket, &dd, sizeof(dd), 0, (struct sockaddr*)&newaddr, &size);
    recvfrom(sersocket, &mm, sizeof(mm), 0, (struct sockaddr*)&newaddr, &size);
    recvfrom(sersocket, &yy, sizeof(yy), 0, (struct sockaddr*)&newaddr, &size);

    // Printing the received birth date
    printf("\nString received: %d/%d/%d\n", dd, mm, yy);

    // Calculating and printing the age
    findAge(days, months, years, dd, mm, yy);

    // Closing the server socket
    close(sersocket);

    return 0;  // Indicating successful execution
}

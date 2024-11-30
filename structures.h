#ifndef PROJECTC_STRUCTURES_H
#define PROJECTC_STRUCTURES_H

struct vehicle {

    char plate[10];
    int year;
    char model[20];
    char fuelType[10];
    double consumption;
    int seats;
    double dailyPrice;
    int vehicelCounter;

    struct vehicle *next;

};

struct reservation {

    int reservationID;
    int clientID;
    int nrOfDays;
    double totalPrice;
    long long int date;
    long long int returnDate;
    char plate[10];

    struct reservation *next;

};

struct client {

    int clientID;
    char name[20];
    char surname[20];
    char passport[20];
    char state[20];
    int phoneNr;
    int clientCounter;

    struct client *next;
};

#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structures.h"
#include "global.h"


#ifndef CARRENTALSYSTEM_SULJON_H
#define CARRENTALSYSTEM_SULJON_H

void dsiplayAllVehicels(struct vehicle *headV) {

    if (headV == NULL) {
        printf("No vehicels are listed!\n");
        printf("\n");
    }

    while (headV != NULL) {
        printf("Plate : %s\nYear : %d\nModel : %s\nFuel Type : %s\nConsumption : %.1lf l/km \nSeats : %d\nDaily Price : %.3lf\nRented : %d times\n",
               headV->plate, headV->year, headV->model, headV->fuelType, headV->consumption, headV->seats,
               headV->dailyPrice, headV->vehicelCounter);
        headV = headV->next;
        printf("\n");
    }

}

void displayAllReservations(struct reservation *headR) {
    if (headR == NULL) {
        printf("No reservations!\n\n");
    } else {
        while (headR != NULL) {
            time_t seconds = (time_t) headR->date;
            struct tm *dateInfo = localtime(&seconds);
            char date[50];
            strftime(date, sizeof(date), "%d-%m-%Y %H:%M:%S", dateInfo);

            time_t returnSec = (time_t) headR->returnDate;
            struct tm *returnDateInfo = localtime(&returnSec);
            char returnDate[50];
            strftime(returnDate, sizeof(returnDate), "%d-%m-%Y %H:%M:%S", returnDateInfo);

            printf("Reservation ID: %d\nClient ID: %d\nVehicle Plate: %s\nDate: %s\nReturn Date: %s\nTotal Price: %.3lf\n\n",
                   headR->reservationID, headR->clientID, headR->plate, date, returnDate, headR->totalPrice);

            headR = headR->next;
        }
    }
}



void modifyInformation(struct vehicle **headV) {
    struct vehicle *temp = *headV;
    printf("Enter the plate number of the vehicle you want to change the info: ");
    char plt[10];
    int found = 0;
    scanf("%s", plt);
    while (temp != NULL) {
        if (strcmp(temp->plate, plt) == 0) {
            int choice;
            printf("Enter the new data for the vehicle:\n");

            printf("Do you want to change the year of production(1-Yes | 2-No):");
            scanf("%d", &choice);
            if(choice == 1){
                printf("Year of the production : ");
                scanf("%d", &temp->year);
            }

            printf("Do you want to change the model(1-Yes | 2-No):");
            scanf("%d", &choice);
            if(choice==1){
                printf("Model : ");
                scanf("%s", temp->model);
            }

            printf("Do you want to change the fuel type(1-Yes | 2-No):");
            scanf("%d", &choice);
            if(choice == 1){
                printf("Fuel type : ");
                scanf("%s", temp->fuelType);
            }

            printf("Do you want to change the consumption(1-Yes | 2-No):");
            scanf("%d", &choice);
            if(choice == 1){
                printf("Consumption : ");
                scanf("%lf", &temp->consumption);
            }

            printf("Do you want to change the number of seats(1-Yes | 2-No):");
            scanf("%d", &choice);
            if(choice == 1){
                printf("Number of seats : ");
                scanf("%d", &temp->seats);
            }

            printf("Do you want to change the daily price(1-Yes | 2-No):");
            scanf("%d", &choice);
            if(choice == 1){
                printf("Daily Price : ");
                scanf("%lf", &temp->dailyPrice);
            }
            found = 1;
            break;
        }
        temp = temp->next;
    }
    if (found == 1) {
        printf("Information was modified successfully.\n");
    } else {
        printf("There is no vehicle registered with plate number:%s\n", plt);
    }
    printf("\n");
}



#endif //CARRENTALSYSTEM_SULJON_H

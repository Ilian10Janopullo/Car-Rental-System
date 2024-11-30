#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <string.h>
#include "structures.h"
#include "global.h"

#ifndef ARION_H_INCLUDED
#define ARION_H_INCLUDED

void cancelReservation(struct reservation **head) {
    struct reservation *current = NULL;
    struct reservation *previous = NULL;

    if (*head == NULL) {
        printf("There are no reservations\n");
        printf("\n");
        return;
    }

    int ID;
    int cnt = 0;
    printf("Enter the ID : ");

    while (cnt == 0) {

        scanf("%d", &ID);
        current = *head;

        while (1) {

            if (current->reservationID == ID) {
                (*head) = current->next;
                free(current);
                cnt++;
                break;
            } else {
                while ((current != NULL) && (current->reservationID != ID)) {

                    previous = current;
                    current = current->next;

                }

                if (current == NULL) {

                    printf("Invalid ID! Enter the correct ID : ");
                    break;
                } else if (current->reservationID == ID) {
                    previous->next = current->next;

                    free(current);
                    cnt++;
                    break;
                }

            }
        }
    }
    printf("\n");
    reservationCnt--;
}


void sort(struct vehicle *head) {

    if (head == NULL) {
        printf("No vehicles currently!\n");
        printf("\n");
        return;
    }

    int year, seats, vehicelCounter;
    double consumption, dailyPrice;
    char plate[10], model[20], fuelType[10];

    struct vehicle *current = NULL;
    current = head;

    struct vehicle *nextNode = current->next;

    while (current->next != NULL) {

        struct vehicle *nextNode = current->next;

        while (nextNode != NULL) {
            if (current->dailyPrice < nextNode->dailyPrice) {
                dailyPrice = current->dailyPrice;
                current->dailyPrice = nextNode->dailyPrice;
                nextNode->dailyPrice = dailyPrice;

                year = current->year;
                current->year = nextNode->year;
                nextNode->year = year;

                seats = current->seats;
                current->seats = nextNode->seats;
                nextNode->seats = seats;

                vehicelCounter = current->vehicelCounter;
                current->vehicelCounter = nextNode->vehicelCounter;
                nextNode->vehicelCounter = vehicelCounter;

                consumption = current->consumption;
                current->consumption = nextNode->consumption;
                nextNode->consumption = consumption;

                strcpy(plate, current->plate);
                strcpy(current->plate, nextNode->plate);
                strcpy(nextNode->plate, plate);

                strcpy(model, current->model);
                strcpy(current->model, nextNode->model);
                strcpy(nextNode->model, model);

                strcpy(fuelType, current->fuelType);
                strcpy(current->fuelType, nextNode->fuelType);
                strcpy(nextNode->fuelType, fuelType);
            }

            nextNode = nextNode->next;
        }
        current = current->next;
    }
    printf("\n");
    while (head != NULL) {
        printf("Plate number: %s\nYear: %d\nModel: %s\nFuel Type: %s\nCosumption: %.1lf\nSeats: %d\nDaily Price: %.3lf\nRented %d times\n",
               head->plate, head->year, head->model, head->fuelType, head->consumption, head->seats, head->dailyPrice,
               head->vehicelCounter);

        head = head->next;
        printf("\n");
    }
}


void searchVehicleByPlate(struct vehicle *head) {

    if (head == NULL) {
        printf("No vehicle found! \n");
        printf("\n");
        return;
    }

    int found = 0;
    printf("Enter the plate number you want to search for : ");
    char plateNumber[10];
    scanf("%s", plateNumber);

    while (head != NULL) {
        if (strcmp(head->plate, plateNumber) == 0) {
            printf("Information :\n");
            printf("Plate : %s\nYear : %d\nModel : %s\nFuel Type : %s\nCosumption : %.1lf\nSeats : %d\nDaily Price : %.3lf\nRented : %d times\n",
                   head->plate, head->year, head->model, head->fuelType, head->consumption, head->seats,
                   head->dailyPrice, head->vehicelCounter);
            printf("\n");

            found = 1;
            break;
        }

        head = head->next;
    }

    if (found == 0) {
        printf("There are no vehicles with this plate number! \n");
        printf("\n");
    }

}

void sortAndDisplay(struct vehicle *head) {
    if (head == NULL) {
        printf("No vehicles currently!\n");
        printf("\n");
        return;
    }

    int year, seats, vehicelCounter;
    double consumption, dailyPrice;
    char plate[10], model[20], fuelType[10];

    struct vehicle *current = NULL;
    current = head;


    while (current->next != NULL) {
        struct vehicle *nextNode = current->next;

        while (nextNode != NULL) {
            if (current->vehicelCounter < nextNode->vehicelCounter) {
                dailyPrice = current->dailyPrice;
                current->dailyPrice = nextNode->dailyPrice;
                nextNode->dailyPrice = dailyPrice;

                year = current->year;
                current->year = nextNode->year;
                nextNode->year = year;

                seats = current->seats;
                current->seats = nextNode->seats;
                nextNode->seats = seats;

                vehicelCounter = current->vehicelCounter;
                current->vehicelCounter = nextNode->vehicelCounter;
                nextNode->vehicelCounter = vehicelCounter;

                consumption = current->consumption;
                current->consumption = nextNode->consumption;
                nextNode->consumption = consumption;

                strcpy(plate, current->plate);
                strcpy(current->plate, nextNode->plate);
                strcpy(nextNode->plate, plate);

                strcpy(model, current->model);
                strcpy(current->model, nextNode->model);
                strcpy(nextNode->model, model);

                strcpy(fuelType, current->fuelType);
                strcpy(current->fuelType, nextNode->fuelType);
                strcpy(nextNode->fuelType, fuelType);
            }

            nextNode = nextNode->next;
        }

        current = current->next;
    }

    int cnt = 0;
    while (head != NULL) {
        printf("Plate number: %s\nYear: %d\nModel: %s\nFuel Type: %s\nCosumption: %.1lf\nSeats: %d\nDaily Price: %.3lf\nRented %d times\n",
               head->plate, head->year, head->model, head->fuelType, head->consumption, head->seats, head->dailyPrice,
               head->vehicelCounter);

        cnt++;
        if (cnt > 2) {
            break;
        }

        head = head->next;
        printf("\n");
    }
    printf("\n");
}

#endif
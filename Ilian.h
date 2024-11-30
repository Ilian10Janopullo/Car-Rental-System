#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structures.h"
#include "global.h"
#include "Unejsi.h"

#ifndef Ilian_H_INCLUDED
#define Ilian_H_INCLUDED


void getFileVehicel(struct vehicle **head, struct vehicle **tail) {

    struct vehicle *prev = NULL, *newVehicel = NULL;

    int cnt = 0;

    FILE *v1;

    v1 = fopen("vehicels.txt", "r");

    if (v1 == NULL) {
        return;
    }

    fscanf(v1, "%d", &vehicelCnt);

    while (cnt != vehicelCnt) {
        newVehicel = (struct vehicle *) malloc(sizeof(struct vehicle));
        newVehicel->next = NULL;

        fscanf(v1, "%s%d%s%s%lf%d%lf%d", newVehicel->plate, &newVehicel->year, newVehicel->model, newVehicel->fuelType,
               &newVehicel->consumption, &newVehicel->seats, &newVehicel->dailyPrice, &newVehicel->vehicelCounter);

        if (*head == NULL) {
            *head = newVehicel;
        } else {
            prev->next = newVehicel;
        }
        cnt++;
        prev = newVehicel;
    }
    (*tail) = prev;

    fclose(v1);
}


void getFileReservation(struct reservation **head, struct reservation **tail) {

    struct reservation *prev = NULL, *newReservation = NULL;

    int cnt = 0;

    FILE *r1;

    r1 = fopen("reservations.txt", "r");

    if (r1 == NULL) {
        return;
    }

    fscanf(r1, "%d%d", &reservationCnt, &reservationIDCnt);

    while (cnt != reservationCnt) {
        newReservation = (struct reservation *) malloc(sizeof(struct reservation));
        newReservation->next = NULL;

        fscanf(r1, "%d%d%d%lf%lld%lld%s", &newReservation->reservationID, &newReservation->clientID,
               &newReservation->nrOfDays, &newReservation->totalPrice, &newReservation->date,&newReservation->returnDate, newReservation->plate);

        if (*head == NULL) {
            *head = newReservation;
        } else {
            prev->next = newReservation;
        }
        cnt++;
        prev = newReservation;
    }
    (*tail) = prev;

    fclose(r1);
}


void getFileClient(struct client **head, struct client **tail) {

    struct client *prev = NULL, *newClient = NULL;

    int cnt = 0;

    FILE *c1;

    c1 = fopen("clients.txt", "r");

    if (c1 == NULL) {
        return;
    }

    fscanf(c1, "%d", &clientCnt);

    while (cnt != clientCnt) {
        newClient = (struct client *) malloc(sizeof(struct client));
        newClient->next = NULL;

        fscanf(c1, "%d%s%s%s%s%d%d", &newClient->clientID, newClient->name, newClient->surname, newClient->passport,
               newClient->state, &newClient->phoneNr, &newClient->clientCounter);

        if (*head == NULL) {
            *head = newClient;
        } else {
            prev->next = newClient;
        }
        cnt++;
        prev = newClient;
    }
    (*tail) = prev;

    fclose(c1);
}


void addVehicle(struct vehicle **head, struct vehicle **tail) {

    struct vehicle *newVehicle = NULL;
    newVehicle = (struct vehicle *) malloc(sizeof(struct vehicle));
    newVehicle->next = NULL;

    printf("Enter the data below : \n");

    printf("Plate number : ");
    scanf("%s", newVehicle->plate);

    printf("Year of the production : ");
    scanf("%d", &newVehicle->year);

    printf("Model : ");
    scanf("%s", newVehicle->model);

    printf("Fuel type : ");
    scanf("%s", newVehicle->fuelType);

    printf("Consumotion : ");
    scanf("%lf", &newVehicle->consumption);

    printf("Number of seats : ");
    scanf("%d", &newVehicle->seats);

    printf("Daily Price : ");
    scanf("%lf", &newVehicle->dailyPrice);

    int cnt = 0;

    newVehicle->vehicelCounter = cnt;

    if (*head == NULL) {
        *head = newVehicle;
        *tail = newVehicle;
    } else {
        (*tail)->next = newVehicle;
        (*tail) = newVehicle;
    }

    vehicelCnt++;
    printf("\n");
}


void addReservation(struct reservation **headR, struct reservation **tailR, struct client **headC, struct client **tailC,
               struct vehicle *headV, double profits[][13]) {


    if (vehicelCnt == 0) {
        printf("You cannot make a reservation, due to not owning any cars yet!\n");
    } else {
        struct reservation *newReservation = NULL;
        newReservation = (struct reservation *) malloc(sizeof(struct reservation));
        newReservation->next = NULL;


        printf("Enter the data below : \n");

        reservationIDCnt++;
        newReservation->reservationID = reservationIDCnt;

        int cnt = 0;

        printf("Vehicle plate number : ");

        while (cnt == 0) {

            struct vehicle *repeat = NULL;
            repeat = headV;

            struct reservation *oldReservations = NULL;
            oldReservations = (*headR);

            scanf("%s", newReservation->plate);

            if(*headR == NULL){
                break;
            }

            while((oldReservations != NULL) && (strcmp(newReservation->plate, oldReservations->plate) != 0)){
                oldReservations = oldReservations->next;
            }

            if(oldReservations==NULL){

            }

            else if (strcmp(oldReservations->plate, newReservation->plate)==0){
                    printf("This vehicel is already reserved! \n");
                    printf("\n");
                    return;
                }

            while ((repeat != NULL) && (strcmp(newReservation->plate, repeat->plate) != 0)) {

                repeat = repeat->next;

            }


            if (repeat == NULL) {
                printf("This plate does not belong to any vehicel! Enter the correct plate number : ");
            } else {
                repeat->vehicelCounter++;
                cnt++;
            }

        }

        printf("Number of days : ");
        scanf("%d", &newReservation->nrOfDays);

        newReservation->date = time(NULL);

        newReservation->returnDate = time(NULL)+((newReservation->nrOfDays)*86400);

        if(newReservation->nrOfDays >= 7){
            printf("Choose between fixed (1) and flexible (2) price : ");
            int operation;

            while (1) {
                scanf("%d", &operation);
                if (operation == 1) {
                    newReservation->totalPrice = newReservation->nrOfDays * headV->dailyPrice;
                    break;
                } else if (operation == 2) {
                    if (newReservation->nrOfDays <= 13) {
                        newReservation->totalPrice = 0.9 * (newReservation->nrOfDays * headV->dailyPrice);
                        break;
                    } else if (newReservation->nrOfDays <= 27) {
                        newReservation->totalPrice = 0.85 * (newReservation->nrOfDays * headV->dailyPrice);
                        break;
                    } else {
                        newReservation->totalPrice = 0.8 * (newReservation->nrOfDays * headV->dailyPrice);
                        break;
                    }
                } else {
                    printf("Invalid input! Enter the operation again : ");
                }
            }
        }

        else{
            newReservation->totalPrice = newReservation->nrOfDays * headV->dailyPrice;
        }

        

        addToProfits(10,13,profits, newReservation->totalPrice);

        printf("Client ID : ");
        scanf("%d", &newReservation->clientID);

        struct client *current = NULL;

        current = *headC;


        while ((current != NULL) && (current->clientID != newReservation->clientID)) {

            current = current->next;

        }

        if (current == NULL) {
            printf("\n");
            struct client *newClient = NULL;
            newClient = (struct client *) malloc(sizeof(struct client));
            newClient->next = NULL;

            printf("Enter the data for the new client : \n");
            newClient->clientID = newReservation->clientID;
            printf("Name : ");
            scanf("%s", newClient->name);
            printf("Surname : ");
            scanf("%s", newClient->surname);
            printf("Passport Number : ");
            scanf("%s", newClient->passport);
            printf("State : ");
            scanf("%s", newClient->state);
            printf("Phone Number : ");
            scanf("%d", &newClient->phoneNr);
            newClient->clientCounter = 1;

            if ((*headC) == NULL) {

                (*headC) = newClient;
                (*tailC) = newClient;
            } else {
                (*tailC)->next = newClient;
                (*tailC) = newClient;
            }

            clientCnt++;
        } else {
            current->clientCounter++;
        }


        if ((*headR) == NULL) {
            (*headR) = newReservation;
            (*tailR) = newReservation;
        } else {
            (*tailR)->next = newReservation;
            (*tailR) = newReservation;
        }

        reservationCnt++;
        printf("\n");
    }

}


void displayWithThrre(struct client *headV) {
    int f=0;

    if (headV == NULL) {
        printf("No client in the list!\n");
    } else {
        while (headV != NULL) {
            if (headV->clientCounter > 3) {
                printf("Name : %s\nSurname : %s\nClient ID : %d\n", headV->name, headV->surname, headV->clientID);
                printf("\n");
                f=1;
            }
            headV = headV->next;
        }
    }
    if(f==0){
        printf("No client have rented more than 3 cars!\n");
        printf("\n");
    }
}


void removeVehicle(struct vehicle **headV) {


    struct vehicle *prev = NULL, *current = NULL;

    if (*headV == NULL) {
        printf("No  cars owned! Nothing can be done!\n");
    } else {

        char plate[20];
        printf("Enter the plate of the vehicle you want to remove : ");
        int cnt = 1;


        while (cnt == 1) {

            scanf("%s", plate);
            current = *headV;

            if (strcmp(plate, current->plate) == 0) {
                *headV = current->next;
                free(current);
                cnt--;
            } else {

                while ((current != NULL) && (strcmp(plate, current->plate) != 0)) {
                    prev = current;
                    current = current->next;
                }


                if (current == NULL) {
                    printf("No car with this plate is owned! Enter the correct plate : ");
                } else if (strcmp(plate, current->plate) == 0) {
                    prev->next = current->next;
                    free(current);
                    cnt--;
                }
                vehicelCnt--;
            }
            printf("\n");
        }
    }
    printf("\n");
}


void printfFileVehicle(struct vehicle *head) {

    FILE *v2;
    v2 = fopen("vehicels.txt", "w");

    fprintf(v2, "%d\n", vehicelCnt);

    if (vehicelCnt == 0) {

    } else {
        while (head != NULL) {
            fprintf(v2, "%s %d %s %s %lf %d %lf %d\n", head->plate, head->year, head->model, head->fuelType,
                    head->consumption, head->seats, head->dailyPrice, head->vehicelCounter);
            head = head->next;
        }
    }
    fclose(v2);
}

void printfFileReservations(struct reservation *head) {

    FILE *r2;
    r2 = fopen("reservations.txt", "w");

    fprintf(r2, "%d %d\n", reservationCnt, reservationIDCnt);

    if (reservationCnt == 0) {

    } else {
        while (head != NULL) {
            fprintf(r2, "%d %d %d %lf %lld %lld %s\n", head->reservationID, head->clientID, head->nrOfDays, head->totalPrice,
                    head->date, head->returnDate, head->plate);
            head = head->next;
        }
    }
    fclose(r2);
}

void printfFileClients(struct client *head) {

    FILE *c2;
    c2 = fopen("clients.txt", "w");

    fprintf(c2, "%d\n", clientCnt);

    if (clientCnt == 0) {

    } else {
        while (head != NULL) {
            fprintf(c2, "%d %s %s %s %s %d %d\n", head->clientID, head->name, head->surname, head->passport,
                    head->state, head->phoneNr, head->clientCounter);
            head = head->next;
        }
    }
    fclose(c2);
}

#endif
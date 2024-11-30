#include <stdio.h>
#include <stdlib.h>
#include "global.h"
#include "structures.h"
#include "Ilian.h"
#include "Unejsi.h"
#include "Arion.h"
#include "Suljon.h"

int vehicelCnt = 0;
int reservationCnt = 0;
int clientCnt = 0;
int reservationIDCnt = 0;

void welcome();
void menu();

int main() {

    system("color 06");
    int option;
    struct vehicle *headV = NULL, *tailV = NULL;
    struct reservation *headR = NULL, *tailR = NULL;
    struct client *headC = NULL, *tailC = NULL;
    double profits[10][13];
    char months[13][10]={"Year", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};

    getFileVehicel(&headV, &tailV);
    getFileReservation(&headR, &tailR);
    getFileClient(&headC, &tailC);
    getFileProfits(10,13,profits,months);
    welcome();
    printf("\n");
    checkForDueDates(headR, headC);

    for (;;) {
        menu();

        scanf("%d", &option);

        switch (option) {
            case 1: {
                printf("\n");
                dsiplayAllVehicels(headV);
                
            }
                break;

            case 2: {
                printf("\n");
                displayAvailableVehicles(headV, headR);
            }
                break;

            case 3: {
                printf("\n");
                displayVehiclesAvailableAfterXDays(headV, headR);
            }
                break;

            case 4: {
                printf("\n");
                addReservation(&headR, &tailR, &headC, &tailC, headV, profits);
            }
                break;

            case 5: {
                printf("\n");
                addVehicle(&headV, &tailV);
            }
                break;

            case 6: {
                printf("\n");
                searchVehicleByPlate(headV);
            }
                break;

            case 7: {
                printf("\n");
                sort(headV);
            }
                break;

            case 8: {
                printf("\n");
                sortAndDisplay(headV);
            }
                break;

            case 9: {
                printf("\n");
                displayAllReservations(headR);
            }
                break;

            case 10: {
                printf("\n");
                removeVehicle(&headV);
            }
                break;

            case 11: {
                printf("\n");
                cancelReservation(&headR);
            }
                break;

            case 12: {
                printf("\n");
                displayWithThrre(headC);
            }
                break;

            case 13:
                printf("\n");
                saveResExceedingXPrice(headR);
                break;

            case 14: {
                printf("\n");
                modifyInformation(&headV);
            }
                break;

            case 15: {
                printf("\n");
                calculateBiggestProfit(10,13,profits);
            }
                break;

            case 16: {
                printf("\n");
                displayProfits(months,profits);
            }
                break;

            case 0: {
                printfFileVehicle(headV);
                printfFileReservations(headR);
                printfFileClients(headC);
                printFileProfits(10,13,profits,months);
            }
                return 0;

            default: {
                printf("\n");
                printf("Invalid Command!");
                printf("\n");
            }
                break;
        }
    }
}



void welcome() {
    printf("\n");
    printf("\t \t \t \t \t*********************************************\n");
    printf("\t \t \t \t \t*                                           *\n");
    printf("\t \t \t \t \t*                Welcome to                 *\n");
    printf("\t \t \t \t \t*                                           *\n");
    printf("\t \t \t \t \t*             HOT WHEELS Rental             *\n");
    printf("\t \t \t \t \t*                                           *\n");
    printf("\t \t \t \t \t*           Enjoy your experience!          *\n");
    printf("\t \t \t \t \t*                                           *\n");
    printf("\t \t \t \t \t*********************************************\n");
}


void menu() {
    printf("1- Display all vehicle information.\n\
2- Display available vehicles currently.\n\
3- Display vehicles that will be available after x days.\n\
4- Create a new reservation.\n\
5- Add a new vehicle.\n\
6- Search for a vehicle using the license plate number.\n\
7- Sort and display all vehicles according to their daily rental price.\n\
8- Display the top 3 most reserved vehicles.\n\
9- Display all reservations.\n\
10- Remove a vehicle. (delete)\n\
11- Cancel a reservation. (delete)\n\
12- Display the name, surname and Client ID of all clients who have rented a vehicle (not necessarily the same) more than 3 times.\n\
13- Save all reservations with a total cost exceeding x to a new file.\n\
14- Modify information for a vehicle using its plate number.\n\
15- Display the biggest monthly profit generated in a specific year.\n\
16- Display all profits made.\n\
0 - Close\n\
Choose the operation you want to make : ");
}
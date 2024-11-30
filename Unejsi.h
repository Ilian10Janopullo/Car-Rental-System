#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "global.h"
#include <time.h>
#include "Suljon.h"


void displayAvailableVehicles(struct vehicle *headV, struct reservation *headR);
void displayVehiclesAvailableAfterXDays(struct vehicle *headV, struct reservation *headR);
void saveResExceedingXPrice(struct reservation *headR);
void checkForDueDates(struct reservation *headR, struct client *headC);
void addToProfits(int rows, int cols, double profits[][cols], double totalPrice);
void calcCurrentYear(int *currentYear);
void calcCurrentMonth(char *currentMonth);
int findYearIndex(int rows, int cols, double profits[][cols], int year);
int findMonthIndex(char monthsArray[][10], char month[]);
void displayProfits(char months[][10], double profits[][13]);
void getFileProfits(int rows, int cols, double profits[][cols], char months[][10]);
void printFileProfits(int rows, int cols, double profits[][cols], char months[][10]);
void selSort(double x[], int n, char months[][10]);
int binarySearch(double arr[], double target);


#ifndef Unejsi_H_INCLUDED
#define Unejsi_H_INCLUDED

void displayAvailableVehicles(struct vehicle *headV, struct reservation *headR) {
    if (headV == NULL) {
        printf("\nThere are no vehicles registered\n");
        printf("\n");
    } else if (headR == NULL) { //If there are no reservations made it means that all vehicles are available
        dsiplayAllVehicels(headV);
    } else {
        while (headV != NULL) {
            int currentVehicleIsReserved = 0;

            struct reservation *temp = headR;
            while (temp != NULL) {
                if (strcmp(headV->plate, temp->plate) == 0) {
                    currentVehicleIsReserved = 1;
                    break;
                }
                temp = temp->next;
            }
            if (!(currentVehicleIsReserved)) {
                printf("Plate : %s\nYear : %d\nModel : %s\nFuel Type : %s\nConsumption : %.1lf l/km \nSeats : %d\nDaily Price : %.3lf\nRented : %d times\n",
                       headV->plate, headV->year, headV->model, headV->fuelType, headV->consumption, headV->seats,
                       headV->dailyPrice, headV->vehicelCounter);
                printf("\n");
            }
            headV = headV->next;
        }
    }
}




void displayVehiclesAvailableAfterXDays(struct vehicle *headV, struct reservation *headR) {

    if (headV == NULL) {
        printf("There are no vehicles registered.\n");
        printf("\n");
        return;
    } else if (headR == NULL) {
        printf("There are no reservations made.\n");
        printf("\n");
        return;
    } else {
        int x, found = 0;
        printf("Enter the number of days: ");
        scanf("%d", &x);

        struct vehicle *tempV = headV;
        struct reservation *tempR = headR;

        while(tempV != NULL){
            int pltFound=0;
            tempR = headR;

            while(tempR != NULL){
                if(strcmp(tempR->plate, tempV->plate) == 0){
                    pltFound = 1;
                    found = 1;
                    break;
                }
                tempR = tempR->next;
            }
            if(pltFound==0){
                printf("Plate : %s\nYear : %d\nModel : %s\nFuel Type : %s\nConsumption : %.1lf l/km \nSeats : %d\nDaily Price : %.3lf\nRented : %d times\nThis vehicle is not currently reserved\n",
                       tempV->plate, tempV->year, tempV->model, tempV->fuelType, tempV->consumption, tempV->seats,
                       tempV->dailyPrice, tempV->vehicelCounter);
                printf("\n");
            }
            tempV = tempV->next;
        }


        while (headR != NULL) {
            time_t rentedUntilDate = headR->date + (headR->nrOfDays * 86400);
            time_t todayDate = time(NULL);

            time_t dateToCheckIfAvail = todayDate + (x * 86400);
            if (dateToCheckIfAvail >= rentedUntilDate) {

                struct vehicle *temp = headV;
                while (temp != NULL) {
                    if (strcmp(headR->plate, temp->plate) == 0) {
                        time_t seconds = (time_t) rentedUntilDate;
                        char *date = ctime(&seconds);
                        date[strlen(date) - 1] = '0';
                        printf("Plate : %s\nYear : %d\nModel : %s\nFuel Type : %s\nConsumption : %.1lf l/km \nSeats : %d\nDaily Price : %.3lf\nRented : %d times\nThe vehicle will be available in: %s\n",
                               temp->plate, temp->year, temp->model, temp->fuelType, temp->consumption, temp->seats,
                               temp->dailyPrice, temp->vehicelCounter, date);
                        found = 1;
                        printf("\n");
                    }
                    temp = temp->next;
                }
            }
            headR = headR->next;
        }

        if (found == 0) {
            printf("There are no vehicles that will be available after %d days.\n", x);
        }
    }
}

void saveResExceedingXPrice(struct reservation *headR) {
    printf("Enter the cost of the reservation: ");
    double cost;
    int found = 0;
    scanf("%lf", &cost);
    FILE *fptr = fopen("reservationsExceedingX.txt", "a");

    if (headR == NULL) {
        printf("There are no current reservations.\n");
    } else {
        time_t now = time(NULL);
        char *date = ctime(&now);
        fprintf(fptr, "Reservations with a total cost exceeding %.2lf: These reservations were saved on: %s", cost,
                date);
        while (headR != NULL) {
            if (cost < headR->totalPrice) {
                time_t seconds = (time_t) headR->date;
                char *date1 = ctime(&seconds);
                fprintf(fptr, "Reservation ID : %d \nClient ID : %d\nNumber of days : %d\nPrice : %.3lf\nDate : %sVehicle plate : %s\n", headR->reservationID, headR->clientID, headR->nrOfDays,
                        headR->totalPrice, date1, headR->plate);
                found = 1;
                fprintf(fptr, "\n");
            }
            headR = headR->next;
        }
    }

    if (found == 1) {
        printf("Current reservations with a total cost exceeding %.2lf saved successfully.\n", cost);
    } else {
        printf("There are no reservations with a total cost that exceed %.2lf\n", cost);
    }

    printf("\n");

    fclose(fptr);
}

void checkForDueDates(struct reservation *headR, struct client *headC) {
    if (headR == NULL) {
        printf("There are no reservations available.\n");
        printf("\n");
        return;
    }
    int found = 0;

    while (headR != NULL) {
        time_t rentedUntilDate = headR->date + (headR->nrOfDays * 86400);
        time_t todayDate = time(NULL);

        if (todayDate >= rentedUntilDate) {
            int daysPast = (todayDate - rentedUntilDate) / 86400;
            int phoneNo = -1;
            while (headC != NULL) {
                if (headR->clientID == headC->clientID) {
                    phoneNo = headC->phoneNr;
                    break;
                }
                headC = headC->next;
            }
            if(daysPast>0){
                printf("Reservation with ID: %d and plate number: %s is past its due date date with %d days. Client phone number: %d\n",
                       headR->reservationID, headR->plate, daysPast, phoneNo);
            }

            found = 1;
        }
        headR = headR->next;
    }
    if (found == 0) {
        printf("There are no reservations which are past their due date.\n");
    }
    printf("\n");

}

void addToProfits(int rows, int cols, double profits[][cols], double totalPrice){
    char months[13][10]={"Year", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    FILE *fp = fopen("profits.txt", "r");

    int c = fgetc(fp);
    if (c == EOF) { //file empty

        int currentYear;
        calcCurrentYear(&currentYear);

        for(int i=0; i<rows; i++){

            for(int j=0; j<cols; j++){
                if(j==0){
                    profits[i][j]=currentYear;
                    currentYear++;
                }else{
                    profits[i][j]=0;
                }
            }
        }

        getFileProfits(rows,cols,profits,months);

        int currentYear2;
        calcCurrentYear(&currentYear2);

        char currentMonth[4];
        calcCurrentMonth((char *) &currentMonth);

        int yearIndex = findYearIndex(rows, cols, profits, currentYear2);
        int monthIndex = findMonthIndex(months,currentMonth);
        profits[yearIndex][monthIndex]+=totalPrice;
        printf("Total price added to profits!\n");
    } else {
        ungetc(c, fp);
        getFileProfits(rows,cols,profits,months);

        int currentYear;
        calcCurrentYear(&currentYear);

        char currentMonth[4];
        calcCurrentMonth((char *) &currentMonth);

        int yearIndex = findYearIndex(rows, cols, profits, currentYear);
        int monthIndex = findMonthIndex(months,currentMonth);
        profits[yearIndex][monthIndex]+=totalPrice;
        printf("Total price added to profits!\n");

    }

}

void calcCurrentYear(int *currentYear){
    time_t now = time(NULL);
    char *date = ctime(&now);
    char* token = strtok(date, " ");

    while (token != NULL) {
        *currentYear = atoi(token);
        token = strtok(NULL, " ");
    }
}

void calcCurrentMonth(char *currentMonth){
    time_t now = time(NULL);
    char *date = ctime(&now);
    char* token = strtok(date, " ");

    for (int i=0; token != NULL; i++) {
        if(i==1){
            strcpy(currentMonth, token);
        }
        token = strtok(NULL, " ");
    }
}

int findYearIndex(int rows, int cols, double profits[][cols], int year){
    for(int i=0; i<cols; i++){
        if(year == profits[i][0]){
            return i;
        }
    }
    return -1;
}

int findMonthIndex(char monthsArray[][10], char month[]){
    for(int i=1; i<13; i++){
        char str[10];
        strcpy(str,monthsArray[i]);
        char firstThree[4];

        strncpy(firstThree, str, 3);
        firstThree[3] = '\0';
        if(strcmp(month, firstThree) == 0){
            return i;
        }
    }
    return -1;
}

void calculateBiggestProfit(int rows, int cols, double profits[][cols]){
    double year;
    printf("Enter the year: ");
    scanf("%lf", &year);

    double yearsArr[10];
    for(int i=0; i<10; i++){
        yearsArr[i] = profits[i][0];
    }
    int yearIndex = binarySearch(yearsArr,year);
    if(yearIndex == -1){
        printf("No data available for this year.\n");
    }else{
        char months[12][10]={ "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
        double tempArray[12];
        for(int i=0; i<12; i++){
            tempArray[i] = profits[yearIndex][i+1];
        }
        selSort(tempArray,12, months);
        printf("\nThe month with the biggest profit in year %.lf was %s with a total profit of %.lf.\n", year, months[11], tempArray[11]);
    }
    printf("\n");
}

void displayProfits(char months[][10], double profits[][13]){
    for(int i=0; i<13; i++){
        if(i==0){
            printf("%s ", months[i]);
        }else if(i==3){
            printf("%s  ", months[i]);

        }
        else if(i==5){
            printf("  %s ", months[i]);
        }
        else if(i==6 || i==8){
            printf("   %s ", months[i]);
        }else if(i==7){
            printf("    %s ", months[i]);
        }
        else{
            printf(" %s ", months[i]);
        }
    }
    printf("\n");
    for(int i=0; i<10; i++){
        for(int j=0; j<13; j++){
            if(j==0){
                printf("%.lf ", profits[i][j]);
            }else if(j>=10){
                printf("\t  %.lf ", profits[i][j]);
            }
            else{
                printf("\t%.lf", profits[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

void selSort(double x[], int n, char months[][10]) {
    int k, j, m;
    double temp;
    char strTemp[10];

    for (k = 0; k <= n - 2; k++) {
        m = k;
        for (j = m + 1; j <= n - 1; j++)
            if (x[j] < x[m])
                m = j;
        temp = x[k];
        x[k] = x[m];
        x[m] = temp;
        strcpy(strTemp, months[k]);
        strcpy(months[k], months[m]);
        strcpy(months[m], strTemp);
    }
}

int binarySearch(double arr[], double target) {
    int left=0, right=9;
    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target)
            return mid;

        if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }

    return -1;
}


void getFileProfits(int rows, int cols, double profits[][cols], char months[][10]){
    FILE *fp;
    fp = fopen("profits.txt", "r");

    for(int i=0; i<13; i++){
        fscanf(fp, "%s", months[i]);
    }

    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            fscanf(fp, "%lf", &profits[i][j]);
        }
    }
    fclose(fp);

}


void printFileProfits(int rows, int cols, double profits[][cols], char months[][10]){
    FILE *fp;
    fp = fopen("profits.txt", "w");

    for(int i=0; i<13; i++){
        fprintf(fp, "%s ", months[i]);
    }
    fprintf(fp,"\n");

    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            fprintf(fp, "%.lf ", profits[i][j]);
        }
        fprintf(fp,"\n");
    }
    fclose(fp);
}

#endif //Unejsi_H_INCLUDED

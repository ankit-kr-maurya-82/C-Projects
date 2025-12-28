#include <stdio.h>
void display_time_menu();
void displayMenu();
void get_user_time();
int main(){
    int option;
    do
    {
        printf("------------FOOD ORDER SYSTEM--------------\n");
        printf("1. Display Menu\n");
        printf("2. Order Food\n");
        printf("3. Order History\n");
        printf("4. Exit\n");
        printf("--------------------------------------------\n");

        printf("Enter your choice: ");
        scanf("%d", &option);

        switch (option)
        {
        case 1 :
            printf("code 1");
            break;
        case 2 :
            printf("code 2");
            break;
        case 3 :
            printf("code 3");
            break;
        case 4 :
            printf("code 4");
            break;
        
        default:
            printf("Invalid choice!!");
        }
    } while (option != 4);
    return 0;
}

void displayMenu(){
}

void display_time_menu(){

    printf("---------------Time--------------\n");
    printf("Say Good Moring (1)\n");
    printf("Say Good Afternoon (2)\n");
    printf("Say Good Evening (3)\n");
    printf("---------------------------------\n");
}

void get_user_time(){
    int time = printf("Enter the Time:");
    switch (time)
    {
    case 1:
        printf("\nGood Morning");
        break;
    case 2:
        printf("\nGood Afternoon");
        break;
    case 3:
        printf("\nGood Evening");

    default:
        break;
    }
}
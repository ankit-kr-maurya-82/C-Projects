#include <stdio.h>

// Menu-Driven Program by Function
void display_time_menu();
void displayMenu();
void get_user_time();
void foodItemMorning();
void Drinks(int selectDrinks);

int main() {
    int user_choice;

    while (1) {
        printf("\n------------ FOOD ORDER SYSTEM --------------\n");
        printf("1. Time Greeting Menu\n");
        printf("2. Display Food Menu\n");
        printf("3. Order History\n");
        printf("4. Exit\n");
        printf("--------------------------------------------\n");

        printf("Enter your choice: ");
        scanf("%d", &user_choice);

        if (user_choice == 1) {
            display_time_menu();
            get_user_time();
        }
        else if (user_choice == 2) {
            displayMenu();
        }
        else if (user_choice == 3) {
            printf("No order history available.\n");
        }
        else if (user_choice == 4) {
            printf("Exiting program. Thank you!\n");
            break;   
        }
        else {
            printf("Invalid choice!\n");
        }
    }

    return 0;
}

// food menu
void displayMenu() {
    printf("\nFood Menu Coming Soon...\n");
}

// time menu
void display_time_menu() {
    printf("\n--------------- TIME MENU --------------\n");
    printf("1. Good Morning\n");
    printf("2. Good Afternoon\n");
    printf("3. Good Evening\n");
    printf("----------------------------------------\n");
}

//  logic
void get_user_time() {
    int time;
    printf("Enter your choice: ");
    scanf("%d", &time);

    switch (time) {
        case 1:
            printf("Good Morning \n");
            printf("Food Item \n");
            foodItemMorning();
            break;
        case 2:
            printf("Good Afternoon \n");
            break;
        case 3:
            printf("Good Evening \n");
            break;
        default:
            printf("Invalid time choice!\n");
    }
}

void foodItemMorning(){
    printf("Drinks (1)\n");
    printf("Snacks (2)\n");

    int selectUser;
    printf("enter item: ");
    scanf("%d", &selectUser);
    if(selectUser==1){
        printf("Hot Drinks (1)\n");
        printf("Cold Drinks (2)\n");

        int selectDrinks;
        printf("Select Drink: ");
        scanf("%d", &selectDrinks);

         Drinks(selectDrinks);

    }
}

// drinks functions
void Drinks(int selectDrinks){
    if(selectDrinks == 1){
        printf("Coca Cola");
    }else if(selectDrinks == 2){
        printf("Chai");
    }
}
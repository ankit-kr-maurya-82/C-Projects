#include <stdio.h>

// function declarations
void display_time_menu();
void displayMenu();
void get_user_time();

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

// food menu (dummy)
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

// greeting logic
void get_user_time() {
    int time;
    printf("Enter your choice: ");
    scanf("%d", &time);

    switch (time) {
        case 1:
            printf("Good Morning \n");
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

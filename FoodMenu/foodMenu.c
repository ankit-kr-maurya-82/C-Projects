#include <stdio.h>

/* ---------- Function Declarations ---------- */
void line();
void smallLine();

void displayMainMenu();
void displayTimeMenu();
void displayFoodMenu();

void getUserTime();
void foodItemMorning();
void drinksMenu(int choice);

/* ---------- MAIN FUNCTION ---------- */
int main() {
    int userChoice;

    while (1) {
        displayMainMenu();

        printf("Enter your choice: ");
        scanf("%d", &userChoice);

        switch (userChoice) {
            case 1:
                displayTimeMenu();
                getUserTime();
                break;

            case 2:
                displayFoodMenu();
                break;

            case 3:
                printf("\nNo order history available.\n");
                break;

            case 4:
                printf("\nThank you! Program exited successfully.\n");
                return 0;

            default:
                printf("\nInvalid choice! Try again.\n");
        }
    }
}

/* ---------- DESIGN FUNCTIONS ---------- */
void line() {
    printf("============================================\n");
}

void smallLine() {
    printf("--------------------------------------------\n");
}

/* ---------- MENU DISPLAY FUNCTIONS ---------- */
void displayMainMenu() {
    line();
    printf("        FOOD ORDER MANAGEMENT SYSTEM\n");
    line();
    printf("1. Time Greeting Menu\n");
    printf("2. Display Food Menu\n");
    printf("3. Order History\n");
    printf("4. Exit\n");
    line();
}

void displayTimeMenu() {
    smallLine();
    printf("            TIME GREETING MENU\n");
    smallLine();
    printf("1. Good Morning\n");
    printf("2. Good Afternoon\n");
    printf("3. Good Evening\n");
    smallLine();
}

void displayFoodMenu() {
    smallLine();
    printf("             FOOD MENU\n");
    smallLine();
    printf("Breakfast\n");
    printf("Lunch\n");
    printf("Dinner\n");
    smallLine();
}

/* ---------- LOGIC FUNCTIONS ---------- */
void getUserTime() {
    int timeChoice;

    printf("Enter your choice: ");
    scanf("%d", &timeChoice);

    switch (timeChoice) {
        case 1:
            printf("\nGood Morning ☀️\n");
            foodItemMorning();
            break;

        case 2:
            printf("\nGood Afternoon 🌤\n");
            break;

        case 3:
            printf("\nGood Evening 🌙\n");
            break;

        default:
            printf("\nInvalid time choice!\n");
    }
}

/* ---------- MORNING FOOD ---------- */
void foodItemMorning() {
    int choice;

    smallLine();
    printf("          MORNING FOOD MENU\n");
    smallLine();
    printf("1. Drinks\n");
    printf("2. Snacks\n");
    smallLine();

    printf("Select item: ");
    scanf("%d", &choice);

    if (choice == 1) {
        int drinkChoice;

        smallLine();
        printf("             DRINKS MENU\n");
        smallLine();
        printf("1. Hot Drink (Chai)\n");
        printf("2. Cold Drink (Coca Cola)\n");
        smallLine();

        printf("Select drink: ");
        scanf("%d", &drinkChoice);

        drinksMenu(drinkChoice);
    }
    else if (choice == 2) {
        printf("\nSnacks coming soon...\n");
    }
    else {
        printf("\nInvalid item choice!\n");
    }
}

/* ---------- DRINKS FUNCTION ---------- */
void drinksMenu(int choice) {
    smallLine();

    if (choice == 1) {
        printf("You selected: Chai ☕\n");
    }
    else if (choice == 2) {
        printf("You selected: Coca Cola 🥤\n");
    }
    else {
        printf("Invalid drink choice!\n");
    }

    smallLine();
}

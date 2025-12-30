#include <stdio.h>
#include <string.h>

/* ---------- Menu-Driven Program using Functions  ---------- */
void line();
void smallLine();
void dotLine();
void spaceTab(int num);

void displayMainMenu();
void displayTimeMenu();
void displayFoodMenu();

void getUserTime();
void foodItemMorning();
void drinksMenu(int choice);
void hotDrink();
void TeaList();
void orderChai(char *teaItem[],int itemList, float priceList[]);
void CoffeeList();
void orderCoffee(char *coffeeItem[], int itemList, float priceList[]);
void coldDrink();
void CarbonatedDrinksList();
void ColaList();

/* ---------- MAIN FUNCTION ---------- */
int main()
{
    int userChoice;

    while (1)
    {
        displayMainMenu();
        spaceTab(6);
        printf("Enter your choice: ");
        scanf("%d", &userChoice);

        switch (userChoice)
        {
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
void line()
{
    printf("============================================\n");
}

void smallLine()
{
    printf("--------------------------------------------\n");
}

void dotLine()
{
    printf("............................................\n");
}

void spaceTab(int num){

    for (int i = 0; i < num; i++)
    {
        printf("\t");
    }
    
}

/* ---------- MENU DISPLAY FUNCTIONS ---------- */
void displayMainMenu()
{
    spaceTab(5);
    line();
    spaceTab(6);
    printf("FOOD ORDER MANAGEMENT SYSTEM\n");
    spaceTab(5);
    line();
    spaceTab(6);
    printf("1. Time Greeting Menu\n");
    spaceTab(6);
    printf("2. Display Food Menu\n");
    spaceTab(6);
    printf("3. Order History\n");
    spaceTab(6);
    printf("4. Exit\n");
    spaceTab(5);
    line();
}

void displayTimeMenu()
{
    smallLine();
    printf("TIME GREETING MENU\n");
    smallLine();
    printf("1. Good Morning\n");
    printf("2. Good Afternoon\n");
    printf("3. Good Evening\n");
    smallLine();
}

void displayFoodMenu()
{
    smallLine();
    printf("\t\t\tFOOD MENU\n");
    smallLine();
    printf("Breakfast\n");
    printf("Lunch\n");
    printf("Dinner\n");
    smallLine();
}

/* ---------- LOGIC FUNCTIONS ---------- */
void getUserTime()
{
    int timeChoice;

    printf("Enter your choice: ");
    scanf("%d", &timeChoice);

    switch (timeChoice)
    {
    case 1:
        printf("\nGood Morning \n");
        foodItemMorning();
        break;

    case 2:
        printf("\nGood Afternoon \n");
        break;

    case 3:
        printf("\nGood Evening \n");
        break;

    default:
        printf("\nInvalid time choice!\n");
    }
}

/* ---------- MORNING FOOD ---------- */
void foodItemMorning()
{
    int choice;

    smallLine();
    printf("          MORNING FOOD MENU\n");
    smallLine();
    printf("1. Drinks\n");
    printf("2. Snacks\n");
    printf("3. Breakfast\n");
    smallLine();

    printf("Select item: ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        int drinkChoice;

        smallLine();
        printf("             DRINKS MENU\n");
        smallLine();
        printf("1. Hot Drink\n");
        printf("2. Cold Drink\n");
        smallLine();

        printf("Select drink: ");
        scanf("%d", &drinkChoice);

        drinksMenu(drinkChoice);
    }
    else if (choice == 2)
    {
        printf("\nSnacks coming soon...\n");
    }
    else
    {
        printf("\nInvalid item choice!\n");
    }
}

/* ---------- DRINKS FUNCTION ---------- */
void drinksMenu(int choice)
{

    if (choice == 1)
    {
        hotDrink();
    }
    else if (choice == 2)
    {
        coldDrink();
    }
    else
    {
        printf("Invalid drink choice!\n");
    }
}

void hotDrink()
{
    smallLine();
    printf("     LIST OF HOT DRINKS\n");
    dotLine();
    char hotDrinkList[2][20] = {"Chai", "Coffee"};

    for (int i = 0; i < 2; i++){
        printf(" %d. %s\n", i + 1, hotDrinkList[i]);
    }

    int selectedItem;
    printf("Choice your hot drink: ");
    scanf("%d", &selectedItem);

    if (selectedItem == 1){
        TeaList();
    }else if(selectedItem == 2){
        CoffeeList();
    }
}
void TeaList(){
    char *teaItem[] = {
        "Masala chai",
        "Adarak Chai",
        "Nimbu Chai",
        "Elaichi Chai",
        "Cutting Chai"
    };

    float priceList[] = {10, 40, 30, 10, 15};

    int itemList = sizeof(teaItem) / sizeof(teaItem[0]);

    for (int i = 0; i < itemList; i++){
        printf("%d. %s ___________________________ %.2f/-\n",
               i + 1, teaItem[i], priceList[i]);
    }

    orderChai(teaItem, itemList, priceList);
}

void orderChai(char *teaItem[], int itemList, float priceList[]){
    int selectChai;
    printf("Select a chai: ");
    scanf("%d", &selectChai);

    if (selectChai < 1 || selectChai > itemList){
        printf("Invalid choice!\n");
        return;
    }

    int qty;
    printf("Enter the quantity: ");
    scanf("%d", &qty);

    float totalAmount = qty * priceList[selectChai - 1];

    printf("\nItem: %s\n", teaItem[selectChai - 1]);
    printf("Price: %.2f\n", priceList[selectChai - 1]);
    printf("Total Amount: %.2f/-\n", totalAmount);
}

void CoffeeList(){
    char *coffeeItem[] = {
        "Black Coffee",
        "Cold Coffee",
        "Espresso Coffee",
        "Americano Coffee",
        "Latte Coffee",
        "Cappuccino Coffee",
        "Mocha Coffee",
        "Breve Coffee"
    };

    float priceList[] = {20, 30, 50, 80, 90, 140, 180, 190};

    int itemList = sizeof(coffeeItem) / sizeof(coffeeItem[0]);

    for(int i=0; i<itemList; i++){
        printf("%d. %s ___________________________ %.2f/-\n",
               i + 1, coffeeItem[i], priceList[i]);
    }

    orderCoffee(coffeeItem, itemList, priceList);
}


void orderCoffee(char *coffeeItem[], int itemList, float priceList[]){
    int selectCoffee;
    printf("Select a Coffee: ");
    scanf("%d", &selectCoffee);

    if(selectCoffee < 1 || selectCoffee > itemList){
        printf("Invalid choice!\n");
        return;
    }

    int qty;
    printf("Enter the quantity: ");
    scanf("%d", &qty);

    float totalAmount = qty * priceList[selectCoffee - 1];

    printf("\nItem: %s\n", coffeeItem[selectCoffee - 1]);
    printf("Price: %.2f\n", priceList[selectCoffee - 1]);
    printf("Total Amount: %.2f/-\n", totalAmount);
}


// Cold Drink

void coldDrink(){
    smallLine();
    printf("LIST IF HOT DRINKS\n");
    dotLine();
    char coldDrinkList[5][100] = {"Carbonated Drinks", "Non-Carbonated Drinks", "Traditional & Herbal Drinks", "Energy Drinks", "Iced Tea & Coffee"};
    for(int i=0;i<5;i++){
        printf(" %d. %s\n", i+1, coldDrinkList[i]);
    }

    int selectedItem;
    printf("Choice your cold drink: ");
    scanf("%d",&selectedItem);

    if(selectedItem == 1){
        CarbonatedDrinksList();
    }
}

void CarbonatedDrinksList(){
    char carbonatedDrinksItem[5][20] = {
        "Cola", 
        "Lemon-lime",
        "Fruit Flavored",
        "Ginger Ale",
        "Sparkling Water"
    };
    for(int i=0;i<5;i++){
        printf(" %d. %s\n", i+1, carbonatedDrinksItem[i]);
    }

     int selectedItem;
    printf("Choice your carbonatedDrinks drink: ");
    scanf("%d",&selectedItem);

    if(selectedItem == 1){
        ColaList();
    }

}

void ColaList(){

}
#include <stdio.h>
#include <string.h>
#include <windows.h>  // Windows
// Sleep(1000);

// <------Menu-Driven Program using  Functions-----> 

// <-------------------Structure------------------>
typedef struct {
    char name[50];
    float price;
} Drink;


// All functions


void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}



void line();
void smallLine();
void dotLine();
void spaceTab(int num);

void displayMainMenu();
void displayTimeMenu();
void displayFoodMenu();

void getUserTime();
void foodItemMorning();
// Calculator
void PriceCalculator(Drink items[], int choice);
void drinksMenu(int choice);
// Hot Drinks
void hotDrink();
void TeaList();  // Tea
void orderChai(Drink chai[], int count);
void CoffeeList(); // Coffee
void orderCoffee(Drink coffee[], int count);
// Cold Drinks
void coldDrink();
void CarbonatedDrinksList(); // Carbonated Drinks
void ColaList(); // Cola
void orderCola(Drink cola[], int count);
void LemonLimeList();
// Fruit Flavored
void FruitFlavoredList();
// Ginger ALe
void GingerAleList();
// Sparkling Water
void SparklingWaterList();
void orderHistory() {
    printf("Order history feature coming soon...\n");
}
displayDrinksMenu(){
    printf("display drinks feature coming soon...\n");

}


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
        clearScreen();

        switch (userChoice)
        {
        case 1:
            displayTimeMenu();
            getUserTime();
            break;

        case 2:
            orderHistory();
            break;
        case 3:
            displayDrinksMenu();
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


void PriceCalculator(Drink items[], int choice) {
    int qty;
    float totalAmount;

    printf("Enter the quantity: ");
    scanf("%d", &qty);

    totalAmount = qty * items[choice - 1].price;

    dotLine();
    printf("Item  : %s\n", items[choice - 1].name);
    printf("Price : %.2f\n", items[choice - 1].price);
    printf("Qty   : %d\n", qty);
    printf("Total : %.2f/-\n", totalAmount);
    dotLine();
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
    printf("1. Display Food Menu\n");
    spaceTab(6);
    printf("2. Order History\n");
    spaceTab(6);
    printf("3. Drinks Menu\n");
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



/* ---------- LOGIC FUNCTIONS ---------- */
void getUserTime()
{
    int timeChoice;

    printf("Enter your choice: ");
    scanf("%d", &timeChoice);
    clearScreen();

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
    clearScreen();

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
        clearScreen();


        drinksMenu(drinkChoice);
    }
    else if (choice == 2){
        printf("\nSnacks coming soon...\n");
    }
    else if (choice == 3){
        clearScreen();
        smallLine();
        printf("\n          Breakfast\n");
        printf("1. Sandwich");
        printf("1. Sandwich");
        printf("1. Sandwich");

    }
    else
    {
        printf("\nInvalid item choice!\n");
    }
}

/* ---------- DRINKS FUNCTION ---------- */
void drinksMenu(int choice)
{

    if (choice == 0){
        return;
    }
    if (choice == 1){
        hotDrink();
    }
    else if (choice == 2){
        coldDrink();
    }
    else{
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
    Drink chai[] = {
        {"Masala chai", 10},
        {"Adarak chai", 40},
        {"Nimbu chai", 15.5},
        {"Elaichi chai", 10},
        {"Cutting chai", 5}
    };

    int count = sizeof(chai) / sizeof(chai[0]);

    for (int i = 0; i < count; i++){
        printf("%d. %s ___________________________ %.2f/-\n",
               i + 1, chai[i].name, chai[i].price);
    }

    orderChai(chai, count);
}


void orderChai(Drink chai[], int count){
    int selectChai;
    printf("Select a chai: ");
    scanf("%d", &selectChai);
    clearScreen();

    if (selectChai < 1 || selectChai > count){
        printf("Invalid choice!\n");
        return;
    }

       PriceCalculator(chai, selectChai);

}

void CoffeeList(){
    Drink coffee[] = {
        {"Black Coffee", 20},
        {"Cold Coffee", 30},
        {"Espresso Coffee", 50},
        {"Americano Coffee", 80},
        {"Latte Coffee", 90},
        {"Cappuccino Coffee", 140},
        {"Mocha Coffee", 180},
        {"Breve Coffee", 190}
    };

    int count = sizeof(coffee) / sizeof(coffee[0]);

    for(int i = 0; i < count; i++){
        printf("%d. %s ___________________________ %.2f/-\n",
               i + 1, coffee[i].name, coffee[i].price);
    }

    orderCoffee(coffee, count);
}



void orderCoffee(Drink coffee[], int count){
    int selectCoffee;
    printf("Select a Coffee: ");
    scanf("%d", &selectCoffee);
    clearScreen();

    if(selectCoffee < 1 || selectCoffee > count){
        printf("Invalid choice!\n");
        return;
    }

    PriceCalculator(coffee, selectCoffee);
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
    char carbonatedDrinksItem[5][20] = {"Cola","Lemon-lime", "Fruit Flavored","Ginger Ale","Sparkling Water"
    };
    for(int i=0;i<5;i++){
        printf(" %d. %s\n", i+1, carbonatedDrinksItem[i]);
    }

     int selectedItem;
    printf("Choice your carbonatedDrinks drink: ");
    scanf("%d",&selectedItem);

    if(selectedItem == 1){
        ColaList();
    }else if(selectedItem == 2){
        LemonLimeList();
    }else if(selectedItem == 3){
        FruitFlavoredList();
    }else if(selectedItem == 4){
        GingerAleList();
    }else if(selectedItem == 5){
        SparklingWaterList();
    }

}

// Cola 
void ColaList() {
    Drink cola[] = {
        {"Coca-Cola", 15.3},
        {"Pepsi", 14.76},
        {"Thums Up", 45.94},
        {"Diet Coke", 50.83}
    };

    int count = sizeof(cola) / sizeof(cola[0]);

    dotLine();
    spaceTab(4);
    printf("COLA MENU\n");
    dotLine();

    for (int i = 0; i < count; i++) {
        printf("%d. %s ___________________________ %.2f/-\n",
               i + 1, cola[i].name, cola[i].price);
    }

    orderCola(cola, count);
}


void orderCola(Drink cola[], int count){
    int selectCola;
     printf("Select Cola: ");
    scanf("%d", &selectCola);
    clearScreen();

    if(selectCola < 1 || selectCola > count){
        printf("Invalid choice!\n");
        return;
    }

    PriceCalculator(cola, selectCola);
}

// LemonLine
void LemonLimeList(){}
// Fruit Flavored
void FruitFlavoredList(){}
// Ginger ALe
void GingerAleList(){}
// Sparkling Water
void SparklingWaterList(){}
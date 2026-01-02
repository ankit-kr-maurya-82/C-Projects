#include <stdio.h>
#include <string.h>
// #include <windows.h>  // Windows
#include <stdlib.h>

// Sleep(1000);


// <------Menu-Driven Program using  Functions-----> 

// <-------------------Structure------------------>
typedef struct {
    char name[50];
    float price;
} Item;



#define MAX_ORDERS 100

typedef struct{
    char name[30];
    float price;
    int qty;
    float total;
} Order;

Order orderHistory[MAX_ORDERS];
int orderCount = 0;


// file handling
#define ORDER_FILE "orders.dat"
void saveOrderToFile(Order o) {
    FILE *fp = fopen(ORDER_FILE, "ab"); // append binary
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fwrite(&o, sizeof(Order), 1, fp);
    fclose(fp);
}



void loadOrdersFromFile() {
    FILE *fp = fopen(ORDER_FILE, "rb");
    if (!fp) return;

    Order o;
    orderCount = 0;
    while(fread(&o, sizeof(Order), 1, fp)) {
        if(orderCount < MAX_ORDERS) {
            orderHistory[orderCount++] = o;
        }
    }
    fclose(fp);
}






void showOrderHistory();


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

void getUserTime();
void foodItemMorning();
// Calculator
void PriceCalculator(Item items[], int choice);
void drinksMenu(int choice);
// Hot Drinks
void hotDrink();
void TeaList();  // Tea
void orderTea(Item tea[], int count);
void CoffeeList(); // Coffee
void orderCoffee(Item coffee[], int count);
// Cold Drinks
void coldDrink();
void CarbonatedDrinksList(); // Carbonated Drinks
void ColaList(); // Cola
void orderCola(Item cola[], int count);
void LemonLimeList();
// Fruit Flavored
void FruitFlavoredList();
// Ginger ALe
void GingerAleList();
// Sparkling Water
void SparklingWaterList();
void showOrderHistory();
void displayDrinksMenu(){
    printf("display drinks feature coming soon...\n");

}

// breakfast
void breakfastMenu(int choice);
void sandwichList();
void burgerList();
void omletList();
void noodleList();


void orderSandwich(Item[], int);
void orderBurger(Item[], int);
void orderOmlet(Item[], int);
void orderNoodle(Item[], int);


/* ---------- MAIN FUNCTION ---------- */
int main()
{
    loadOrdersFromFile();  // Load old orders from file

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
            showOrderHistory();
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

void showOrderHistory() {
    clearScreen();
    smallLine();
    printf("ORDER HISTORY\n");
    smallLine();

    FILE *fp = fopen("orders.dat", "rb");
    if (fp == NULL) {
        printf("No orders found.\n");
        return;
    }

    Order o;
    int count = 0;
    float grandTotal = 0;
    while (fread(&o, sizeof(Order), 1, fp)) {
        count++;
        printf("%d. %s\n", count, o.name);
        printf("   Price : %.2f\n", o.price);
        printf("   Qty   : %d\n", o.qty);
        printf("   Total : %.2f\n", o.total);
        printf("---------------------------------\n");
        grandTotal += o.total;
    }
    fclose(fp);

    if(count == 0){
        printf("No orders placed yet.\n");
    } else {
        printf("GRAND TOTAL: %.2f\n", grandTotal);
    }

    printf("\nPress Enter to go back...");
    getchar();
    getchar();
    clearScreen();
}



void PriceCalculator(Item items[], int choice) {
    int qty;
    float totalAmount;

    printf("Enter the quantity: ");
    scanf("%d", &qty);

    totalAmount = qty * items[choice - 1].price;

    // Save to memory (optional)
    if (orderCount < MAX_ORDERS) {
        strcpy(orderHistory[orderCount].name, items[choice - 1].name);
        orderHistory[orderCount].price = items[choice - 1].price;
        orderHistory[orderCount].qty = qty;
        orderHistory[orderCount].total = totalAmount;
        orderCount++;
    }

    // Save to file
    Order o;
    strcpy(o.name, items[choice - 1].name);
    o.price = items[choice - 1].price;
    o.qty = qty;
    o.total = totalAmount;
    saveOrderToFile(o);

    dotLine();
    printf("Item  : %s\n", items[choice - 1].name);
    printf("Price : %.2f\n", items[choice - 1].price);
    printf("Qty   : %d\n", qty);
    printf("Total : %.2f/-\n", totalAmount);
    dotLine();

    printf("Press Enter to continue...");
    getchar();
    getchar();
    clearScreen();
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
    printf("2. Breakfast\n");
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
        int breakfastChoice;
        clearScreen();
        smallLine();
        printf("\n          Breakfast\n");
        smallLine();
        printf("1. Sandwich\n");
        printf("2. Burger\n");
        printf("3. Omlet\n");
        printf("4. Noodle\n");
        smallLine();

        printf("Select Breakfast: ");
        scanf("%d", &breakfastChoice);
        clearScreen();

        breakfastMenu(breakfastChoice);
    }else{
        printf("\nInvalid item choice!\n");
    }
}

//  ------------- Breakfast Function --------
void breakfastMenu(int choice){
    if(choice == 0){
        return;
    }else if(choice == 1){
        sandwichList();
    }else if(choice == 2){
        burgerList();
    }else if(choice == 3){
        omletList();
    }else if(choice == 4){
        noodleList();
    }else{
        printf("Invalid breakfast choice!\n");
    }
}

void sandwichList(){
    Item sandwich[] = {
        {"layered Bombay Sandwich",36.54},
        {"Paneer Tikka Sandwich", 87.43},
        {"Aloo Tikki Sandwich", 36.93},
        {"Veg Masala Sandwich", 54.62},
        {"Chutney Sandwich", 32.64},
        {"Chicken Tikka Sandwich", 96.64},
        {"Egg Bhurji Sandwich", 94.24},
        {"Keema Sandwich", 85.00},
        {"Boiled Egg Sandwich", 87.90}
    };

    int count = sizeof(sandwich) / sizeof(sandwich[0]);

    for(int i=0; i<count; i++){
         printf("%d. %s ___________________________ %.2f/-\n",
               i + 1, sandwich[i].name, sandwich[i].price);
    }

    orderSandwich(sandwich, count);
}

void orderSandwich(Item sandwich[], int count){
    int selectItem;
    printf("Select a sandwich: ");
    scanf("%d", &selectItem);
    clearScreen();

    if (selectItem < 1 || selectItem > count){
        printf("Invalid choice!\n");
        return;
    }

       PriceCalculator(sandwich, selectItem);

}



void burgerList(){
    Item burger[] = {
        {"Aloo Tikki Burger", 169.75},
        {"Paneer Burger", 149.84},
        {"Tandoori Chicken Burger", 329.74},
        {"Veggie Burger",132.85},
        {"Chicken Burger", 247.84},
        {"Mutton/Lamb Burger", 549.35},
        {"Zinger Burger",549.73}
    };
    int count = sizeof(burger) / sizeof(burger[0]);

    for(int i=0; i<count; i++){
         printf("%d. %s ___________________________ %.2f/-\n",
               i + 1, burger[i].name, burger[i].price);
    }
    orderBurger(burger, count);

}

void orderBurger(Item burger[], int count){
    int selectItem;
    printf("Select a burger: ");
    scanf("%d", &selectItem);
    clearScreen();

    if (selectItem < 1 || selectItem > count){
        printf("Invalid choice!\n");
        return;
    }

       PriceCalculator(burger, selectItem);

}

void omletList(){
    Item omlet[] = {
        {"Masala Omelette", 374.75},
        {"Bread Omelette", 346.84},
        {"Tandoori Omelette", 214.74},
        {"Cheese Omelette",325.85},
        {"Paneer Omelette", 435.84},
        {"Mushroom Omelette", 453.35},
        {"Spinach Omelette",435.73},
        {"Chapati Omelette Roll",465.73}
    };
    int count = sizeof(omlet) / sizeof(omlet[0]);

    for(int i=0; i<count; i++){
         printf("%d. %s ___________________________ %.2f/-\n",
               i + 1, omlet[i].name, omlet[i].price);
    }
    orderOmlet(omlet, count);
}

void orderOmlet(Item omlet[], int count){
    int selectItem;
    printf("Select a burger: ");
    scanf("%d", &selectItem);
    clearScreen();

    if (selectItem < 1 || selectItem > count){
        printf("Invalid choice!\n");
        return;
    }

       PriceCalculator(omlet, selectItem);

}



void noodleList(){
    Item noodle[] = {
        {"Maggi",36.54},
        {"Sunfeast YiPPee!", 87.43},
        {"Ching's Secret", 36.93},
        {"Top Ramen", 54.62},
        {"Knorr", 32.64},
        {"Patanjali", 96.64},
        {"Wai Wai", 94.24},
        {"Hakka Noodles", 85.00},
        {"Chowmein", 87.90},
        {"Thukpa", 87.90},
        {"Idiyappam", 87.90},
        {"Seviyan (Vermicelli)", 87.90},
        {"Chilli Garlic Noodles", 87.90},
        {"Ramen", 87.90},
    };

    int count = sizeof(noodle) / sizeof(noodle[0]);

    for(int i=0; i<count; i++){
         printf("%d. %s ___________________________ %.2f/-\n",
               i + 1, noodle[i].name, noodle[i].price);
    }

    orderNoodle(noodle, count);
}


void orderNoodle(Item noodle[], int count){
    int selectItem;
    printf("Select a burger: ");
    scanf("%d", &selectItem);
    clearScreen();

    if (selectItem < 1 || selectItem > count){
        printf("Invalid choice!\n");
        return;
    }

       PriceCalculator(noodle, selectItem);

}


/* ---------- DRINKS FUNCTION ---------- */
void drinksMenu(int choice){

    if (choice == 0){
        return;
    }else if (choice == 1){
        hotDrink();
    }else if (choice == 2){
        coldDrink();
    }else{
        printf("Invalid drink choice!\n");
    }
}

void hotDrink(){
    smallLine();
    printf("     LIST OF HOT DRINKS\n");
    dotLine();
    char hotDrinkList[2][20] = {"Tea", "Coffee"};

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
    Item tea[] = {
        {"Masala tea", 10},
        {"Adarak tea", 40},
        {"Nimbu tea", 15.57},
        {"Elaichi tea", 10.39},
        {"Green tea", 30.58}
    };

    int count = sizeof(tea) / sizeof(tea[0]);

    for (int i = 0; i < count; i++){
        printf("%d. %s ___________________________ %.2f/-\n",
               i + 1, tea[i].name, tea[i].price);
    }

    orderTea(tea, count);
}


void orderTea(Item tea[], int count){
    int selectTea;
    printf("Select a tea: ");
    scanf("%d", &selectTea);
    clearScreen();

    if (selectTea < 1 || selectTea > count){
        printf("Invalid choice!\n");
        return;
    }

       PriceCalculator(tea, selectTea);

}

void CoffeeList(){
    Item coffee[] = {
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



void orderCoffee(Item coffee[], int count){
    int selectItem;
    printf("Select a Coffee: ");
    scanf("%d", &selectItem);
    clearScreen();

    if(selectItem < 1 || selectItem > count){
        printf("Invalid choice!\n");
        return;
    }

    PriceCalculator(coffee, selectItem);
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
    Item cola[] = {
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


void orderCola(Item cola[], int count){
    int selectItem;
     printf("Select Cola: ");
    scanf("%d", &selectItem);
    clearScreen();

    if(selectItem < 1 || selectItem > count){
        printf("Invalid choice!\n");
        return;
    }

    PriceCalculator(cola, selectItem);
}

// LemonLine
void LemonLimeList(){
    printf("LemonLime coming soon...............\n");
}
// Fruit Flavored
void FruitFlavoredList(){
    printf("Fruit Flavored coming soon...............\n");
}
// Ginger ALe
void GingerAleList(){
    printf("Ginger Ale coming soon...............\n");
}
// Sparkling Water
void SparklingWaterList(){
    printf("Sparkling Water coming soon...............\n");
}
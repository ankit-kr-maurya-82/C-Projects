#include <stdio.h>
#include <string.h>
// #include <windows.h>  // Windows
#include <stdlib.h>
#include <math.h>

// Sleep(1000);

// <------Menu-Driven Program using  Functions----->

// <-------------------Structure------------------>
typedef struct
{
    char name[50];
    float price;
} Item;

#define MAX_ORDERS 100

typedef struct
{
    char category[50];
    char name[50];
    float price;
    int qty;
    float total;
} Order;

Order orderHistory[MAX_ORDERS];
int orderCount = 0;

// file handling
#define ORDER_FILE "orders.dat"
void saveOrderToFile(Order o)
{
    FILE *fp = fopen(ORDER_FILE, "ab"); // append binary
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    o.name[sizeof(o.name) - 1] = '\0';
    size_t written = fwrite(&o, sizeof(Order), 1, fp);
    if (written != 1)
    {
        printf("Error writing order to file.\n");
    }
    fclose(fp);
}

void loadOrdersFromFile()
{
    FILE *fp = fopen(ORDER_FILE, "rb");
    if (!fp)
        return;

    Order o;
    orderCount = 0;
    // read all orders and keep only valid ones
    Order validOrders[MAX_ORDERS];
    int validCount = 0;
    int corrupted = 0;
    while (fread(&o, sizeof(Order), 1, fp) == 1)
    {
        o.name[sizeof(o.name) - 1] = '\0';
        int qty_ok = (o.qty > 0 && o.qty <= 10000);
        int price_ok = isfinite(o.price) && o.price > 0.0f && o.price < 100000.0f;
        int total_ok = isfinite(o.total) && o.total >= 0.0f;
        float expected_total = o.price * (float)o.qty;
        int total_matches = fabsf(o.total - expected_total) <= fmaxf(1.0f, 0.01f * fabsf(expected_total));

        if (qty_ok && price_ok && total_ok && total_matches)
        {
            if (validCount < MAX_ORDERS)
                validOrders[validCount++] = o;
        }
        else
        {
            corrupted = 1;
        }
    }
    fclose(fp);

    // populate in-memory history
    for (int i = 0; i < validCount && i < MAX_ORDERS; ++i)
    {
        orderHistory[orderCount++] = validOrders[i];
    }

    // if corruption detected, rewrite file with only valid orders
    if (corrupted)
    {
        FILE *wf = fopen(ORDER_FILE, "wb");
        if (wf)
        {
            for (int i = 0; i < validCount; ++i)
            {
                fwrite(&validOrders[i], sizeof(Order), 1, wf);
            }
            fclose(wf);
        }
    }
}

void showOrderHistory();

// All functions

void clearScreen()
{
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
void foodItemAfternoon();
// Calculator
void PriceCalculator(Item items[], int choice, const char *category);
void drinksMenu(int choice);
// Hot Drinks
void hotDrink();
void TeaList(); // Tea
void orderTea(Item tea[], int count);
void CoffeeList(); // Coffee
void orderCoffee(Item coffee[], int count);
// Mini Cold Drinks
void miniColdDrink();
void coldDrink();

// Carbonated Drinks
void CarbonatedDrinksList();

void ColaList(); // Cola
void orderCola(Item cola[], int count);
void LemonLimeList();
// Fruit Flavored
void FruitFlavoredList();
// Ginger ALe
void GingerAleList();
// Sparkling Water
void SparklingWaterList();

// Non-Carbonated Drinks
void NonCarbonatedDrinksList();
void JuiceList();
void orderJuice(Item[], int);
void ShakesList();
void orderShakes(Item[], int);
void DairyBasedList();
void orderDairyBased(Item[], int);
void CoconutWaterList();
void orderCoconutWater(Item[], int);

void showOrderHistory();

// Drinks Menu
void displayDrinksMenu();

// breakfast
void breakfastMenu(int choice);
void sandwichList();
void burgerList();
void omletList();
void noodleList();

// lunch
void VegLunchFoodMenu();
void MainCarbList();
void DalList();
void VegeDishList();
void SweetList();
void RiceDishList();

void orderMainCarb(Item[], int);
void orderDal(Item[], int);
void orderVegDish(Item[], int);
void orderSweet(Item[], int);
void orderRiceDish(Item[], int);

void NonVegLunchFoodMenu();

void orderSandwich(Item[], int);
void orderBurger(Item[], int);
void orderOmlet(Item[], int);
void orderNoodle(Item[], int);
void orderLemonLime(Item[], int);
void orderfruitFlavored(Item[], int);
void orderGingerAle(Item[], int);
void orderSparklingWater(Item[], int);

/* ---------- MAIN FUNCTION ---------- */
int main()
{
    loadOrdersFromFile(); // Load old orders from file

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

void spaceTab(int num)
{

    for (int i = 0; i < num; i++)
    {
        printf("\t");
    }
}

void showOrderHistory()
{
    clearScreen();
    smallLine();
    printf("ORDER HISTORY\n");
    smallLine();

    if (orderCount == 0)
    {
        printf("No orders placed yet.\n");
    }
    else
    {
        float grandTotal = 0.0f;

        for (int i = 0; i < orderCount; ++i)
        {
            Order *o = &orderHistory[i];

            printf("%d. Category : %s\n", i + 1, o->category);
            printf("   Item  : %s\n", o->name);
            printf("   Price : %.2f\n", o->price);
            printf("   Qty   : %d\n", o->qty);
            printf("   Total : %.2f\n", o->total);
            printf("---------------------------------\n");

            grandTotal += o->total;
        }

        printf("GRAND TOTAL: %.2f\n", grandTotal);
    }

    printf("\nPress Enter to go back...");
    getchar();
    getchar();
    clearScreen();
}

void PriceCalculator(Item items[], int choice, const char *category)
{
    int qty;
    float totalAmount;

    printf("Item  : %s\n", items[choice - 1].name);
    printf("Enter the quantity: ");
    scanf("%d", &qty);

    totalAmount = qty * items[choice - 1].price;

    // Save to memory (optional)
    if (orderCount < MAX_ORDERS)
    {
        strcpy(orderHistory[orderCount].category, category);
        strcpy(orderHistory[orderCount].name, items[choice - 1].name);
        orderHistory[orderCount].price = items[choice - 1].price;
        orderHistory[orderCount].qty = qty;
        orderHistory[orderCount].total = totalAmount;
        orderCount++;
    }

    // Save to file
    Order o;
    strcpy(o.category, category);
    strncpy(o.name, items[choice - 1].name, sizeof(o.name) - 1);
    o.name[sizeof(o.name) - 1] = '\0';
    o.price = items[choice - 1].price;
    o.qty = qty;
    o.total = totalAmount;
    saveOrderToFile(o);

    dotLine();
    printf("Category  : %s\n", category);
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
    printf("\t\t\t\t0. Back\n");
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
    case 0:
        return;
    case 1:
        printf("\nGood Morning \n");
        foodItemMorning();
        break;

    case 2:
        printf("\nGood Afternoon \n");
        foodItemAfternoon();
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
    printf("\t\t\t\t0. Back\n");
    smallLine();

    printf("Select item: ");
    scanf("%d", &choice);
    clearScreen();
    if (choice == 0)
    {
        return;
    }
    else if (choice == 1)
    {
        int drinkChoice;

        smallLine();
        printf("             DRINKS MENU\n");
        smallLine();
        printf("1. Hot Drink\n");
        printf("\t\t\t\t0. Cold Drink\n");
        smallLine();

        printf("Select drink: ");
        scanf("%d", &drinkChoice);
        clearScreen();

        drinksMenu(drinkChoice);
    }
    else if (choice == 2)
    {
        int breakfastChoice;
        clearScreen();
        smallLine();
        printf("\n          Breakfast\n");
        smallLine();
        printf("1. Sandwich\n");
        printf("2. Burger\n");
        printf("3. Omlet\n");
        printf("4. Noodle\n");
        printf("\t\t\t\t0. Back\n");
        smallLine();

        printf("Select Breakfast: ");
        scanf("%d", &breakfastChoice);
        clearScreen();

        breakfastMenu(breakfastChoice);
    }
    else
    {
        printf("\nInvalid item choice!\n");
    }
}

//  ------------- Breakfast Function --------
void breakfastMenu(int choice)
{
    if (choice == 0)
    {
        return;
    }
    else if (choice == 1)
    {
        sandwichList();
    }
    else if (choice == 2)
    {
        burgerList();
    }
    else if (choice == 3)
    {
        omletList();
    }
    else if (choice == 4)
    {
        noodleList();
    }
    else
    {
        printf("Invalid breakfast choice!\n");
    }
}

void sandwichList()
{
    Item sandwich[] = {
        {"layered Bombay Sandwich", 36.54},
        {"Paneer Tikka Sandwich", 87.43},
        {"Aloo Tikki Sandwich", 36.93},
        {"Veg Masala Sandwich", 54.62},
        {"Chutney Sandwich", 32.64},
        {"Chicken Tikka Sandwich", 96.64},
        {"Egg Bhurji Sandwich", 94.24},
        {"Keema Sandwich", 85.00},
        {"Boiled Egg Sandwich", 87.90}};

    int count = sizeof(sandwich) / sizeof(sandwich[0]);

    for (int i = 0; i < count; i++)
    {
        printf("%d. %s ___________________________ %.2f/-\n",
               i + 1, sandwich[i].name, sandwich[i].price);
    }

    orderSandwich(sandwich, count);
}

void orderSandwich(Item sandwich[], int count)
{
    int selectItem;
    printf("Select a sandwich: ");
    scanf("%d", &selectItem);
    clearScreen();

    if (selectItem < 1 || selectItem > count)
    {
        printf("Invalid choice!\n");
        return;
    }

    PriceCalculator(sandwich, selectItem, "Sandwich");
}

void burgerList()
{
    Item burger[] = {
        {"Aloo Tikki Burger", 169.75},
        {"Paneer Burger", 149.84},
        {"Tandoori Chicken Burger", 329.74},
        {"Veggie Burger", 132.85},
        {"Chicken Burger", 247.84},
        {"Mutton/Lamb Burger", 549.35},
        {"Zinger Burger", 549.73}};
    int count = sizeof(burger) / sizeof(burger[0]);

    for (int i = 0; i < count; i++)
    {
        printf("%d. %s ___________________________ %.2f/-\n",
               i + 1, burger[i].name, burger[i].price);
    }
    orderBurger(burger, count);
}

void orderBurger(Item burger[], int count)
{
    int selectItem;
    printf("Select a burger: ");
    scanf("%d", &selectItem);
    clearScreen();

    if (selectItem < 1 || selectItem > count)
    {
        printf("Invalid choice!\n");
        return;
    }

    PriceCalculator(burger, selectItem, "Burger");
}

void omletList()
{
    Item omlet[] = {
        {"Masala Omelette", 374.75},
        {"Bread Omelette", 346.84},
        {"Tandoori Omelette", 214.74},
        {"Cheese Omelette", 325.85},
        {"Paneer Omelette", 435.84},
        {"Mushroom Omelette", 453.35},
        {"Spinach Omelette", 435.73},
        {"Chapati Omelette Roll", 465.73}};
    int count = sizeof(omlet) / sizeof(omlet[0]);

    for (int i = 0; i < count; i++)
    {
        printf("%d. %s ___________________________ %.2f/-\n",
               i + 1, omlet[i].name, omlet[i].price);
    }
    orderOmlet(omlet, count);
}

void orderOmlet(Item omlet[], int count)
{
    int selectItem;
    printf("Select a omlet: ");
    scanf("%d", &selectItem);
    clearScreen();

    if (selectItem < 1 || selectItem > count)
    {
        printf("Invalid choice!\n");
        return;
    }

    PriceCalculator(omlet, selectItem, "Omlet");
}

void noodleList()
{
    Item noodle[] = {
        {"Maggi", 36.54},
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

    for (int i = 0; i < count; i++)
    {
        printf("%d. %s ___________________________ %.2f/-\n",
               i + 1, noodle[i].name, noodle[i].price);
    }

    orderNoodle(noodle, count);
}

void orderNoodle(Item noodle[], int count)
{
    int selectItem;
    printf("Select a noodle: ");
    scanf("%d", &selectItem);
    clearScreen();

    if (selectItem < 1 || selectItem > count)
    {
        printf("Invalid choice!\n");
        return;
    }

    PriceCalculator(noodle, selectItem, "Noodle");
}

/*------------------Drinks Menu-----------------*/
void displayDrinksMenu()
{

    int choice;
    smallLine();
    printf("DRINKS MENU\n");
    smallLine();
    printf("1. Hot Drink\n");
    printf("2. Cold Drink\n");
    printf("0. Back\n");
    printf("Choice: ");
    scanf("%d", &choice);
    clearScreen();

    switch (choice)
    {
    case 1:
        hotDrink();
        break;
    case 2:
        coldDrink();
        break;
    case 0:
        return;
    default:
        printf("Invalid choice!\n");
    }
}

/* ---------- DRINKS FUNCTION ---------- */
void drinksMenu(int choice)
{

    if (choice == 0)
    {
        return;
    }
    else if (choice == 1)
    {
        hotDrink();
    }
    else if (choice == 2)
    {
        miniColdDrink();
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
    char hotDrinkList[2][20] = {"Tea", "Coffee"};

    for (int i = 0; i < 2; i++)
    {
        printf(" %d. %s\n", i + 1, hotDrinkList[i]);
    }

    int selectedItem;
    printf("Choice your hot drink: ");
    scanf("%d", &selectedItem);

    if (selectedItem == 0)
    {
        return;
    }
    else if (selectedItem == 1)
    {
        TeaList();
    }
    else if (selectedItem == 2)
    {
        CoffeeList();
    }
}

void TeaList()
{
    Item tea[] = {
        {"Masala tea", 10},
        {"Adarak tea", 40},
        {"Lemon tea", 15.57},
        {"Elaichi tea", 10.39},
        {"Green tea", 30.58}};

    int count = sizeof(tea) / sizeof(tea[0]);

    for (int i = 0; i < count; i++)
    {
        printf("%d. %s ___________________________ %.2f/-\n",
               i + 1, tea[i].name, tea[i].price);
    }

    orderTea(tea, count);
}

void orderTea(Item tea[], int count)
{
    int selectTea;
    printf("Select a tea: ");
    scanf("%d", &selectTea);
    clearScreen();

    if (selectTea < 1 || selectTea > count)
    {
        printf("Invalid choice!\n");
        return;
    }

    PriceCalculator(tea, selectTea, "Tea");
}

void CoffeeList()
{
    Item coffee[] = {
        {"Black Coffee", 20},
        {"Cold Coffee", 30},
        {"Espresso Coffee", 50},
        {"Americano Coffee", 80},
        {"Latte Coffee", 90},
        {"Cappuccino Coffee", 140},
        {"Mocha Coffee", 180},
        {"Breve Coffee", 190}};

    int count = sizeof(coffee) / sizeof(coffee[0]);

    for (int i = 0; i < count; i++)
    {
        printf("%d. %s ___________________________ %.2f/-\n",
               i + 1, coffee[i].name, coffee[i].price);
    }

    orderCoffee(coffee, count);
}

void orderCoffee(Item coffee[], int count)
{
    int selectItem;
    printf("Select a Coffee: ");
    scanf("%d", &selectItem);
    clearScreen();

    if (selectItem < 1 || selectItem > count)
    {
        printf("Invalid choice!\n");
        return;
    }

    PriceCalculator(coffee, selectItem, "Coffee");
}

// Cold Drink
void coldDrink()
{
    smallLine();
    printf("LIST IF COLD DRINKS\n");
    dotLine();
    char coldDrinkList[5][100] = {"Carbonated Drinks", "Non-Carbonated Drinks", "Traditional & Herbal Drinks", "Energy Drinks", "Iced Tea & Coffee"};
    for (int i = 0; i < 5; i++)
    {
        printf(" %d. %s\n", i + 1, coldDrinkList[i]);
    }

    int selectedItem;
    printf("Choice your cold drink: ");
    scanf("%d", &selectedItem);

    if (selectedItem == 0)
    {
        return;
    }
    else if (selectedItem == 1)
    {
        CarbonatedDrinksList();
    }
    else if (selectedItem == 2)
    {
        NonCarbonatedDrinksList();
    }
}
// Mini Cold Drink
void miniColdDrink()
{
    smallLine();
    printf("LIST OF COLD DRINKS\n");
    dotLine();
    char coldDrinkList[2][100] = {"Carbonated Drinks", "Non-Carbonated Drinks"};
    for (int i = 0; i < 2; i++)
    {
        printf(" %d. %s\n", i + 1, coldDrinkList[i]);
    }

    int selectedItem;
    printf("Choice your cold drink: ");
    scanf("%d", &selectedItem);

    if (selectedItem == 0)
    {
        return;
    }
    else if (selectedItem == 1)
    {
        CarbonatedDrinksList();
    }
}
// Carbonated Drinks
void CarbonatedDrinksList()
{
    char carbonatedDrinksItem[5][20] = {"Cola", "Lemon-lime", "Fruit Flavored", "Ginger Ale", "Sparkling Water"};
    for (int i = 0; i < 5; i++)
    {
        printf(" %d. %s\n", i + 1, carbonatedDrinksItem[i]);
    }

    int selectedItem;
    printf("Choice your carbonated drink: ");
    scanf("%d", &selectedItem);

    if (selectedItem == 0)
    {
        return;
    }
    else if (selectedItem == 1)
    {
        ColaList();
    }
    else if (selectedItem == 2)
    {
        LemonLimeList();
    }
    else if (selectedItem == 3)
    {
        FruitFlavoredList();
    }
    else if (selectedItem == 4)
    {
        GingerAleList();
    }
    else if (selectedItem == 5)
    {
        SparklingWaterList();
    }
}

// Cola
void ColaList()
{
    Item cola[] = {
        {"Coca-Cola", 15.3},
        {"Pepsi", 14.76},
        {"Thums Up", 45.94},
        {"Diet Coke", 50.83}};

    int count = sizeof(cola) / sizeof(cola[0]);

    dotLine();
    spaceTab(4);
    printf("COLA MENU\n");
    dotLine();

    for (int i = 0; i < count; i++)
    {
        printf("%d. %s ___________________________ %.2f/-\n",
               i + 1, cola[i].name, cola[i].price);
    }

    orderCola(cola, count);
}

void orderCola(Item cola[], int count)
{
    int selectItem;
    printf("Select Cola: ");
    scanf("%d", &selectItem);
    clearScreen();

    if (selectItem < 1 || selectItem > count)
    {
        printf("Invalid choice!\n");
        return;
    }
    PriceCalculator(cola, selectItem, "Cola");
}

// LemonLine
void LemonLimeList()
{
    Item lemonLime[] = {
        {"Sprite", 120},
        {"7UP", 67},
        {"Limca", 30},
        {"Mountain Dew", 78},
    };
    int count = sizeof(lemonLime) / sizeof(lemonLime[0]);

    for (int i = 0; i < count; i++)
    {
        printf("%d. %s ___________________________ %.2f/-\n",
               i + 1, lemonLime[i].name, lemonLime[i].price);
    }
    orderLemonLime(lemonLime, count);
}

void orderLemonLime(Item orderLemonLime[], int count)
{
    int selectItem;
    printf("Select orderLemonLime: ");
    scanf("%d", &selectItem);
    clearScreen();

    if (selectItem < 1 || selectItem > count)
    {
        printf("Invalid choice!\n");
        return;
    }

    PriceCalculator(orderLemonLime, selectItem, "LemonLime");
}
// Fruit Flavored
void FruitFlavoredList()
{
    Item fruitFlavored[] = {
        {"Fanta", 43},
        {"Mirinda", 76},
    };
    int count = sizeof(fruitFlavored) / sizeof(fruitFlavored[0]);

    for (int i = 0; i < count; i++)
    {
        printf("%d. %s ___________________________ %.2f/-\n",
               i + 1, fruitFlavored[i].name, fruitFlavored[i].price);
    }
    orderfruitFlavored(fruitFlavored, count);
}

void orderfruitFlavored(Item fruitFlavored[], int count)
{
    int selectItem;
    printf("Select orderfruitFlavored: ");
    scanf("%d", &selectItem);
    clearScreen();

    if (selectItem < 1 || selectItem > count)
    {
        printf("Invalid choice!\n");
        return;
    }

    PriceCalculator(fruitFlavored, selectItem, "OrderfruitFlavored");
}
// Ginger ALe
void GingerAleList()
{
    Item gingerAle[] = {
        {"Schweppes", 54.65},
    };

    int count = sizeof(gingerAle) / sizeof(gingerAle[0]);

    for (int i = 0; i < count; i++)
    {
        printf("%d. %s ___________________________ %.2f/-\n",
               i + 1, gingerAle[i].name, gingerAle[i].price);
    }

    orderGingerAle(gingerAle, count);
}

void orderGingerAle(Item gingerAle[], int count)
{
    int selectItem;
    printf("Select gingerAle: ");
    scanf("%d", &selectItem);
    clearScreen();

    if (selectItem < 1 || selectItem > count)
    {
        printf("Invalid choice!\n");
        return;
    }

    PriceCalculator(gingerAle, selectItem, "GingerAle");
}

// Sparkling Water
void SparklingWaterList()
{
    Item sparklingWater[] = {
        {"Plain", 20},
    };
    int count = sizeof(sparklingWater) / sizeof(sparklingWater[0]);

    for (int i = 0; i < count; i++)
    {
        printf("%d. %s ___________________________ %.2f/-\n",
               i + 1, sparklingWater[i].name, sparklingWater[i].price);
    }
    orderSparklingWater(sparklingWater, count);
}

void orderSparklingWater(Item sparklingWater[], int count)
{
    int selectItem;
    printf("Select sparklingWater: ");
    scanf("%d", &selectItem);
    clearScreen();

    if (selectItem < 1 || selectItem > count)
    {
        printf("Invalid choice!\n");
        return;
    }

    PriceCalculator(sparklingWater, selectItem, "SparklingWater");
}

// Non-Carbonated Drinks

void NonCarbonatedDrinksList()
{
    char nonCarbonatedDrinksItem[4][20] = {"Juices", "Shakes", "Dairy-Based", "Coconut Water"};
    for (int i = 0; i < 4; i++)
    {
        printf(" %d. %s\n", i + 1, nonCarbonatedDrinksItem[i]);
    }

    int selectedItem;

    printf("Choice your non-carbonated drink: ");
    scanf("%d", &selectedItem);

    if (selectedItem == 0)
    {
        return;
    }
    else if (selectedItem == 1)
    {
        JuiceList();
    }
    else if (selectedItem == 2)
    {
        ShakesList();
    }
    else if (selectedItem == 3)
    {
        DairyBasedList();
    }
    else if (selectedItem == 4)
    {
        CoconutWaterList();
    }
}

void JuiceList()
{
    Item juice[] = {
        {"Orange", 195},
        {"Apple", 154},
        {"Mango", 175},
        {"Mixed Fruit", 132},
    };
    int count = sizeof(juice) / sizeof(juice[0]);

    for (int i = 0; i < count; i++)
    {
        printf("%d. %s ___________________________ %.2f/-\n",
               i + 1, juice[i].name, juice[i].price);
    }
    orderJuice(juice, count);
}
void orderJuice(Item Juice[], int count)
{
    int selectItem;
    printf("Select Juice: ");
    scanf("%d", &selectItem);
    clearScreen();

    if (selectItem < 1 || selectItem > count)
    {
        printf("Invalid choice!\n");
        return;
    }

    PriceCalculator(Juice, selectItem, "Juice");
}
void ShakesList()
{
    Item shakes[] = {
        {"Chocolate Shake", 65},
        {"Mango Shake", 96},
        {"Banana Shake", 75},
        {"Milk shakes", 54},
        {"Papaya Shake", 32},
    };
    int count = sizeof(shakes) / sizeof(shakes[0]);

    for (int i = 0; i < count; i++)
    {
        printf("%d. %s ___________________________ %.2f/-\n",
               i + 1, shakes[i].name, shakes[i].price);
    }
    orderShakes(shakes, count);
}
void orderShakes(Item Shakes[], int count)
{
    int selectItem;
    printf("Select Shakes: ");
    scanf("%d", &selectItem);
    clearScreen();

    if (selectItem < 1 || selectItem > count)
    {
        printf("Invalid choice!\n");
        return;
    }

    PriceCalculator(Shakes, selectItem, "Shakes");
}
void DairyBasedList()
{
    Item dairyBase[] = {
        {"ButterMilk", 32},
        {"Lassi", 43},
        {"Milk shakes", 54},
        {"Chocolate Milk", 85},
    };
    int count = sizeof(dairyBase) / sizeof(dairyBase[0]);

    for (int i = 0; i < count; i++)
    {
        printf("%d. %s ___________________________ %.2f/-\n",
               i + 1, dairyBase[i].name, dairyBase[i].price);
    }
    orderDairyBased(dairyBase, count);
}
void orderDairyBased(Item DairyBased[], int count)
{
    int selectItem;
    printf("Select Dairy Based: ");
    scanf("%d", &selectItem);
    clearScreen();

    if (selectItem < 1 || selectItem > count)
    {
        printf("Invalid choice!\n");
        return;
    }

    PriceCalculator(DairyBased, selectItem, "DairyBased");
}
void CoconutWaterList()
{
    Item coconutWater[] = {
        {"Natural Water", 50},
        {"Refresh Water", 58},
    };
    int count = sizeof(coconutWater) / sizeof(coconutWater[0]);

    for (int i = 0; i < count; i++)
    {
        printf("%d. %s ___________________________ %.2f/-\n",
               i + 1, coconutWater[i].name, coconutWater[i].price);
    }
    orderCoconutWater(coconutWater, count);
}
void orderCoconutWater(Item CoconutWater[], int count)
{
    int selectItem;
    printf("Select Coconut Water: ");
    scanf("%d", &selectItem);
    clearScreen();

    if (selectItem < 1 || selectItem > count)
    {
        printf("Invalid choice!\n");
        return;
    }

    PriceCalculator(CoconutWater, selectItem, "CoconutWater");
}

// -------------- NOON FOOD------------------

void foodItemAfternoon()
{
    int choice;
    int lunchChoice;

    smallLine();
    printf("          EVENING FOOD MENU\n");
    smallLine();
    printf("1. Veg\n");
    printf("2. Non-Veg\n");
    printf("\t\t\t\t0. Back\n");
    smallLine();

    printf("Select item: ");
    scanf("%d", &choice);
    clearScreen();
    switch (choice)
    {
    case 1:
        VegLunchFoodMenu();
        break;
    case 2:
        NonVegLunchFoodMenu();
        break;
    case 0:
        return;
    default:
        printf("Invalid choice!\n");
    }
}

//  ------------- Lunch Function --------

void VegLunchFoodMenu()
{
    char vegLunchFoodItem[5][20] = {"Main Carb", "Dal", "Vegetable Dish", "Sweet", "Rice Dishes"};
    for (int i = 0; i < 5; i++)
    {
        printf(" %d. %s\n", i + 1, vegLunchFoodItem[i]);
    }

    int selectedItem;
    printf("Choice your Lunch ");
    scanf("%d", &selectedItem);

    if (selectedItem == 0)
    {
        return;
    }
    else if (selectedItem == 1)
    {
        MainCarbList();
    }
    else if (selectedItem == 2)
    {
        DalList();
    }
    else if (selectedItem == 3)
    {
        VegeDishList();
    }
    else if (selectedItem == 4)
    {
        SweetList();
    }
    else if (selectedItem == 5)
    {
        RiceDishList();
    }
}

void MainCarbList()
{
    Item maincarb[] = {
        {"Roti", 20},
        {"Paratha", 30},
        {"Jeera Rice", 45},
        {"Pulao", 56},
    };

    int count = sizeof(maincarb) / sizeof(maincarb[0]);
    dotLine();
    spaceTab(4);
    printf("MAIN CARB MENU\n");
    dotLine();

    for (int i = 0; i < count; i++)
    {
        printf("%d. %s ___________________________ %.2f/-\n",
               i + 1, maincarb[i].name, maincarb[i].price);
    }

    orderMainCarb(maincarb, count);
}

void orderMainCarb(Item maincarb[], int count)
{
    int selectItem;
    printf("Select Main Carb: ");
    scanf("%d", &selectItem);
    clearScreen();

    if (selectItem < 1 || selectItem > count)
    {
        printf("Invalid choice!\n");
        return;
    }
    PriceCalculator(maincarb, selectItem, "Main Carb");
}

void DalList()
{
    Item dal[] = {
        {"Dal Makhani", 154},
        {"Dal Tadka", 326},
        {"Kadi Pakora", 246},
        {"Toor Dal", 165},
        {"Moong Dal", 136},
    };

    int count = sizeof(dal) / sizeof(dal[0]);
    dotLine();
    spaceTab(4);
    printf("DAL MENU\n");
    dotLine();

    for (int i = 0; i < count; i++)
    {
        printf("%d. %s ___________________________ %.2f/-\n",
               i + 1, dal[i].name, dal[i].price);
    }

    orderMainCarb(dal, count);
}

void orderDal(Item dal[], int count)
{
    int selectItem;
    printf("Select Dal: ");
    scanf("%d", &selectItem);
    clearScreen();

    if (selectItem < 1 || selectItem > count)
    {
        printf("Invalid choice!\n");
        return;
    }
    PriceCalculator(dal, selectItem, "Dal");
}

void VegeDishList(){

    Item vegdish[] = {
        {"Palak Paneer", 154},
        {"Aloo Matar", 326},
        {"Mixed Veg", 246},
        {"Kadai Paneer", 165},
    };

    int count = sizeof(vegdish) / sizeof(vegdish[0]);
    dotLine();
    spaceTab(4);
    printf("VEGETABLE DISH  MENU\n");
    dotLine();

    for (int i = 0; i < count; i++){
        printf("%d. %s ___________________________ %.2f/-\n",
               i + 1, vegdish[i].name, vegdish[i].price);
    }

    orderMainCarb(vegdish, count);
}

void orderVegDish(Item vegdish[], int count)
{
    int selectItem;
    printf("Select Vegetable  Dish: ");
    scanf("%d", &selectItem);
    clearScreen();

    if (selectItem < 1 || selectItem > count)
    {
        printf("Invalid choice!\n");
        return;
    }
    PriceCalculator(vegdish, selectItem, "Vegetable Dish");
}

void SweetList()
{
    Item sweet[] = {
        {"Gulab Jamun", 154},
        {"Rasgulla", 326},
        {"Kheer", 246},
        {"Jalebi", 165},
    };

    int count = sizeof(sweet) / sizeof(sweet[0]);
    dotLine();
    spaceTab(4);
    printf("SWEET MENU\n");
    dotLine();

    for (int i = 0; i < count; i++){
        printf("%d. %s ___________________________ %.2f/-\n",
               i + 1, sweet[i].name, sweet[i].price);
    }

    orderMainCarb(sweet, count);
}

void orderSweet(Item sweet[], int count)
{
    int selectItem;
    printf("Select Sweet: ");
    scanf("%d", &selectItem);
    clearScreen();

    if (selectItem < 1 || selectItem > count)
    {
        printf("Invalid choice!\n");
        return;
    }
    PriceCalculator(sweet, selectItem, "Sweet");
}
void RiceDishList(){

    Item ricedish[] = {
        {"Simple Rice", 154},
        {"Jeera Rice", 326},
        {"Vegetable Pulao", 246},
        {"Fried Rice", 165},
    };

    int count = sizeof(ricedish) / sizeof(ricedish[0]);
    dotLine();
    spaceTab(4);
    printf("RICE DISH MENU\n");
    dotLine();

    for (int i = 0; i < count; i++){
        printf("%d. %s ___________________________ %.2f/-\n",
               i + 1, ricedish[i].name, ricedish[i].price);
    }

    orderMainCarb(ricedish, count);
}

void orderRiceDish(Item ricedish[], int count)
{
    int selectItem;
    printf("Select Vegetable  Dish: ");
    scanf("%d", &selectItem);
    clearScreen();

    if (selectItem < 1 || selectItem > count)
    {
        printf("Invalid choice!\n");
        return;
    }
    PriceCalculator(ricedish, selectItem, "Rice Dish");
}

void NonVegLunchFoodMenu()
{
    printf("Non-Veg menu coming soon...\n");
}

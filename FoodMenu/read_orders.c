#include <stdio.h>
#include <string.h>

typedef struct {
    char name[30];
    float price;
    int qty;
    float total;
} Order;

void saveOrder(Order o) {
    FILE *fp = fopen("orders.dat", "ab"); // "ab" = append in binary
    if (fp == NULL) {
        printf("Unable to open file!\n");
        return;
    }
    fwrite(&o, sizeof(Order), 1, fp);
    fclose(fp);
}

void showAllOrders() {
    FILE *fp = fopen("orders.dat", "rb"); // read binary
    if (fp == NULL) {
        printf("No orders found.\n");
        return;
    }

    Order o;
    int count = 0;
    printf("========= ORDER HISTORY =========\n");
    while (fread(&o, sizeof(Order), 1, fp)) {
        count++;
        printf("%d. %s | Price: %.2f | Qty: %d | Total: %.2f\n",
               count, o.name, o.price, o.qty, o.total);
    }

    if(count == 0) {
        printf("No orders placed yet.\n");
    }
    printf("=================================\n");
    fclose(fp);
}

int main() {
    int choice;
    while (1) {
        printf("1. Add Order\n2. Show All Orders\n3. Exit\nChoice: ");
        scanf("%d", &choice);
        getchar(); // consume newline

        if (choice == 1) {
            Order o;
            printf("Enter Item Name: ");
            fgets(o.name, sizeof(o.name), stdin);
            o.name[strcspn(o.name, "\n")] = 0; // remove newline

            printf("Enter Price: ");
            scanf("%f", &o.price);
            printf("Enter Quantity: ");
            scanf("%d", &o.qty);

            o.total = o.price * o.qty;

            saveOrder(o);
            printf("Order saved!\n\n");
        } 
        else if (choice == 2) {
            showAllOrders();
        } 
        else if (choice == 3) {
            break;
        } 
        else {
            printf("Invalid choice!\n");
        }
    }

    return 0;
}

#include <stdio.h>
#include <string.h>

// Define a structure to hold item details
struct Item {
    char name[50];
    int quantity;
    float price;
    float total;
};

int main() {
    int numItems, i;
    float grandTotal = 0.0;
    float discount = 0.0;
    float netTotal = 0.0;
    char customerName[50];
    char phone[20];

    // --- Collect Customer Details ---
    printf("Enter Customer Name: ");
    fgets(customerName, sizeof(customerName), stdin);
    customerName[strcspn(customerName, "\n")] = 0; // Remove newline

    printf("Enter Customer Phone: ");
    fgets(phone, sizeof(phone), stdin);
    phone[strcspn(phone, "\n")] = 0; // Remove newline

    printf("\n--- Shopping Bill Generator ---\n");
    printf("Enter the number of items: ");
    scanf("%d", &numItems);

    // Create an array of Item structures
    struct Item items[numItems];

    // Loop to get details for each item
    for (i = 0; i < numItems; i++) {
        printf("\nEnter details for Item %d:\n", i + 1);

        // Consume the newline character left by the previous scanf
        while (getchar() != '\n'); 

        printf("  Item Name: ");
        scanf("%49[^\n]", items[i].name);

        printf("  Quantity: ");
        scanf("%d", &items[i].quantity);

        printf("  Price per unit: ");
        scanf("%f", &items[i].price);

        // Calculate the total for the current item
        items[i].total = items[i].quantity * items[i].price;
        grandTotal += items[i].total;
    }

    // --- Print the Bill ---
    printf("\n\n================= CUSTOMER BILL =================\n");
    printf("Customer Name : %s\n", customerName);
    printf("Phone Number  : %s\n", phone);
    printf("-------------------------------------------------\n");
    printf("%-10s %-20s %-10s %-15s %-10s\n", 
           "Item No.", "Item Name", "Quantity", "Price/Unit", "Total Price");
    printf("-------------------------------------------------\n");

    // Loop through the items and print their details
    for (i = 0; i < numItems; i++) {
        printf("%-10d %-20s %-10d %-15.2f %-10.2f\n", 
               i + 1, 
               items[i].name, 
               items[i].quantity, 
               items[i].price, 
               items[i].total);
    }
    
    printf("-------------------------------------------------\n");
    printf("%60s: %.2f\n", "SUB TOTAL", grandTotal);

    // --- Discount Calculation ---
    if (grandTotal >= 25000) {
        discount = grandTotal * 0.15;   // 15% discount
        printf("%60s: -%.2f\n", "DISCOUNT (15%)", discount);
    }
    else if (grandTotal >= 10000) {
        discount = grandTotal * 0.07;   // 7% discount
        printf("%60s: -%.2f\n", "DISCOUNT (7%)", discount);
    }
    else if (grandTotal >= 5000) {
        discount = grandTotal * 0.05;   // 5% discount
        printf("%60s: -%.2f\n", "DISCOUNT (5%)", discount);
    }

    netTotal = grandTotal - discount;
    
    printf("-------------------------------------------------\n");
    printf("%60s: %.2f\n", "NET PAYABLE", netTotal);
    printf("-------------------------------------------------\n");
    printf("\nThank you for shopping with us!\n");
    printf("=================================================\n");

    return 0;
}

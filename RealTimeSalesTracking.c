/*
CMPUT 201 LAB 2, University Of ALberta
Program: Developed a program to efficiently track and analyze product sales statistics in real-time for profit optimization.
Author: Jeremy Ajoku

binary search from https://www.geeksforgeeks.org/binary-search/
bubble sort from https://webdocs.cs.ualberta.ca/~ghlin/CMPUT201/bubblesort.c

*/


#include <stdio.h>
#include <stdlib.h>

// Function to sort products by product_ID in ascending order using Bubble Sort
void bubble_sort(int product_IDs[], int manufacturer_sale_prices[], int retail_prices[], int n) {
    for (int j = 0; j < n - 1; j++) {
        for (int i = 0; i < n - j - 1; i++) {
            if (product_IDs[i] > product_IDs[i + 1]) {
                // this swaps product_IDs inline
                int temp_ID = product_IDs[i];
                product_IDs[i] = product_IDs[i + 1];
                product_IDs[i + 1] = temp_ID;

                // this swaps corresponding manufacturer_sale_prices inline
                int temp_manufacturer_price = manufacturer_sale_prices[i];
                manufacturer_sale_prices[i] = manufacturer_sale_prices[i + 1];
                manufacturer_sale_prices[i + 1] = temp_manufacturer_price;

                // this swaps corresponding retail_prices inline
                int temp_retail_price = retail_prices[i];
                retail_prices[i] = retail_prices[i + 1];
                retail_prices[i + 1] = temp_retail_price;
            }
        }
    }
}

// Function to count occurrences of a product ID starting from the first occurrence index
int count_occurrences(int arr[], int size, int start_index, int key) {
    int count = 0;
    for (int i = start_index; i < size && arr[i] == key; i++) {
        count++;
    }
    return count;
}

// Binary search function to find the first occurrence of the key
int binary_search_first(int arr[], int size, int key) {
    int left = 0, right = size - 1;
    int result = -1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == key) {
            result = mid;
            right = mid - 1;  // Keep searching to the left for the first occurrence
        } else if (arr[mid] < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return result;
}

// Function to sort sold products by profit margin descending using Bubble Sort
void bubble_sort_sales(int sold_indices[], int manufacturer_sale_prices[], int retail_prices[], int quantities_sold[], int sold_count) {
    for (int j = 0; j < sold_count - 1; j++) {
        for (int i = 0; i < sold_count - j - 1; i++) {
            // Calculate profit margins
            float profit_margin_i = ((float)(retail_prices[sold_indices[i]] - manufacturer_sale_prices[sold_indices[i]]) / retail_prices[sold_indices[i]]);
            float profit_margin_j1 = ((float)(retail_prices[sold_indices[i + 1]] - manufacturer_sale_prices[sold_indices[i + 1]]) / retail_prices[sold_indices[i + 1]]);

            if (profit_margin_i < profit_margin_j1) {
                // Swap the indices
                int temp = sold_indices[i];
                sold_indices[i] = sold_indices[i + 1];
                sold_indices[i + 1] = temp;
            }
        }
    }
}

// Function to display sales information
void display_sales_info(int no_of_inputs, int product_IDs[], int manufacturer_sale_prices[], int retail_prices[], int quantities_sold[]) {
    // Collect indices of products that have been sold
    int sold_indices[no_of_inputs];
    int sold_count = 0;
    
    for (int i = 0; i < no_of_inputs; i++) {
        if (quantities_sold[i] > 0) {
            sold_indices[sold_count++] = i;
        }
    }

    // Handle the case where no products have been sold
    if (sold_count == 0) {
        printf("Sales:\n");
        printf("No sales made yet.\n\n");
        return;
    }

    // Sort the sold products by profit margin descending
    bubble_sort_sales(sold_indices, manufacturer_sale_prices, retail_prices, quantities_sold, sold_count);

    // Print the table header
    printf("Sales:\n");
    printf("+---------+---------+------------+--------+\n");
    printf("| ID      | Sold    | Profit ($) | GM (%%) |\n");
    printf("+---------+---------+------------+--------+\n");

    float total_profit = 0.0f;
    float sumM = 0.0f;
    int sumQ = 0;

    // Print each sold product
    for (int i = 0; i < sold_count; i++) {
        int index = sold_indices[i];
        int profit_per_unit = retail_prices[index] - manufacturer_sale_prices[index];
        int total_profit_product = profit_per_unit * quantities_sold[index];
        float profit_margin = ((float)profit_per_unit / retail_prices[index]) * 100.0f;

        printf("| %-7d | %-7d | %-10d | %6.2f |\n",
               product_IDs[index],
               quantities_sold[index],
               total_profit_product,
               profit_margin);

        total_profit += total_profit_product;
        sumM += profit_margin * quantities_sold[index];
        sumQ += quantities_sold[index];
    }

    printf("+---------+---------+------------+--------+\n");

    // Calculate average profit margin
    float avgM = 0.0f;
    if (sumQ > 0) {
        avgM = sumM / sumQ;
    }

    // Print total profit and average GM
    printf("Total profit: $%.0f\n", total_profit);
    printf("Average GM: %.2f%%\n\n", avgM);
}


int main() {
    int no_of_inputs, product_ID, manufacturer_sale_price, retail_price;

    // Input the number of products
    if (scanf("%d", &no_of_inputs) != 1) {

        return 1;
    }

    // Define arrays 
    int max_inputs = no_of_inputs;  
    int product_IDs[max_inputs];
    int manufacturer_sale_prices[max_inputs];
    int retail_prices[max_inputs];
    int quantities_sold[max_inputs];

    // Initialize quantities_sold to 0
    for (int i = 0; i < max_inputs; i++) {
        quantities_sold[i] = 0;
    }

    // Input product information
    for (int i = 0; i < no_of_inputs; i++) {
        if (scanf("%d %d %d", &product_ID, &manufacturer_sale_price, &retail_price) != 3) {
            
            return 1;
        }
        product_IDs[i] = product_ID;
        manufacturer_sale_prices[i] = manufacturer_sale_price;
        retail_prices[i] = retail_price;
    }

    // Sort the products by product_ID using Bubble Sort
    bubble_sort(product_IDs, manufacturer_sale_prices, retail_prices, no_of_inputs);

    int code;
    while (1) {  // Live tracking mode
        if (scanf("%d", &code) != 1) {
            break;  // Exit if no more input
        }

        if (code == -1 || code == -2) {
            // Display sales information
            display_sales_info(no_of_inputs, product_IDs, manufacturer_sale_prices, retail_prices, quantities_sold);
            if (code == -2) {
                break;  // Ends the program
            }
        }
        else {
            // Use Binary Search to check if the code is a valid product_ID
            int index = binary_search_first(product_IDs, no_of_inputs, code);
            if (index != -1) {
                // Valid product ID, increment the sale count
                quantities_sold[index]++;
            }
            else {
                // Invalid code
                printf("Invalid code\n");
            }
        }
    }

    return 0;
}

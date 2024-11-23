CMPUT 201 LAB, University Of Alberta :

Product Sales Tracker
Overview
This program is designed to efficiently track and analyze product sales statistics in real-time, aiding in profit optimization for a retail business. It uses sorting and binary search algorithms to manage product data and display sales statistics dynamically based on live inputs.

Features
Product Sorting: Sorts product information by product IDs using Bubble Sort.
Sales Tracking: Tracks quantities sold for each product in real-time.
Profit Analysis:
Calculates total profit for each sold product.
Determines the profit margin (Gross Margin) in percentage terms.
Displays total profit and average profit margin for all sold products.
Dynamic Sorting of Sold Products: Sorts sold products by descending profit margin using Bubble Sort.
Binary Search: Efficiently validates product IDs using Binary Search.
Interactive Input: Allows live input of product sales data.
Getting Started
Prerequisites
A C compiler (e.g., GCC).
Basic knowledge of compiling and running C programs in the terminal.
Compilation
Compile the program using the following command:

bash

gcc -o sales_tracker sales_tracker.c
Running the Program
Run the program with:


./sales_tracker
Input Format
First, input the number of products (n).
For each product, input three values:
Product ID (integer)
Manufacturer sale price (integer)
Retail price (integer)
After entering product data, input sales data or commands in real-time:
Enter a product ID to record its sale.
Use -1 to display sales information.
Use -2 to display sales information and terminate the program.
Output
Displays a table of sales information for sold products, including:
Product ID
Quantity sold
Total profit ($)
Gross Margin (%)
Displays total profit and average Gross Margin.



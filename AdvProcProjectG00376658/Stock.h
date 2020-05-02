#ifndef STOCK
#define STOCK

#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>

typedef struct product {
	int item_number;
	char item_name[30];
	char item_supplier[30];
	char item_supplier_contact[13];

	int reorder_threshold;
	int amount_unit;
	float cost_per_unit;
	char last_order_date[15];

	bool hazardous;
	
	/*
	0 - Undefined department
	1 - Office department
	2 - Maintenance department
	*/
	int department;
	/*
	0 - No Specified Month
	1 - Feb.
	2 - Aug.
	*/
	int reorder_month;
	/*
	0 - Managing Director
	1 - Financial Controller
	2 - Department Manager
	*/
	int authorise_purchase;
};

typedef struct stock_node {
	product data;

	struct stock_node* NEXT;
};

void addStock(product* stock);
void printAllProducts();
void printByNumber(int number);
void deleteProduct(int number);
void generateReport();
void persistenceStockSave();
void persistenceStockRestore();

#endif
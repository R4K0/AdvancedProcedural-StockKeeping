#include "Stock.h"

stock_node* head = NULL;
bool checkDuplicates(product* stock) {
	struct stock_node* temp = head;

	while (temp != NULL) {
		if (temp->data.item_number == stock->item_number) {
			return true;
		}
		temp = temp->NEXT;
	}

	return false;
}

void printProduct(product* prod) {
	printf(
	"\n== PRODUCT DETAILS ==\n"
	"Product Name: %s\n"
	"Number: %d\n\n"
	"Product Supplier: %s\n"
	"Supplier Contact: %s\n\n"
	"Reorder Treshold: %d\n"
	"Amount of Units: %d\n"
	"Price per Unit: %.2f\n\n"
	"Department: %s\n"
	"Reorder Month: %s\n"
	"Authoriser: %s\n", prod->item_name, prod->item_number, prod->item_supplier, prod->item_supplier_contact, prod->reorder_threshold,
		prod->amount_unit, prod->cost_per_unit,
		prod->department == 1 ? "Office" : prod->department == 2 ? "Maintenance" : "Undefined",
		prod->reorder_month == 1 ? "February" : prod->reorder_month == 2 ? "August" : "Not Specified",
		prod->authorise_purchase == 1 ? "Financial Director" : prod->authorise_purchase == 2 ? "Department Manager" : "Managing Director" );
}


void persistenceStockSave() {
	FILE* File = fopen("./stock.txt", "w");

	struct stock_node* temp = head;
	while (temp != NULL) {
		struct product* prod = &temp->data;
		fprintf(File, "%d %s %s %s %d %f %d %d %d %s %d %d\n", prod->item_number, prod->item_name,
			prod->item_supplier, prod->item_supplier_contact,
			prod->amount_unit, prod->cost_per_unit, prod->reorder_threshold,
			prod->hazardous ? 1 : 0, prod->department,
			prod->last_order_date, prod->reorder_month, prod->authorise_purchase);
		temp = temp->NEXT;
	}

	fclose(File);
}

void persistenceStockRestore() {
	FILE* File = fopen("./stock.txt", "r");
	if (File == NULL) { return; }

	int amount = 0;
	while (feof(File) == false) {
		struct product newProduct;
		int hazard = 0;
		fscanf(File, "%d %s %s %s %d %f %d %d %d %s %d %d ",
			&newProduct.item_number, newProduct.item_name,
			newProduct.item_supplier, newProduct.item_supplier_contact,
			&newProduct.amount_unit, &newProduct.cost_per_unit, &newProduct.reorder_threshold,
			&hazard, &newProduct.department,
			newProduct.last_order_date, &newProduct.reorder_month, &newProduct.authorise_purchase);

		newProduct.hazardous = hazard == 1 ? true : false;
		addStock(&newProduct);
		amount = amount + 1;
	}

	if (amount > 0) {
		printf("Restored %d products from a file.\n", amount);
		getch();
	}

	fclose(File);
}

void generateReport() {
	struct stock_node* temp = head;
	struct product* prod = NULL;
	FILE* File = fopen("./report.txt", "w");

	while (temp != NULL) {
		prod = &temp->data;
		fprintf(File,
			"\n== PRODUCT DETAILS ==\n"
			"Product Name: %s\n"
			"Number: %d\n\n"
			"Product Supplier: %s\n"
			"Supplier Contact: %s\n\n"
			"Reorder Treshold: %d\n"
			"Amount of Units: %d\n"
			"Price per Unit: %.2f\n\n"
			"Department: %s\n"
			"Reorder Month: %s\n"
			"Authoriser: %s\n", prod->item_name, prod->item_number, prod->item_supplier, prod->item_supplier_contact, prod->reorder_threshold,
			prod->amount_unit, prod->cost_per_unit,
			prod->department == 1 ? "Office" : prod->department == 2 ? "Maintenance" : "Undefined",
			prod->reorder_month == 1 ? "February" : prod->reorder_month == 2 ? "August" : "Not Specified",
			prod->authorise_purchase == 1 ? "Financial Director" : prod->authorise_purchase == 2 ? "Department Manager" : "Managing Director");

		temp = temp->NEXT;
	}
	fclose(File);
}

void printByNumber(int number) {
	struct stock_node* temp = head;

	while (temp != NULL) {
		if (temp->data.item_number == number) {
			printProduct(&temp->data);
			return;
		}

		temp = temp->NEXT;
	}

	printf("Sorry, couldn't find a product with such a number\n");
}

void printAllProducts() {
	struct stock_node* temp = head;

	while (temp != NULL) {
		printProduct(&temp->data);

		temp = temp->NEXT;
	}
}

product* getProductByNumber(int number) {
	struct stock_node* temp = head;

	while (temp != NULL) {
		if (temp->data.item_number == number) {
			return &temp->data;
		}

		temp = temp->NEXT;
	}
}

void deleteProduct(int number) {
	struct stock_node* temp = head;
	struct stock_node* prev = NULL;

	/*
	I think I got the general concept down, but I am not sure if it'll work...
	*/

	while ( temp != NULL ) {
		if (temp->data.item_number == number) {
			if (temp == head) {
				if (temp->NEXT != NULL) {
					head = temp->NEXT;
				}

				free(temp);
				break;
			}
			else if (prev != NULL && temp->NEXT != NULL) {
				prev->NEXT = temp->NEXT;
				free(temp);
				break;
			}
			else if (temp->NEXT == NULL) {
				free(temp);
				break;
			}
		}

		prev = temp;
		temp = temp->NEXT;
	}
}

void addStock(product* stock) {
	if (checkDuplicates(stock)) {
		printf("Cannot add that product, item number already taken.\nNew Number> ");
		scanf("%d", &stock->item_number);

		/*
		Recursion is magical!
		*/
		addStock(stock);
		return;
	}

	struct stock_node* temp = head;
	struct stock_node* newProduct = (struct stock_node*) malloc(sizeof(struct stock_node));
	newProduct->data = *stock;

	if (temp == NULL) {
		/*If there are no records then create the first node*/
		newProduct->NEXT = NULL;
		head = newProduct;
		return;
	}

	/*
	On the other hand, if there were records, then go to the end of the linked list and insert it there.
	*/
	while (temp->NEXT != NULL) {
		temp = temp->NEXT;
	}

	newProduct->NEXT = NULL;
	temp->NEXT = newProduct;
}
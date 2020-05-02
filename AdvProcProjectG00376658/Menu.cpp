#include "Menu.h";
#include "Login.h"
#include "Stock.h"


void menuLogin() {
	system("@cls||clear");
	if (isEmpty()) {
		menuAddUser();
		return;
	}
	char login[15]; char password[15];

	printf("Login> ");
	scanf("%s", login);
	printf("Pass> ");
	scanf("%s", password);

	bool success = attemptLogin(login, password);
	printf(success ? "Successful log-in! Welcome %s\n" : "Unsuccessful login! Try again\n", login);
	getch();
}

void menuAddUser() {
	system("@cls||clear");
	char login[15]; char password[15];

	if (isEmpty()) {
		printf("There are no accounts set-up, please set up an administrator account now!\n");
	}

	printf("New Login> ");
	scanf("%s", login);
	printf("New Pass> ");
	scanf("%s", password);

	addNewLogin(login, password);
}

void menuAddItem() {
	system("@cls||clear");
	struct product newProduct;

	printf("Enter the Product Number\n> ");
	scanf("%d", &newProduct.item_number);
	printf("Enter the Product Name\n> ");
	scanf("%s", newProduct.item_name);
	printf("Enter the Supplier Name\n> ");
	scanf("%s", newProduct.item_supplier);
	printf("Enter the Supplier Contact Number\n> ");
	scanf("%s", newProduct.item_supplier_contact);
	printf("Enter the Reorder Treshold Limit\n> ");
	scanf("%d", &newProduct.reorder_threshold);
	printf("Enter the Amount of Units\n> ");
	scanf("%d", &newProduct.amount_unit);
	printf("Enter the Price per Unit (1)\n> ");
	scanf("%f", &newProduct.cost_per_unit);
	printf("Enter the Last Order Date\n> ");
	scanf("%s", newProduct.last_order_date);

	char option[2];
	printf("Does the item need to be stored in a hazardous chemical store? (Y/N)\n> ");
	scanf("%s", option);
	newProduct.hazardous = (strcmp(option, "y") == 0 || strcmp(option, "Y") == 0) ? true : false;

	int department;
	printf("Which Department does the Item belong to?\n[1] Office\n[2] Maintenance\n> ");
	scanf("%d", &department);

	/*
		Must be in range 1-2 otherwise 0 (undefined)
	*/
	newProduct.department = (department == 1 || department == 2) ? department : 0;

	printf("Which month do items need to re-order?\n[0] No specified month\n[1] February\n[2] August\n> ");
	scanf("%d", &department); // Let's reuse the variable.
	newProduct.reorder_month = (department == 1 || department == 2) ? department : 0;

	printf("Which of the following people need to authorise the purchase??\n[0] Managing Director\n[1] Financial Director\n[2] Department Manager\n> ");
	scanf("%d", &department); // Let's reuse the variable.

	newProduct.authorise_purchase = (department == 1 || department == 2) ? department : 0;
	
	addStock(&newProduct);
}

void menuSearch() {
	system("@cls||clear");
	int number = 0;
	printf("Which product number do you want to display?\n> ");
	scanf("%d", &number);
	system("@cls||clear");

	printByNumber(number);
}

void menuDelete() {
	system("@cls||clear");
	int number = 0;
	printf("Which product number do you want to delete?\n> ");
	scanf("%d", &number);
	system("@cls||clear");

	deleteProduct(number);
}

void displayMenu() {
	system("@cls||clear");
	login* currentUser = getLoggedUser();
	printf("You're logged in as [%s] %s\n", currentUser->username, currentUser->admin ? "(ADMIN)" : "");
	printf("Select an option:\n");
	printf("[0] Log-Out\n");
	printf("[1] Add a New User (ADMIN ONLY)\n");
	printf("[2] Add a New Stock Item\n");
	printf("[3] Show all Items\n");
	printf("[4] Search by Number\n");
	printf("[5] Delete by Number\n");
	printf("[6] Generate Stock Report\n");
	printf("[7] Quit and Save (ADMIN ONLY)\n");

	printf("> ");
}

int parseOption(int option) {
	displayMenu();

	switch (option) {
	case 0:
		printf("Logged out...\n");
		getch();
		logOut();
		break;
	case 1:
		if (!getLoggedUser()->admin) {
			printf("Missing permissions...\n");
			getch();
			break;
		}
		menuAddUser();
		break;
	case 2:
		menuAddItem();
		break;
	case 3:
		printAllProducts();
		getch();
		break;
	case 4:
		menuSearch();
		getch();
		break;
	case 5:
		menuDelete();
		break;
	case 6:
		generateReport();
		break;
	case 7:
		if (!getLoggedUser()->admin) {
			printf("Missing permissions...\n");
			getch();
			break;
		}

		return 0;
	default:
		printf("Invalid option!\n");
		getch();
		break;
	}

}
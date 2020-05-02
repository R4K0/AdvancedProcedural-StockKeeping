#include <cstdio>
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include "Login.h"
#include "Menu.h"
#include "Stock.h"


void main() {
	bool shouldExit = false;
	int option;
	persistenceStockRestore();

	while (shouldExit != true) {
		if (!isLoggedIn()) {
			menuLogin();
			system("@cls||clear");
		} else {
			displayMenu();
			scanf("%d", &option);

			shouldExit = parseOption(option) == 0 ? true : false;
		}
	}

	persistenceStockSave();
}
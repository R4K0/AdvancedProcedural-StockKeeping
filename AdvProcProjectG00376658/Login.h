#ifndef LOGIN
#define LOGIN

#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <cstdio>

typedef struct login {
	char username[15];
	char password[15];

	bool admin;
};

typedef struct login_node {
	login data;

	struct login_node* NEXT;
};

bool attemptLogin(char *username, char *password);
void addNewLogin(char *username, char *password);
void logOut();
bool isLoggedIn();
bool isEmpty();
login* getLoggedUser();

#endif
#include "Login.h"
login_node* login_head = NULL;
login* loggedMember = NULL;

bool attemptLogin(char* username, char* password) {
	struct login_node* temp = login_head;

	while ( temp != NULL ) {
		if (strcmp(temp->data.password, password) == 0 && strcmp(temp->data.username, username) == 0) {
			loggedMember = &temp->data;
			return true;
		}

		temp = temp->NEXT;
	}

	return false;
}

bool isEmpty() {
	return login_head == NULL;
}

bool isLoggedIn() {
	return loggedMember != NULL;
}

login* getLoggedUser() {
	return loggedMember;
}

void logOut() {
	if (!isLoggedIn()) {
		return;
	}

	loggedMember = NULL;
}

void addNewLogin(char* username, char* password) {
	if (strlen(username) > 15 || strlen(password) > 15) {
		printf("Username or Password exceed 15 character limit!\n");
		getch();
		return;
	}

	struct login_node* temp = login_head;

	struct login_node* newLogin = (struct login_node*) malloc(sizeof(struct login_node));
	
	strcpy(newLogin->data.username, username);
	strcpy(newLogin->data.password, password);
	newLogin->data.admin = false;

	if (temp == NULL) {
		/*If there are no records then create the first node*/
		newLogin->data.admin = true; //Also set the first user as admin
		newLogin->NEXT = temp;
		login_head = newLogin;
		return;
	}

	/*
	On the other hand, if there were records, then go to the end of the linked list and insert it there.
	*/
	while (temp->NEXT != NULL) {
		temp = temp->NEXT;
	}

	newLogin->NEXT = NULL;
	temp->NEXT = newLogin;
}

void saveToFile(login_node* loginHead) {

} 
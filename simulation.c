#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book {
    int bookID;
    char title[50];
    char borrower[50];
    char dueDate[20];
    struct Book* next;
};

struct Book* head = NULL;

struct Book* createBook(int id, char title[], char borrower[], char due[]) {
    struct Book* newBook = (struct Book*)malloc(sizeof(struct Book));
    newBook->bookID = id;
    strcpy(newBook->title, title);
    strcpy(newBook->borrower, borrower);
    strcpy(newBook->dueDate, due);
    newBook->next = NULL;
    return newBook;
}

void addBook(int id, char title[], char borrower[], char due[]) {
    struct Book* newBook = createBook(id, title, borrower, due);

    if (head == NULL) {
        head = newBook;
        return;
    }

    struct Book* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newBook;
}

void displayBooks() {
    struct Book* temp = head;

    if (temp == NULL) {
        printf("\nNo borrowed books.\n");
        return;
    }

    printf("\n--- Borrowed Books List ---\n");
    while (temp != NULL) {
        printf("Book ID   : %d\n", temp->bookID);
        printf("Title     : %s\n", temp->title);
        printf("Borrower  : %s\n", temp->borrower);   
        printf("Due Date  : %s\n\n", temp->dueDate);  
        temp = temp->next;
    }
}

void searchBook(int id) {
    struct Book* temp = head;

    while (temp != NULL) {
        if (temp->bookID == id) {
            printf("\nBook Found!\n");
            printf("Book ID   : %d\n", temp->bookID);
            printf("Title     : %s\n", temp->title);
            printf("Borrower  : %s\n", temp->borrower);    
            printf("Due Date  : %s\n", temp->dueDate);     
            return;
        }
        temp = temp->next;
    }
    printf("\nBook not found.\n");
}

void returnBook(int id) {
    struct Book *temp = head, *prev = NULL;

    if (temp != NULL && temp->bookID == id) {
        head = temp->next;
        free(temp);
        printf("\nBook returned successfully.\n");
        return;
    }

    while (temp != NULL && temp->bookID != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("\nBook not found.\n");
        return;
    }

    prev->next = temp->next;
    free(temp);
    printf("\nBook returned successfully.\n");
}

int main() {
    int choice, id;
    char title[50], borrower[50], due[20];

    while (1) {
        printf("\n--- Library Book Borrowing System ---\n");
        printf("1. Borrow Book\n");
        printf("2. Display Borrowed Books\n");
        printf("3. Search Borrowed Book\n");
        printf("4. Return Book\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Book ID: ");
                scanf("%d", &id);
                printf("Enter Title: ");
                scanf("%s", title);
                printf("Enter Borrower Name: ");
                scanf("%s", borrower);
                printf("Enter Due Date (DD-MM-YYYY): ");
                scanf("%s", due);

                addBook(id, title, borrower, due);
                break;

            case 2:
                displayBooks();
                break;

            case 3:
                printf("Enter Book ID to search: ");
                scanf("%d", &id);
                searchBook(id);
                break;

            case 4:
                printf("Enter Book ID to return: ");
                scanf("%d", &id);
                returnBook(id);
                break;

            case 5:
                printf("\nExiting program...\n");
                exit(0);

            default:
                printf("Invalid choice.\n");
        }
    }
}


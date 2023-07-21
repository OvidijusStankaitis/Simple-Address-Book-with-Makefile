#include <stdio.h>
#include <stdbool.h>

#include <string.h>
#include <signal.h>
#include <setjmp.h>

#include "linkedList.h"

bool ctrlc = false;
jmp_buf jump_buffer;

void clearScreen();
void sig_handler(int signum);
void getContactInfo(char name[50], char surname[50], char email[50], char number[50]);
int inputValidation();

int main()
{
    bool running = true;
    Node *list = initListFromFile();

    signal(SIGINT, sig_handler);

    while (running)
    {
        if (sigsetjmp(jump_buffer, 1) == 1)
        {
            deleteList(&list);
            running = false;
            break;
        }

        clearScreen();
        printf("Adressbook\n\n");
        printf("1. Insert contact\n");
        printf("2. Insert contact at\n");
        printf("3. Delete contact at\n");
        printf("4. Delete list\n");
        printf("5. Print list\n");
        printf("6. Find contact at\n");
        printf("7. Find contact by keyword\n");
        printf("8. Exit\n\n");

        printf("Choose an option: ");
        int option = inputValidation();

        printf("\n");

        switch (option)
        {
            case 1:
            {
                char name[50], surname[50], email[50], number[50];
                getContactInfo(name, surname, email, number);
                insertNode(&list, name, surname, email, number);
                printf("\nInserted. Press enter to continue...");
                getchar();
                getchar();
                break;
            }
            case 2:
            {
                char name[50], surname[50], email[50], number[50];
                printf("Index: ");
                int index = inputValidation();
                getContactInfo(name, surname, email, number);
                insertNodeAt(&list, name, surname, email, number, index);
                printf("\nInserted. Press enter to continue...");
                getchar();
                getchar();
                break;
            }
            case 3:
            {
                printf("Index: ");
                int index = inputValidation();
                deleteNodeAt(&list, index);
                printf("\nDeleted. Press enter to continue...");
                getchar();
                break;
            }
            case 4:
            {
                deleteList(&list);
                printf("Deleted. Press enter to continue...");
                getchar();
                break;
            }
            case 5:
            {
                printList(&list);
                printf("\nPress enter to continue...");
                getchar();
                break;
            }
            case 6:
            {
                printf("Index: ");
                int index = inputValidation();
                printf("\n");
                findNodeAt(list, index);
                printf("\nPress enter to continue...");
                getchar();
                break;
            }
            case 7:
            {
                char keyword[50];
                printf("Keyword: ");
                scanf("%49s", keyword);
                printf("\n");
                findNode(list, keyword);
                printf("\nPress enter to continue...");
                getchar();
                getchar();
                break;
            }
            case 8:
            {
                deleteList(&list);
                running = false;
                break;
            }
            default:
            {
                break;
            }
        }
    }
    clearScreen();
    return 0;
}

void clearScreen()
{
    printf("\033[H\033[J");
}

void sig_handler(int signum)
{
    (void)signum;
    ctrlc = true;
    siglongjmp(jump_buffer, 1);
}

void getContactInfo(char name[50], char surname[50], char email[50], char number[50])
{
    printf("Name: ");
    scanf("%49s", name);
    printf("Surname: ");
    scanf("%49s", surname);
    printf("Email: ");
    scanf("%49s", email);
    printf("Number: ");
    scanf("%49s", number);
}

int inputValidation()
{
    int option = 0;
    while (scanf("%d", &option) != 1 || getchar() != '\n')
    {
        printf("Invalid input, please enter an integer: ");
        while (getchar() != '\n')
        {
            ;
        }
    }
    return option;
}

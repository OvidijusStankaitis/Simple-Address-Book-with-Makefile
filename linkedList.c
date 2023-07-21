#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

#include "linkedList.h"

#define FILENAME "addresses.csv"
#define DELIMITER ","

struct Node
{
    char name[50];
    char surname[50];
    char email[50];
    char number[50];
    struct Node *next;
};

typedef struct Node Node;

void removeChar(char *str, char ch)
{
    int len = strlen(str);
    int index = 0;

    for (int i = 0; i < len; i++)
    {
        if (str[i] != ch)
        {
            str[index++] = str[i];
        }
    }

    str[index] = '\0';
}

Node *initList()
{
    Node *node = (Node *)malloc(sizeof(Node));
    node->next = NULL;
    return node;
}

Node *initListFromFile()
{
    const char *homedir;
    if ((homedir = getenv("HOME")) == NULL)
    {
        homedir = getpwuid(getuid())->pw_dir;
    }

    char path[100];
    strcpy(path, homedir);
    strcat(path, "/");
    strcat(path, FILENAME);

    FILE *addresses = fopen(path, "r");

    if (addresses == NULL)
    {
        return NULL;
    }

    Node *head = NULL;
    Node *tail = NULL;
    char line[200];

    while (fgets(line, sizeof(line), addresses))
    {
        Node *newNode = (Node *)malloc(sizeof(Node));
        newNode->next = NULL;

        removeChar(line, '\n');

        char *name = strtok(line, DELIMITER);
        char *surname = strtok(NULL, DELIMITER);
        char *email = strtok(NULL, DELIMITER);
        char *number = strtok(NULL, DELIMITER);

        initializeNode(newNode, name, surname, email, number);

        if (head == NULL)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            tail->next = newNode;
            tail = newNode;
        }
    }

    fclose(addresses);
    return head;
}

void initializeNode(Node *node, const char *name, const char *surname, const char *email, const char *number)
{
    strncpy(node->name, name, sizeof(node->name) - 1);
    strncpy(node->surname, surname, sizeof(node->surname) - 1);
    strncpy(node->email, email, sizeof(node->email) - 1);
    strncpy(node->number, number, sizeof(node->number) - 1);

    node->name[sizeof(node->name) - 1] = '\0';
    node->surname[sizeof(node->surname) - 1] = '\0';
    node->email[sizeof(node->email) - 1] = '\0';
    node->number[sizeof(node->number) - 1] = '\0';
}

int printList(Node **head)
{
    if (*head == NULL)
    {
        return 1;
    }
    else
    {
        printf("%s %s %s %s\n", (*head)->name, (*head)->surname, (*head)->email, (*head)->number);
        if ((*head)->next == NULL)
        {
            return 0;
        }
        return printList(&((*head)->next));
    }
}

int deleteList(Node **head)
{
    if (*head == NULL)
    {
        return 1;
    }

    Node *current = *head;
    *head = current->next;

    free(current);

    if (*head != NULL)
    {
        return deleteList(head);    
    }
    else
    {
        *head = NULL;
        return 0;
    }
}

int insertNode(Node **head, const char *name, const char *surname, const char *email, const char *number)
{
    Node *newNode = (Node *)malloc(sizeof(Node));

    if (newNode == NULL)
    {
        return 1;
    }

    initializeNode(newNode, name, surname, email, number);

    newNode->next = NULL;

    if (*head == NULL)
    {
        *head = newNode;
    }
    else
    {
        Node *tail = *head;
        while (tail->next != NULL)
        {
            tail = tail->next;
        }
        tail->next = newNode;
    }

    return 0;
}

int insertNodeAt(Node **head, const char *name, const char *surname, const char *email, const char *number, int index)
{
    if (index == 1 || *head == NULL)
    {
        insertNode(head, name, surname, email, number);
        return 0;
    }

    if (index <= 0 || index > linkedListLength(*head))
    {
        return 1;
    }

    Node *newNode = (Node *)malloc(sizeof(Node));
    initializeNode(newNode, name, surname, email, number);

    Node *current = *head;
    int currentPosition = 1;

    while (currentPosition < index - 1)
    {
        current = current->next;
        currentPosition++;
    }

    newNode->next = current->next;
    current->next = newNode;

    return 0;
}

int deleteNodeAt(Node **head, int index)
{
    if (*head == NULL || index <= 0 || index > linkedListLength(*head))
    {
        return 1;
    }

    if (index == 1)
    {
        Node *current = *head;
        *head = current->next;

        free(current);
        return 0;
    }

    Node *current = *head;
    Node *previous = NULL;
    int currentPosition = 1;

    while (current != NULL && currentPosition < index)
    {
        previous = current;
        current = current->next;
        currentPosition++;
    }

    previous->next = current->next;
    free(current);

    return 0;
}

int findNodeAt(Node *head, int index)
{
    if (head == NULL || index <= 0 || index > linkedListLength(head))
    {
        return 1;
    }

    Node *current = head;
    int currentPosition = 1;

    while (current != NULL && currentPosition < index)
    {
        current = current->next;
        currentPosition++;
    }
    printf("Name: %s\n", current->name);
    printf("Surname: %s\n", current->surname);
    printf("Email: %s\n", current->email);
    printf("Number: %s\n", current->number);

    return 0;
}

int findNode(Node *head, const char *keyword)
{
    if (head == NULL)
    {
        return 1;
    }

    Node *current = head;
    bool found = false;

    while (current != NULL)
    {
        if (strstr(current->name, keyword) != NULL ||
            strstr(current->surname, keyword) != NULL ||
            strstr(current->email, keyword) != NULL ||
            strstr(current->number, keyword) != NULL)
        {
            printf("%s %s %s %s\n", current->name, current->surname, current->email, current->number);
            found = true;
        }
        current = current->next;
    }

    if (!found)
    {
        return 1;
    }

    return 0;
}

int linkedListLength(const Node *head)
{
    int length = 0;
    const Node *current = head;

    while (current != NULL)
    {
        length++;
        current = current->next;
    }

    return length;
}
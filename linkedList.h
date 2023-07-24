#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct Node Node;

Node *initList();
Node *initListFromFile();
void initializeNode(Node *node, const char *name, const char *surname, const char *email, const char *number);
int printList(Node **head);
int deleteList(Node **head);
int insertNode(Node **head, int *indexp);
int deleteNodeAt(Node **head, int index);
int findNodeAt(Node *head, int index);
int findNode(Node *head, const char *keyword);
int linkedListLength(const Node *head);
void getContactInfo(char name[50], char surname[50], char email[50], char number[50]);

#endif
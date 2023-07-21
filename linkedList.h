#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct Node Node;

Node *initList();
Node *initListFromFile();
void initializeNode(Node *node, const char *name, const char *surname, const char *email, const char *number);
int printList(Node **head);
int deleteList(Node **head);
int insertNode(Node **head, const char *name, const char *surname, const char *email, const char *number);
int insertNodeAt(Node **head, const char *name, const char *surname, const char *email, const char *number, int index);
int deleteNodeAt(Node **head, int index);
int findNodeAt(Node *head, int index);
int findNode(Node *head, const char *keyword);
int linkedListLength(const Node *head);

#endif
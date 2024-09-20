#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct Node {
    int value;
    struct Node* next;
} Node;

typedef struct LinkedList {
    Node* head;
    Node* current;
    Node* tail;
} LinkedList;

LinkedList createLinkedList();
void destroyLinkedList(LinkedList* list);
void addNode(LinkedList* list, Node* newNode);
void addNodeByValue(LinkedList* list, int value);
Node* getNextNode(LinkedList* list);
void shuffleList(LinkedList* list);
void printList(LinkedList* list);

#endif
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct Node {
    int index;
    struct Node* next;
} Node;

typedef struct LinkedList {
    Node* head;
    Node* current;
    Node* tail;
} LinkedList;

#endif
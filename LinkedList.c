#include <stdlib.h>
#include <stdio.h>
#include "LinkedList.h"

LinkedList createLinkedList() {
    LinkedList newList = {NULL, NULL, NULL};
    return newList;
}

void destroyLinkedList(LinkedList* list) {
    Node* temp = list->head->next;
    while(list->head != NULL) {
        free(list->head);
        list->head = temp;
        temp = list->head->next;
    }

    list->tail = NULL;
    list->current = NULL;
}

void addNode(LinkedList* list, Node* newNode) {
    if(list->head == NULL)
        list->head = newNode;

    if(list->tail == NULL) {
        list->tail = list->head;
    }
    else {
        list->tail->next = newNode;
        list->tail = list->tail->next;
    }

    if(list->current == NULL)
        list->current = list->tail;
}

void addNodeByValue(LinkedList* list, int value) {
    Node* newNode = malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;
    addNode(list, newNode);
}


Node* getNextNode(LinkedList* list) {
    if(list->current == NULL)
        return NULL;

    Node* current = list->current;
    list->current = list->current->next;

    return current; 
}
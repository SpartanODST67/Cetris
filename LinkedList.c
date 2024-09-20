#include <stdlib.h>
#include <stdio.h>
#include "LinkedList.h"

LinkedList createLinkedList() {
    LinkedList newList = {NULL, NULL, NULL};
    return newList;
}

void destroyLinkedList(LinkedList* list) {
    while(list->head != NULL) {
        Node* temp = list->head;
        list->head = list->head->next;
        free(temp);
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

void shuffleList(LinkedList* list) {
    Node* current = list->head->next;
    list->head->next = current->next;
    current->next = list->head;
    list->head = current;

    for(int i = 0; i < 10; i++) {
        for(; current->next->next != NULL; current = current->next) {
            if(rand() % 2 == 0) {
                Node* n1 = current->next;
                Node* n2 = current->next->next;
                n1->next = n2->next;
                n2->next = n1;
                current->next = n2;
            }
        }
    }
}

void printList(LinkedList* list) {
    Node* current = list->head;
    while(current != NULL) {
        printf("%d ", current->value);
        current = current->next;
    }
    printf("\n");
}
#include<stdio.h>
#include<stdlib.h>
#include "assignment_2.h"

typedef struct node {
    int data; //to store the number
    struct node * next; //link to next node
}
node;

static int log_2(int n) { //function to finde log
    int i = 1;
    int log_value = 0;
    while (i < n) {
        i *= 2;
        log_value++;
    }
    return log_value;
}

static void printlist(node * nod) { //function to print the list
    node * temp = nod;
    while (temp != NULL) {
        printf("%d ", temp -> data);
        temp = temp -> next;
    }
}

static node * createnode(int data) { //function to create a node
    node * temp = (node * ) malloc(sizeof(node));
    temp -> next = NULL;
    temp -> data = data;
    return temp;
}

void find_second_greatest(int * arr, int n) {
    int size = log_2(n) + 1;
    node * array[size]; //this is the array which can store pointers to the list
    for (int i = 0; i < size; i++) { //initialization of array
        array[i] = NULL;
    }
    int count = 0;
    int a;
    int b;
    while (count != n) { //to go throught the arr
        if (count + 1 == n) { //if only one element is left
            a = arr[count++];
            node * temp = createnode(a);
            int i = 0;
            array[i] = temp; //put the list into the first position of the array
            while (array[i + 1] != NULL) { //this is used to go througth the array
                printlist(array[i + 1]);
                printf("x ");
                printlist(array[i]);
                printf("= ");
                if (array[i + 1] -> data > array[i] -> data) {
                    array[i] -> next = array[i + 1] -> next;
                    array[i + 1] -> next = array[i];
                } else {
                    array[i + 1] -> next = array[i] -> next;
                    array[i] -> next = array[i + 1];
                    array[i + 1] = array[i];
                }
                printlist(array[i + 1]);
                printf("\n");
                array[i] = NULL;
                i++;
            }
            array[i + 1] = array[i]; //moving the array ahead
            array[i] = NULL;
        } else {
            a = arr[count++];
            b = arr[count++];
            node * min;
            node * max;
            if (a > b) {
                min = createnode(b); //creating new list
                max = createnode(a);
                printlist(max);
                printf("x ");
                printlist(min);
            } else {
                min = createnode(a); //creating new list
                max = createnode(b);
                printlist(min);
                printf("x ");
                printlist(max);

            }
            printf("= ");
            min -> next = max -> next;
            max -> next = min;
            printlist(max);
            printf("\n");
            int i = 0;
            array[i] = max; //put the list into the first position of the array
            while (array[i + 1] != NULL) { //this is used to go througth the array
                printlist(array[i + 1]);
                printf("x ");
                printlist(array[i]);
                printf("= ");
                if (array[i + 1] -> data > array[i] -> data) {
                    array[i] -> next = array[i + 1] -> next;
                    array[i + 1] -> next = array[i];
                } else {
                    array[i + 1] -> next = array[i] -> next;
                    array[i] -> next = array[i + 1];
                    array[i + 1] = array[i];
                }
                printlist(array[i + 1]);
                printf("\n");
                array[i] = NULL;
                i++;
            }
            array[i + 1] = array[i]; //moving the array ahead
            array[i] = NULL;
        }
    }
    int i = 0;
    node * temp = NULL;
    while (i < size) { //after reading all the elements of the array going through the array of pointers
        if (temp == NULL) { //if temp is not yet initialized
            temp = array[i];
            array[i] = NULL;
        } else if (array[i] != NULL) { //if the array is not empty
            printlist(array[i]);
            printf("x ");
            printlist(temp);
            printf("= ");
            if (array[i] -> data > temp -> data) {
                temp -> next = array[i] -> next;
                array[i] -> next = temp;
                temp = array[i];
            } else {
                array[i] -> next = temp -> next;
                temp -> next = array[i];
            }
            printlist(temp);
            printf("\n");
            array[i] = NULL;
        }
        i++;
    }
    int max = -1;
    temp = temp -> next;
    while (temp != NULL) { //to get the second biggest element
        if (max < temp -> data)
            max = temp -> data;
        temp = temp -> next;
    }
    printf("\n%d", max);
}
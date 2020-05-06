#include<stdio.h>

#include<stdlib.h>

struct jug_state {
    int init_capacity; //Total water in the initial state
    int A_capacity; //Total capacity of jug A
    int B_capacity; //Total capacity of jug B
    int C_capacity; //Total capacity of jug C
    int A_current; //Water in that state in jug A
    int B_current; //Water in that state in jug B
    int C_current; //Water in that state in jug C
    int function_index; //The current index of fuction to the pointer
};

typedef struct jug_state jug_state;

jug_state * init_state(int A_capacity, int B_capacity, int C_capacity, int A_current, int B_current, int C_current, int init_capacity);

void display_state(const jug_state * ptr_state);

int moveAB(const jug_state * src, jug_state * dest);

int moveAC(const jug_state * src, jug_state * dest);

int moveBA(const jug_state * src, jug_state * dest);

int moveBC(const jug_state * src, jug_state * dest);

int moveCA(const jug_state * src, jug_state * dest);

int moveCB(const jug_state * src, jug_state * dest);

int is_valid(const jug_state * );

int are_same(const jug_state * lhs,
    const jug_state * rhs);

struct node {
    jug_state jug_state; //The jug's state in the node
    struct node * next; //Link to next state
    struct node * prev; //Link to previous state
};

typedef struct node state;

struct list {
    state * head; //Link to head of the list
    state * tail; //Link to tail of the list
};

typedef struct list list_of_states;

void init_list(list_of_states * ptr_list);

void disp_list(list_of_states * ptr_list);

void add_end(list_of_states * ptr_list,
    const jug_state * ptr_state);

void remove_end(list_of_states * ptr_list);

int is_repeated(const list_of_states * ptr_list,
    const jug_state * ptr_state);

int get_solutions(list_of_states * list_of_states,
    const jug_state * start, jug_state * end, int( * change_in_states[])(const jug_state * src, jug_state * dest), int number_of_functions);

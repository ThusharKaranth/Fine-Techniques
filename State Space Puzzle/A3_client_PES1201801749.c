#include<stdio.h>

#include<stdlib.h>

#include"A3_header_PES1201801749.h"

int main() {
    int number_of_solutions = 0;
    int number_of_functions = 6;
    jug_state start;
    jug_state end;
    list_of_states list_of_states;
    int( * change_in_states[])(const jug_state * src, jug_state * dest) = { //Initializing an array of pointer to functions
        moveAB,
        moveAC,
        moveBA,
        moveBC,
        moveCA,
        moveCB
    };
    int A_capacity, B_capacity, C_capacity, A_init, B_init, C_init, A_fin, B_fin, C_fin;
    scanf("%d %d %d", & A_capacity, & B_capacity, & C_capacity);
    scanf("%d %d %d", & A_init, & B_init, & C_init);
    scanf("%d %d %d", & A_fin, & B_fin, & C_fin);
    start = * init_state(A_capacity, B_capacity, C_capacity, A_init, B_init, C_init, A_init + B_init + C_init); //Initializing start state
    end = * init_state(A_capacity, B_capacity, C_capacity, A_fin, B_fin, C_fin, A_init + B_init + C_init); //Initializing end state
    init_list( & list_of_states); //Initializing list
    number_of_solutions = get_solutions( & list_of_states, & start, & end, change_in_states, number_of_functions); //Calling function which uses backtracking
    printf("%d\n", number_of_solutions);
    return 0;
}
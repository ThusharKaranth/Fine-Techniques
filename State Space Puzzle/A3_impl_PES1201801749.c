#include<stdio.h>

#include<stdlib.h>

#include"A3_header_PES1201801749.h"

jug_state * init_state(int A_capacity, int B_capacity, int C_capacity, int A_current, int B_current, int C_current, int init_capacity) { //intialize the states
    jug_state * ptr_state = (jug_state * ) malloc(sizeof(jug_state));
    ptr_state->init_capacity = init_capacity;
    ptr_state->A_capacity = A_capacity;
    ptr_state->B_capacity = B_capacity;
    ptr_state->C_capacity = C_capacity;
    ptr_state->A_current = A_current;
    ptr_state->B_current = B_current;
    ptr_state->C_current = C_current;
    ptr_state->function_index = 0;
    return ptr_state;
}

void display_state(const jug_state * ptr_state) { //print current state 
    printf("%d %d %d\n", ptr_state->A_current, ptr_state->B_current, ptr_state->C_current);
}

int moveAB(const jug_state * src, jug_state * dest) {
    if (src->A_current + src->B_current - src->B_capacity < 0) { //A has less than required
        dest->A_current = 0;
        dest->B_current = src->A_current + src->B_current;
    } 
	else { // A has more than required
        dest->A_current = src->A_current + src->B_current - src->B_capacity;
        dest->B_current = src->B_capacity;
    }
    dest->init_capacity = src->init_capacity;
    dest->A_capacity = src->A_capacity;
    dest->B_capacity = src->B_capacity;
    dest->C_capacity = src->C_capacity;
    dest->C_current = src->C_current;
    dest->function_index = 0;
    if (is_valid(dest))
        if (!are_same(src, dest))
            return 1;
        else
            return 0;
}

int moveAC(const jug_state * src, jug_state * dest) {
    if (src->A_current + src->C_current - src->C_capacity < 0) { //A has less than required
        dest->A_current = 0;
        dest->C_current = src->A_current + src->C_current;
    } 
	else { // A has more than required
        dest->A_current = src->A_current + src->C_current - src->C_capacity;
        dest->C_current = src->C_capacity;
    }
    dest->init_capacity = src->init_capacity;
    dest->A_capacity = src->A_capacity;
    dest->B_capacity = src->B_capacity;
    dest->C_capacity = src->C_capacity;
    dest->B_current = src->B_current;
    dest->function_index = 0;
    if (is_valid(dest))
        if (!are_same(src, dest))
            return 1;
        else
            return 0;
}

int moveBA(const jug_state * src, jug_state * dest) {
    if (src->B_current + src->A_current - src->A_capacity < 0) { //B has less than required
        dest->B_current = 0;
        dest->A_current = src->B_current + src->A_current;
    } 
	else { // B has more than required
        dest->B_current = src->B_current + src->A_current - src->A_capacity;
        dest->A_current = src->A_capacity;
    }
    dest->init_capacity = src->init_capacity;
    dest->A_capacity = src->A_capacity;
    dest->B_capacity = src->B_capacity;
    dest->C_capacity = src->C_capacity;
    dest->C_current = src->C_current;
    dest->function_index = 0;
    if (is_valid(dest))
        if (!are_same(src, dest))
            return 1;
        else
            return 0;
}

int moveBC(const jug_state * src, jug_state * dest) {
    if (src->B_current + src->C_current - src->C_capacity < 0) { //B has less than required
        dest->B_current = 0;
        dest->C_current = src->B_current + src->C_current;
    } 
	else { // B has more than required
        dest->B_current = src->B_current + src->C_current - src->C_capacity;
        dest->C_current = src->C_capacity;
    }
    dest->init_capacity = src->init_capacity;
    dest->A_capacity = src->A_capacity;
    dest->B_capacity = src->B_capacity;
    dest->C_capacity = src->C_capacity;
    dest->A_current = src->A_current;
    dest->function_index = 0;
    if (is_valid(dest))
        if (!are_same(src, dest))
            return 1;
        else
            return 0;
}

int moveCA(const jug_state * src, jug_state * dest) {
    if (src->C_current + src->A_current - src->A_capacity < 0) { //C has less than required
        dest->C_current = 0;
        dest->A_current = src->C_current + src->A_current;
    } 
	else { // C has more than required
        dest->C_current = src->C_current + src->A_current - src->A_capacity;
        dest->A_current = src->A_capacity;
    }
    dest->init_capacity = src->init_capacity;
    dest->A_capacity = src->A_capacity;
    dest->B_capacity = src->B_capacity;
    dest->C_capacity = src->C_capacity;
    dest->B_current = src->B_current;
    dest->function_index = 0;
    if (is_valid(dest))
        if (!are_same(src, dest))
            return 1;
        else
            return 0;
}

int moveCB(const jug_state * src, jug_state * dest) {
    if (src->C_current + src->B_current - src->B_capacity < 0) { //C has less than required
        dest->C_current = 0;
        dest->B_current = src->C_current + src->B_current;
    } 
	else { //C has more than required
        dest->C_current = src->C_current + src->B_current - src->B_capacity;
        dest->B_current = src->B_capacity;
    }
    dest->init_capacity = src->init_capacity;
    dest->A_capacity = src->A_capacity;
    dest->B_capacity = src->B_capacity;
    dest->C_capacity = src->C_capacity;
    dest->A_current = src->A_current;
    dest->function_index = 0;
    if (is_valid(dest))
        if (!are_same(src, dest))
            return 1;
        else
            return 0;
}

int is_valid(const jug_state * ptr_state) { //Check if the states are valid
    return (((ptr_state->A_current <= ptr_state->A_capacity) &&
            (ptr_state->A_current >= 0)) &&
        ((ptr_state->B_current <= ptr_state->B_capacity) &&
            (ptr_state->B_current >= 0)) &&
        ((ptr_state->C_current <= ptr_state->C_capacity) &&
            (ptr_state->C_current >= 0)) &&
        ((ptr_state->A_current + ptr_state->B_current + ptr_state->C_current == ptr_state->init_capacity))
    );
}

int are_same(const jug_state * lhs,
    const jug_state * rhs) { //Check if the states are same
    return (lhs->A_capacity == rhs->A_capacity &&
        lhs->A_current == rhs->A_current &&
        lhs->B_capacity == rhs->B_capacity &&
        lhs->B_current == rhs->B_current &&
        lhs->C_capacity == rhs->C_capacity &&
        lhs->C_current == rhs->C_current &&
        lhs->init_capacity == rhs->init_capacity
    );
}

void init_list(list_of_states * ptr_list) {
    ptr_list->head = NULL;
    ptr_list->tail = NULL;
}

void disp_list(list_of_states * ptr_list) {
    state * temp = ptr_list->head;
    while (temp) {
        display_state( & temp->jug_state);
        temp = temp->next;
    }
}

void add_end(list_of_states * ptr_list,
    const jug_state * ptr_state) {
    state * temp = (state * ) malloc(sizeof(state)); // Create new node
    temp->jug_state = * ptr_state;
    temp->next = temp->prev = NULL;
    if (ptr_list->tail == NULL) // List is empty
        ptr_list->head = ptr_list->tail = temp;
    else { // Add at end
        temp->prev = ptr_list->tail;
        ptr_list->tail->next = temp;
        ptr_list->tail = temp;
    }
}

void remove_end(list_of_states * ptr_list) { // Assumes list is not empty
    state * temp = ptr_list->tail;
    ptr_list->tail = ptr_list->tail->prev;
    if (ptr_list->tail == NULL) // Single node
        ptr_list->head = NULL;
    else // More than one node
        ptr_list->tail->next = NULL;
    free(temp);
}

int is_repeated(const list_of_states * ptr_list,
    const jug_state * ptr_state) { // Test if  ptr_state is there in ptr_list
    state * temp = ptr_list->head;
    int flag = 0;
    while (temp != NULL && !flag) {
        flag = are_same( & temp->jug_state, ptr_state);
        temp = temp->next;
    }
    return flag;
}

int get_solutions(list_of_states * list_of_states,
    const jug_state * start, jug_state * end, int( * change_in_states[])(const jug_state * src, jug_state * dest), int number_of_functions) {
    if (!is_valid(start)) // Invalid start state
        return 0;
    else if (!is_valid(end)) //Invalid end state
        return 0;
    else {
        int number_of_solutions = 0;
        int function_index = 0;
        jug_state temp_state;
        add_end(list_of_states, start); // Start state is added to the list
        while (list_of_states->tail != NULL) { // List is not empty
            function_index = list_of_states->tail->jug_state.function_index; // get next index
            change_in_states[function_index]( & list_of_states->tail->jug_state, & temp_state); // move to next state
            if (is_valid( & temp_state) && !is_repeated(list_of_states, & temp_state)) { // if state is valid and not repeated then append
                add_end(list_of_states, & temp_state);
                if (are_same( & temp_state, end)) { // Solution is obtained , display it and move forward
                    disp_list(list_of_states);
                    printf("\n");
                    ++number_of_solutions;
                }
            } 
			else {
                // increase index until function_index remains at 6
                // if index is more than number_of_function, then set it to zero
                function_index = (list_of_states->tail->jug_state.function_index + 1) % number_of_functions;
                while (list_of_states->tail != NULL && ++(list_of_states->tail->jug_state.function_index) == number_of_functions) // Backtrack to next combination
                    remove_end(list_of_states);
            }
        }

        return number_of_solutions;
    }
}

/*
Algorithm Backtrack ( list, start, end, transitions )
	assert start, end are valid
	append start to list
	while list is not empty do
		get index from tail state in list
		perform transition
		if transition is valid and not repeated in list then
			append in list
			if intermediate_state is final then
				display solution path (list)
				increase number of solutions
		else
			get next index as (tail->index + 1 mod number of functions) to keep it within the array
			while list is not empty and next function is outside transition array
				remove from end // to backtrack to previous combination	
	return number of solutions
*/
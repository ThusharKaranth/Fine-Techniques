 #include<stdio.h>
#include<stdlib.h>
#include"assignment_1.h"

//This is book which keeps record of each block
typedef struct block_info{
    int flag;//flag is 0 if the block is free , 1 if it is allocated
    int next_index;//holds the value of the next block's index , -1 if no blocks are preceding it
    int size_of_block;//has the size of the current block
}block_info;

char *p = NULL;
#define BLOCK_SIZE sizeof(block_info)
static int SIZE = 0;

void allocate(int n){
    if(p != NULL){//If the p is already initialized
        free(p);
        p = NULL;
    }
    p = (char*)malloc(sizeof(char)*n);
    if(p != NULL){
        block_info* temp = (block_info*)p;//Initial book which has the whole block in it as free
        temp->flag = 0;
        temp->size_of_block = n - BLOCK_SIZE;
        temp->next_index = -1;
        SIZE = n;
    }
	else{
		SIZE = 0;
	}
}

void* mymalloc(int size){
	void* ra = NULL;
    if(SIZE == 0)
        return NULL;
    block_info* temp;
    int i=0,j,n;
    while(i <= SIZE){//To iterate through p
        temp = (block_info*)(&p[i]);
        i += BLOCK_SIZE;
        if(temp->flag == 1 || temp->size_of_block < size){//If the block is already allocated or the size is less than expected
            i += temp->size_of_block;
        }
        else{
            ra = (void*)(&p[i]);
			i += size;
            if(temp->size_of_block > size + BLOCK_SIZE){//If the block size is more than expected
				block_info* temp1 = (block_info*)(&p[i]);//Creating a new book
				temp1->flag = 0;
				temp1->size_of_block = temp->size_of_block - size - BLOCK_SIZE;
				temp1->next_index = temp->next_index;
				temp->next_index = i;
				temp->size_of_block = size;
				temp->flag = 1;
				return ra;
			}
			else{//If the block size is same as size
				temp->flag = 1;
				return ra;
			}   
        }
    }
	return ra;
}

void myfree(void *b){
	if(SIZE == 0 || b == NULL)//If b is NULL or the SIZE is 0
		return;
	block_info *pres = NULL; 
	block_info *prev;
	block_info *next;
	int i = 0, j = 0;
	while(i < SIZE){//Iterating through p
		prev = pres;
		pres = (block_info*)(&p[i]);
		i += BLOCK_SIZE;
		if(b == (void*)(&p[i])){//If b points to the block
			if(pres->flag == 0){//If it is already free
			    return;
			}
			else if(prev != NULL && prev->flag == 0){//If the previous block is present and the previous block is free
			    if(pres->next_index != -1){//If the next block is there
			        j = i;
			        j += pres->size_of_block;
			        next = (block_info*)(&p[j]);
			        if(next->flag == 0){//If the next block is free
			            prev->size_of_block = prev->size_of_block + (2*BLOCK_SIZE) + pres->size_of_block + next->size_of_block;
    					prev->next_index = next->next_index;
    					return;
			        }
			        else{//If the next block is not free
			            prev->size_of_block = prev->size_of_block + BLOCK_SIZE + pres->size_of_block;
    					prev->next_index = pres->next_index;
    					return;
			        }
			    }
			    else{//If there is no next block
			        prev->size_of_block = prev->size_of_block + BLOCK_SIZE + pres->size_of_block;
					prev->next_index = pres->next_index;
					return;
			    }
			}
			else{//If there is no previous block , if previous block is present then it is not free
			    if(pres->next_index != -1){//If the next block is present
			        j = i;
			        j += pres->size_of_block;
			        next = (block_info*)(&p[j]);
			        if(next->flag == 0){//If the next block is free
			            pres->size_of_block = pres->size_of_block + BLOCK_SIZE + next->size_of_block;
    					pres->next_index = next->next_index;
    					pres->flag = 0;
    					return;
			        }
			        else{//If the next block is not free
			            pres->flag = 0;
    					return;
			        }
			    }
			    else{//If the next block is not present
			        pres->flag = 0;
    					return;
			    }
			}
		}
		else{//If b is NULL or 
			i += pres->size_of_block;
		}
	}
	return;	
}

void print_book(){//Prints the book size when free and when allocated
    printf("%lu\n%lu\n\n", sizeof(block_info), sizeof(block_info));
}


void display_mem_map(){
	if(SIZE == 0)//IF the size is zero
		return ;
	block_info *temp;
	int i = 0;
	while(i < SIZE){//Iterating through p
		temp = (block_info*)(&p[i]);
		printf("%d\t", i);//Start index of the book
		printf("%lu\t", BLOCK_SIZE);//End index of the book
		printf("book\n");
		i += BLOCK_SIZE;
		printf("%d\t", i);//Start index of the block
		printf("%d\t", temp->size_of_block);//End index of the block
		if(temp->flag == 0)//If the block is free
			printf("free\n");
		else//IF the block is allocated
			printf("allocated\n");
		i += temp->size_of_block;
	}
	printf("\n");
}

#if 0
void main()
{
    allocate(200);
    char *a = (char *)mymalloc(30 * sizeof(char));
	display_mem_map();
	printf("\n");
	char *b = (char *)mymalloc(40 * sizeof(char));
	display_mem_map();
	printf("\n");
	char *c = (char *)mymalloc(30 * sizeof(char));
	display_mem_map();
	printf("\n");
	myfree(a);
	display_mem_map();
	printf("\n");
	myfree(b);
	display_mem_map();
	printf("\n");
    myfree(c);
	display_mem_map();
	printf("\n");
}
#endif
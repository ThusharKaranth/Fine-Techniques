#include<stdio.h>
#include<stdlib.h>
#include"assignment_4.h"

FILE* init_tree(const char* filename){//Initializing the file pointer
    FILE* fp=fopen(filename,"r+");//If file is present then open it
    if(fp==NULL){//If file is not there
        fp = fopen(filename, "w+");
        tree_t temp;
        temp.free_head=-1;
        temp.root=-1;
		fwrite(&temp, sizeof(tree_t), 1, fp);
		fclose(fp);
		fp = fopen(filename,"r+");
    }
	return fp;
}

void close_tree(FILE *fp){//Removing the file pointer or closing the file
    fclose(fp);
}

void display_inorder_recurtion(int key, FILE* fp){//Calls itself and displays in inorder
    node_t node;
    fseek(fp,key,SEEK_SET);
    fread(&node,sizeof(node_t),1,fp);
    if(node.left_offset != -1 || node.right_offset != -1){//If it is not leaf node
        if(node.left_offset != -1 && node.right_offset != -1){//If it has both nodes filled
            display_inorder_recurtion(node.right_offset,fp);
            printf("%d ",node.key);
            display_inorder_recurtion(node.left_offset,fp);
        }
        else if(node.left_offset != -1){//If right node is NULL
            printf("%d ",node.key);
            display_inorder_recurtion(node.left_offset,fp);
        }
        else{//If left node is NULL
            display_inorder_recurtion(node.right_offset,fp);
            printf("%d ",node.key);
        }
    }
    else{//If leaf node
        printf("%d ",node.key);
    }
}

// Space separated keys. Last key followed by '\n'
void display_inorder(FILE *fp){//Calls display_preorder_recurtion and displays in inorder
    tree_t temp;
    fseek(fp,0,SEEK_SET);
    fread(&temp,sizeof(tree_t),1,fp);
    if(temp.root==-1){//If no element is present then leave a line blank
        printf("\n");
        return;
    }
    else{//If root is not NULL
        node_t node;
        fseek(fp,temp.root,SEEK_SET);
        fread(&node,sizeof(node_t),1,fp);
        if(node.left_offset != -1 || node.right_offset != -1){//If it is not leaf node
            if(node.left_offset != -1 && node.right_offset != -1){//If it has both nodes filled
                display_inorder_recurtion(node.right_offset,fp);
                printf("%d ",node.key);
                display_inorder_recurtion(node.left_offset,fp);
            }
            else if(node.left_offset != -1){//If right node is NULL
                printf("%d ",node.key);
                display_inorder_recurtion(node.left_offset,fp);
            }
            else{//If left node is NULL
                display_inorder_recurtion(node.right_offset,fp);
                printf("%d ",node.key);
            }
        }
        else{//If leaf node
            printf("%d ",node.key);
        }
    }
    printf("\n");
}

void display_preorder_recurtion(int key, FILE* fp){//Calls itself and displays in preorder
    node_t node;
    fseek(fp,key,SEEK_SET);
    fread(&node,sizeof(node_t),1,fp);
    if(node.left_offset != -1 || node.right_offset != -1){//If it is not leaf node
        if(node.left_offset != -1 && node.right_offset != -1){//If it has both nodes filled
            printf("%d ",node.key);
            display_preorder_recurtion(node.right_offset,fp);
            display_preorder_recurtion(node.left_offset,fp);
        }
        else if(node.left_offset != -1){//If right node is NULL
            printf("%d ",node.key);
            display_preorder_recurtion(node.left_offset,fp);
        }
        else{//If left node is NULL
            printf("%d ",node.key);
            display_preorder_recurtion(node.right_offset,fp);
        }
    }
    else{//If leaf node
        printf("%d ",node.key);
    }
}

void display_preorder(FILE *fp){//Calls display_preorder_recurtion and displays in preorder
    tree_t temp;
    fseek(fp,0,SEEK_SET);
    fread(&temp,sizeof(tree_t),1,fp);
    if(temp.root==-1){//If no element is present then leave a line blank
        printf("\n");
        return;
    }
    else{//If root is not NULL
        node_t node;
        fseek(fp,temp.root,SEEK_SET);
        fread(&node,sizeof(node_t),1,fp);
        if(node.left_offset != -1 || node.right_offset != -1){//If it is not leaf node
                if(node.left_offset != -1 && node.right_offset != -1){//If it has both nodes filled
                printf("%d ",node.key);
                display_preorder_recurtion(node.right_offset,fp);
                display_preorder_recurtion(node.left_offset,fp);
            }
            else if(node.left_offset != -1){//If right node is NULL
                printf("%d ",node.key);
                display_preorder_recurtion(node.left_offset,fp);
            }
            else{//If left node is NULL
                printf("%d ",node.key);
                display_preorder_recurtion(node.right_offset,fp);
            }
        }
        else{//If leaf node
            printf("%d ",node.key);
        }
    }
    printf("\n");
}

void insert_key_recurtion(int key, int offset,FILE* fp){//Calls itself recursively till key is inserted into specific position if key is already present then it just returns
    int of;
    node_t temp_node;
    tree_t temp;
    fseek(fp,0,SEEK_SET);
    fread(&temp,sizeof(tree_t),1,fp);
    node_t node;
    fseek(fp,offset,SEEK_SET);
    fread(&node,sizeof(node_t),1,fp);
    if(node.key==key){//If key is already present
        return;
    }
    else if(node.key > key){//If key is more than this node
        if(node.right_offset != -1){//If right node is not NULL
            insert_key_recurtion(key,node.right_offset,fp);
        }
        else{//If right node is NULL
            node_t node_insert;
            node_insert.key = key;
            node_insert.left_offset=-1;
            node_insert.right_offset=-1;
            if(temp.free_head!=-1){//If there is a free space formed because of deleting
                of = temp.free_head;
                fseek(fp,of,SEEK_SET);
                fread(&temp_node,sizeof(node_t),1,fp);
                temp.free_head=temp_node.left_offset;
            }
            else{//If there is no free space in file
                fseek(fp, 0, SEEK_END);
		        of = ftell(fp);
            }
            fseek(fp,0,SEEK_SET);
            fwrite(&temp,sizeof(tree_t),1,fp);
            fseek(fp,of,SEEK_SET);
            fwrite(&node_insert,sizeof(node_t),1,fp);
            node.right_offset = of;
            fseek(fp,offset,SEEK_SET);
            fwrite(&node,sizeof(node_t),1,fp);
        }
    }
    else{//If key is less than this node
        if(node.left_offset != -1){//If left node is not NULL
            insert_key_recurtion(key,node.left_offset,fp);
        }
        else{//If left node is NULL
            node_t node_insert;
            node_insert.key = key;
            node_insert.left_offset=-1;
            node_insert.right_offset=-1;
            if(temp.free_head!=-1){//If there is a free space formed because of deleting
                of = temp.free_head;
                fseek(fp,of,SEEK_SET);
                fread(&temp_node,sizeof(node_t),1,fp);
                temp.free_head=temp_node.left_offset;
            }
            else{//If there is  no free space in file
                fseek(fp, 0, SEEK_END);
		        of = ftell(fp);
            }
            fseek(fp,0,SEEK_SET);
            fwrite(&temp,sizeof(tree_t),1,fp);
            fseek(fp,of,SEEK_SET);
            fwrite(&node_insert,sizeof(node_t),1,fp);
            node.left_offset = of;
            fseek(fp,offset,SEEK_SET);
            fwrite(&node,sizeof(node_t),1,fp);
        }
    }
}

void insert_key(int key, FILE *fp){//insert_key calls insert_key_recurtion
    tree_t temp;
    fseek(fp,0,SEEK_SET);
    fread(&temp,sizeof(tree_t),1,fp);
    if(temp.root!=-1){//If there is already a root present
        insert_key_recurtion(key,temp.root,fp);
    }
    else{//If there is no root
        node_t node;
        node.key = key;
        node.left_offset=-1;
        node.right_offset=-1;
        fseek(fp,0,SEEK_END);
        int of=ftell(fp);
        fwrite(&node,sizeof(node_t),1,fp);
        temp.root=of;
        fseek(fp,0,SEEK_SET);
        fwrite(&temp,sizeof(tree_t),1,fp);
    }
}

void find_delete_inorder_successor_recurtion(int present_offset, int previous_offset, int actual_offset,FILE* fp){//This function finds inorder successor and stores the values to present node and deletes inorder successor
    tree_t temp;
    node_t present_node;
    fseek(fp,0,SEEK_SET);
    fread(&temp,sizeof(tree_t),1,fp);
    fseek(fp,present_offset,SEEK_SET);
    fread(&present_node,sizeof(node_t),1,fp);
    if(present_node.right_offset==-1){//If the right node of present node is NULL
        node_t actual_node;
        node_t previous_node;
        fseek(fp,previous_offset,SEEK_SET);
        fread(&previous_node,sizeof(node_t),1,fp);
        fseek(fp,actual_offset,SEEK_SET);
        fread(&actual_node,sizeof(node_t),1,fp);
        actual_node.key=present_node.key;
        int value=previous_node.right_offset;
        previous_node.right_offset=present_node.left_offset;
        present_node.left_offset=temp.free_head;
        temp.free_head=value;
        fseek(fp,previous_offset,SEEK_SET);
        fwrite(&previous_node,sizeof(node_t),1,fp);
        fseek(fp,actual_offset,SEEK_SET);
        fwrite(&actual_node,sizeof(node_t),1,fp);
        fseek(fp,0,SEEK_SET);
        fwrite(&temp,sizeof(tree_t),1,fp);
        fseek(fp,present_offset,SEEK_SET);
        fwrite(&present_node,sizeof(node_t),1,fp);
    }
    else{//If the right node of present node is not NULL
        find_delete_inorder_successor_recurtion(present_node.right_offset,present_offset,actual_offset,fp);
    }

}

void find_delete_inorder_successor(int present_offset,FILE* fp){//deletes the node
    tree_t temp;
    node_t present_node;
    node_t temp_node;
    fseek(fp,0,SEEK_SET);
    fread(&temp,sizeof(tree_t),1,fp);
    fseek(fp,present_offset,SEEK_SET);
    fread(&present_node,sizeof(node_t),1,fp);
    fseek(fp,present_node.left_offset,SEEK_SET);
    fread(&temp_node,sizeof(node_t),1,fp);
    if(temp_node.right_offset==-1){//If the present's left's right node is NULL
        int temp_offset=present_node.left_offset;
        present_node.key=temp_node.key;
        present_node.left_offset=temp_node.left_offset;
        temp_node.left_offset=temp.free_head;
        temp.free_head=temp_offset;
        fseek(fp,0,SEEK_SET);
        fwrite(&temp,sizeof(tree_t),1,fp);
        fseek(fp,present_offset,SEEK_SET);
        fwrite(&present_node,sizeof(node_t),1,fp);
        fseek(fp,temp_offset,SEEK_SET);
        fwrite(&temp_node,sizeof(node_t),1,fp);
    }
    else{//If the present's left's right node is not NULL
        find_delete_inorder_successor_recurtion(temp_node.right_offset,present_node.left_offset,present_offset,fp);
    }
}

void delete_key_recurtion(int key, int present_offset,int previous_offset, FILE* fp){//Delete key using recurtion
    if(present_offset==-1){//If present node is NULL
        return;
    }
    else{//If present node is not NULL
        tree_t temp;
        node_t present_node;
        fseek(fp,0,SEEK_SET);
        fread(&temp,sizeof(tree_t),1,fp);
        fseek(fp,present_offset,SEEK_SET);
        fread(&present_node,sizeof(node_t),1,fp);
        if(key==present_node.key){//If the key is same as present node
            if(present_node.left_offset==-1 && present_node.right_offset==-1){//If present node is leaf node
                if(previous_offset!=-1){//If the present node is not root node
                    node_t previous_node;
                    fseek(fp,previous_offset,SEEK_SET);
                    fread(&previous_node,sizeof(node_t),1,fp);
                    if(previous_node.left_offset==present_offset){//If present node is in the left of previous node
                        previous_node.left_offset=-1;
                    }
                    else if(previous_node.right_offset==present_offset){//If present node is in the right of the previous node
                        previous_node.right_offset=-1;
                    }
                    fseek(fp,previous_offset,SEEK_SET);
                    fwrite(&previous_node,sizeof(node_t),1,fp);
                }
                else{//If the present node is root node
                    temp.root=-1;
                }
                present_node.left_offset=temp.free_head;
                temp.free_head=present_offset;
                fseek(fp,0,SEEK_SET);
                fwrite(&temp,sizeof(tree_t),1,fp);
                fseek(fp,present_offset,SEEK_SET);
                fwrite(&present_node,sizeof(node_t),1,fp);
            }
            else{//If the present node is not leaf node
                if(present_node.left_offset==-1 || present_node.right_offset==-1){//If one of the right or left is NULL
                    if(previous_offset==-1){//If present node is root node
                        if(present_node.left_offset==-1){//If present node's left node is NULL
                            temp.root=present_node.right_offset;
                        }
                        else if(present_node.right_offset==-1){//If present node's right node is NULL
                            temp.root=present_node.left_offset;
                        }
                    }
                    else{//If present node is not a root node
                        node_t previous_node;
                        fseek(fp,previous_offset,SEEK_SET);
                        fread(&previous_node,sizeof(node_t),1,fp);
                        if(present_node.left_offset==-1){//If present node's left node is NULL
                            previous_node.right_offset=present_node.right_offset;
                        }
                        else if(present_node.right_offset==-1){//If present node's right node is NULL
                            previous_node.left_offset=present_node.left_offset;
                        }
                        fseek(fp,previous_offset,SEEK_SET);
                        fwrite(&previous_node,sizeof(node_t),1,fp);
                    }
                    present_node.left_offset=temp.free_head;
                    temp.free_head=present_offset;
                    fseek(fp,0,SEEK_SET);
                    fwrite(&temp,sizeof(tree_t),1,fp);
                    fseek(fp,present_offset,SEEK_SET);
                    fwrite(&present_node,sizeof(node_t),1,fp);
                }
                else{//If both left and right are filled
                    find_delete_inorder_successor(present_offset,fp);
                }
            }
        }
        else if(key > present_node.key){//If the present node is less than key
            delete_key_recurtion(key,present_node.left_offset,present_offset,fp);
        }
        else{//If the present node is more than key
            delete_key_recurtion(key,present_node.right_offset,present_offset,fp);
        }
    }
}

void delete_key(int key, FILE *fp){//Calls delete_key_recurtion to delete node
    tree_t temp;
    fseek(fp,0,SEEK_SET);
    fread(&temp,sizeof(tree_t),1,fp);
    delete_key_recurtion(key,temp.root,-1,fp);
}
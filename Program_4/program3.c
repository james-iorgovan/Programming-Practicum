#include <stdlib.h>
#include <string.h>
#include "header.h"

extern int debugMode;

//(Substitution) Typedef enum {FALSE = 0, TRUE} bool;

//Add new node to the end of the list. 
void addToList(Node **hd, char *name, int groupSize, boolean status){
       
        Node *q = (Node*)malloc(sizeof(Node));
        q->name =(char*)(malloc(sizeof(char) * (strlen(name)+1))); 
        q->next = NULL;
    
        strcpy(q->name, name);
        q->groupSize = groupSize;
        q->status = status;
        Node *cur = *hd;
        if(*hd == NULL){
                *hd = q;
                return;    
        }   
        else{
                while(cur->next !=NULL){
                        cur = cur->next;
                }   
                cur->next = q;
                return;
        }   
    
}

//Check if name exists
int doesNameExist(Node *hd, char* name){
        //A C W L calls
        Node *p = hd; 
        while(p!=NULL){
                if(strcmp(p->name, name) == 0){ 
                        return 1;
                }   
                p = p->next;
        }   
        return 0;
}



//Call update status if table is takent
int  updateStatus(Node *hd, char *name){
        
        Node *p = hd; 
        while(p!= NULL){
                if(strcmp(p->name,name)==0){
                        if(p->status == TRUE){//the group is already in restaurant, nothing to update
                                return 0;
                        }   
                        else{//the group had called ahead and has gotten to the restaurant, now they're waiting in restaurant
                                p->status = TRUE;
                                return 1;
                        }
                }
                p = p->next;
        }
        return 0;//the name wasn't in the queue
}

//Call if a group shows and occupies table size of X
char* retrieveAndRemove(Node **hd, int tableSize){
       
        Node *p = *hd;
        char *name =(char*)(malloc(sizeof(char) * (strlen(p->name)+1)));
        strcpy(name, p->name);
        Node *prev = NULL;
        if(p == NULL){
                printf("There are no groups to be seated\n");
                return NULL;
        }
        while(p != NULL){
                if(p->groupSize <= tableSize){
                        if(prev == NULL){
                                *hd = p->next;
                        }
                        else{
                                prev->next = p->next;
                        }
                        strcpy(name, p->name);
                        free(p);
                        return name;
                }
                prev = p;
                p = p->next;
        }
        return NULL;
}


//Return queue
int countGroupsAhead(Node *hd, char *name){
        Node *p = hd;
        int counter = 0;
        while(strcmp(p->name, name)!=0){
                p = p->next;
                counter++;
        }
        return counter;
}


void displayGroupSizeAhead(Node *hd, char *name){
        Node *p = hd;
        while(strcmp(p->name, name) != 0){
                printf("%s ", p->name);
                p = p->next;
        }

}


void displayListInformation(Node *hd){
        Node *p = hd;
        while(p != NULL){

                printf("Group Name: %s", p->name);
                printf("\n");
                printf("Group size: %d", p->groupSize);
              //  printf("\n");
                printf("Status:");
                if(p->status == 1) printf(" in restaurant.\n");
		else printf(" Not in  restaurant.\n");
		printf("\n");
                printf("--------------\n\n");
                p = p->next;
        }
}


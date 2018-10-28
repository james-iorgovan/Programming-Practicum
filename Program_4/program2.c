#include <stdio.h>
#include <stdlib.h>
#include "header.h"

extern int debugMode;


//Typedef enum {FALSE = 0, TRUE} bool; (substitution)
void doAdd (Node **hd)
{       
        //Call group table SIZE
        int size = getPosInt();
        if (size < 1)
        {       
                printf ("Error: Add command requires an integer value of at least 1\n");
                printf ("Add command is of form: a <size> <name>\n");
                printf ("  where: <size> is the size of the group making the reservation\n");
                printf ("         <name> is the name of the group making the reservation\n");
                return;
        }
        
        //Call group NAME
        char *name = getName();
        if (NULL == name)
        {       
                printf ("Error: Add command requires a name to be given\n");
                printf ("Add command is of form: a <size> <name>\n");
                printf ("where: <size> is the size of the group making the reservation\n");
                printf ("<name> is the name of the group making the reservation\n");
                return;
        }
        
        printf ("Adding group \"%s\" of size %d.\n", name, size);

       
        int doesExist = doesNameExist(*hd, name);
        if(doesExist == 1){
                printf("The name already exist.\n");
        }
        else{   
                addToList(hd, name, size, YES);
        }
}


void doCallAhead (Node **hd)
{       
        //Call group SIZE from stack
        int size = getPosInt();
        if (size < 1)
        {       
                printf ("Error: Call-ahead command requires an integer value of at least 1\n");
                printf ("Call-ahead command is of form: c <size> <name>\n");
                printf ("  where: <size> is the size of the group making the reservation\n");


     printf ("         <name> is the name of the group making the reservation\n");
                return;
        }
        
        //Call group NAME from stack
        char *name = getName();
        if (NULL == name)
        {       
                printf ("Error: Call-ahead command requires a name to be given\n");
                printf ("Call-ahead command is of form: c <size> <name>\n");
                printf ("  where: <size> is the size of the group making the reservation\n");
                printf ("         <name> is the name of the group making the reservation\n");
                return;
        }
        
        printf ("Call-ahead group \"%s\" of size %d\n", name, size);
        
        int doesExist = doesNameExist(*hd, name);
        if(doesExist == 1){
                printf("The name already exist, cannot add\n");
        }
        else{   
                addToList(hd, name, size, NO);
        }
}

void doWaiting (Node **hd)
{       
        //Get group NAME from stack
        char *name = getName();
        if (NULL == name)
        {       
                printf ("Error: Waiting command requires a name to be given\n");
                printf ("Waiting command is of form: w <name>\n");
                printf ("  where: <name> is the name of the group that is now waiting\n");
                return;
        }

        printf ("Waiting group \"%s\" is now in the restaurant\n", name);
        if(updateStatus(*hd, name) == 0){
                printf("Nothing to be done\n");
        }
        else{
                printf("It got updated\n");
        }
}

void doRetrieve (Node **hd)
{
        //Call table SIZE from stack
        int size = getPosInt();
        if (size < 1)
        {
                printf ("Error: Retrieve command requires an integer value of at least 1\n");
                printf ("Retrieve command is of form: r <size>\n");
                printf ("  where: <size> is the size of the group making the reservation\n");
                return;
        }
        clearToEoln();
        printf ("Retrieve (and remove) the first group that can fit at a tabel of size %d\n", size);

        char* this=retrieveAndRemove(hd, size);
}

void doList (Node **hd)
{
        //Call group NAME from stack
        char *name = getName();
        if (NULL == name)
        {
                printf ("Error: List command requires a name to be given\n");
                printf ("List command is of form: l <name>\n");
                printf ("  where: <name> is the name of the group to inquire about\n");
                return;
        }

        printf ("Group \"%s\" is behind the following groups\n", name);
        displayGroupSizeAhead(*hd, name);
        printf("\n");
        printf("Total number of groups ahead: %d\n", countGroupsAhead(*hd, name));
}

void doDisplay (Node **hd)
{
        clearToEoln();
        printf ("Display information about all groups\n");

        displayListInformation(*hd);
}


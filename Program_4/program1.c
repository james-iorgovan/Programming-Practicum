#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

extern int debugMode;

void clearToEoln();

//Call function until char is read

int getNextNWSChar ()
{
 int ch;

 ch = getc(stdin);
 if (ch == EOF || ch == '\n')
   return ch;
 while (isspace (ch))
   {
    ch = getc(stdin);
    if (ch == EOF || ch == '\n')
      return ch;
   }
 return ch;
}


int getPosInt ()
{
 int value = 0;

 //Clear blank chars
 int ch;
 ch = getc(stdin);
 while (!isdigit(ch))
   {
    if ('\n' == ch) 
       return 0;
    if (!isspace(ch)) 
      {
       clearToEoln();
       return 0;
      }
    ch = getc(stdin);
   }

 value = ch - '0';
 ch = getc(stdin);
 while (isdigit(ch))
   {
    value = value * 10 + ch - '0';
    ch = getc(stdin);
   }

 ungetc (ch, stdin);  

 //Clear to end of line if value = 0
 if (0 == value)
    clearToEoln();
   
 return value;
}


char *getName()
{
 
 int ch;
 ch = getc(stdin);
 while (isspace(ch))
   {
    if ('\n' == ch) 
       return NULL;
    ch = getc(stdin);
   }

 char *word;
 int size;
 size = 10;
 word = (char *) malloc (sizeof(char) * size);
  
 //Call and read each char until new line
 int count = 0;

 while (ch != '\n')
   {
    if (count + 1 >= size)
      {
       //Dynamically malloc array
       char* temp;
       int i;
       size = size * 2;
       temp = (char *) malloc (sizeof(char) * size);
       
       
       for (i = 0 ; i < count ; i++)
           temp[i] = word[i];

       free (word);
       word = temp;
      }

    word[count] = ch;
    count++;
    word[count] = '\0';

    //Get next char
    ch = getc(stdin);
   }

 if (count > 30)
   {
    count = 30;
    word[count] = '\0';
   }
 
 
 while (isspace (word[count-1]))
   {
    count--;
    word[count] = '\0';
   }

 return word;
}


//Clear until end of line
void clearToEoln()
{
 int ch;
 
 do {
     ch = getc(stdin);
    }
 while ((ch != '\n') && (ch != EOF));
}


void printCommands()
{
 printf ("The commands for this program are:\n\n");
 printf ("q - to quit the program\n");
 printf ("? - to list the accepted commands\n");
 printf ("a <size> <name> - to add a group to the wait list\n");
 printf ("c <size> <name> - to add a call-ahead group to the wait list\n");
 printf ("w <name> - to specify a call-ahead group is now waiting in the restaurant\n");
 printf ("r <table-size> - to retrieve the first waiting group that can fit at the available table size\n");
 printf ("l <name> - list how many groups are ahead of the named group\n");
 printf ("d - display the wait list information\n");
       
 //Clear input at end of the line
 clearToEoln();
}


int main (int argc, char **argv)
{

 char *input;
 int ch;
 Node *head = NULL;

 int i;
 for (i = 0; i < argc; i++) {
    if (strcmp(argv[i], "-d") == 0) {
       debugMode = 1;
       printf("Debugging Information... \n\n");
    }
    else {
       debugMode = 0;
    }
 }


 printf ("Starting Restaurant Wait List Program\n\n");
 printf ("Enter command: ");

//Iterate through command list
 while ((ch = getNextNWSChar ()) != EOF)
   {
    
    if ('q' == ch)
      {
       printf ("Quitting Program.\n");
       return (0);
      }
    else if ('?' == ch)
      {
       printCommands();
      }
    else if('a' == ch)
      {
       doAdd(&head);
      } 
    else if('c' == ch)
      {
       doCallAhead(&head);
      } 
    else if('w' == ch)
      {
       doWaiting(&head);
      } 
    else if('r' == ch)
      {
       doRetrieve(&head);
      } 
    else if('l' == ch)
      {
       doList(&head);
      } 
    else if('d' == ch)
      {
       doDisplay(&head);
      } 
    else if('\n' == ch)
      {
       
        
      } 
    else
      {
       printf ("%c - in not a valid command\n", ch);
       printf ("For a list of valid commands, type ?\n");
       clearToEoln();
      }

    printf ("\nEnter command: ");
   }

 printf ("Quiting Program - EOF reached\n");
 return 1;
}


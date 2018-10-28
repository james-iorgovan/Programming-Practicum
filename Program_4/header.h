#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum{FALSE = 0, TRUE, NO = 0, YES} boolean;


typedef struct Node{
  char* name;
  int groupSize;
  boolean status;
  struct Node *next;
}Node;

int debugMode;

extern void clearToEoln();
extern int  getNextNWSChar();
extern int getPosInt();
extern char* getName();
extern void printCommands();

extern void doAdd(Node **hd);
extern void doCallAhead(Node **hd);
extern void doWaiting(Node **hd);
extern void doRetrieve(Node **hd);
extern void doList(Node **hd);
extern void doDisplay(Node **hd);

extern void addToList(Node ** head, char * name, int groupSize, boolean status);
extern int  doesNameExist(Node * head, char * name);
extern int updateStatus(Node * head, char * name);
extern char* retrieveAndRemove(Node ** head, int tableSize);
extern int countGroupsAhead(Node * head, char * name);
extern void displayGroupSizeAhead(Node * head, char * name);
extern void displayListInformation(Node * head);


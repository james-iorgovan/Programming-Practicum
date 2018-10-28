#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {FALSE = 0, TRUE, NO = 0, YES} boolean;


typedef struct Node{
  char* name[30];
  int groupSize;
  enum status;
  struct Node *next;
}Node;


extern void clearToEoln();
extern int  getNextNWSChar();
extern int getPosInt();
extern char* getName();
extern void printCommands();

extern void doAdd();
extern void doCallAhead();
extern void doWaiting();
extern void doRetrieve();
extern void doList();
extern void doDisplay();


extern void addToList(Node * head, int groupSize, char* name, enum status);
extern enum doesNameExist(Node * head, char* name);
extern enum updateStatus(Node * head);
extern char* retrieveAndRemove(Node *head);
extern int countGroupsAhead(Node *head, char* name);
extern void displayGroupSizeAhead(Node *head, char* name);
extern void displayListInformation(Node *head);

extern int main()


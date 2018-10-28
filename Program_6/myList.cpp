#include<iostream>
using namespace std;
 
 
class MyLNode{
		private:
				char* name;
				MyLNode *next;
		public:
				MyLNode(char* s)
				{
						name = s;
						next = NULL;
				}
				void setName (char* s)
				{
						name = s;
				}
 
				char* getName()
				{
						return name;
				}
 
				void setNext(MyLNode* n)
				{
						next = n;
				}
 
				MyLNode* getNext()
				{
						return next;
				}
 
};
 
class myList{
		private:
				MyLNode *head;
 
		public:
				myList(){
						MyLNode *head = NULL;
				}
				void insertValue(char* s){
						MyLNode *temp = new MyLNode(s);
 
						temp->setNext(head);
 
						head = temp;
				}
 
				void deleteValue(char* s){
						MyLNode *temp = head;
						MyLNode *prev = temp;
 
						if(temp == NULL){
								printf("Cannot delete from empty stack\n");
								return;
						}
 
						if(strcmp(s, head->getName()) == 0){
								head = head->getNext();
								return;
						}
 
						while(temp->getNext() != NULL){
								if(strcmp(s, head->getName()) == 0){
										prev->setNext(temp->getNext());
										temp = NULL;
										return;
								}
								prev = temp;
								temp = temp->getNext();
						}
 
						if(strcmp(s, head->getName()) == 0){
								prev->setNext(NULL);
								return;
						}
						printf("%c was not in stack\n", s);
						return;
				}
 
				int getNumberOfCurrentValues(char* s){
						MyLNode *temp = head;
						int counter = 0;
						while(temp != NULL){
								counter++;
								temp = temp->getNext();
						}
						return counter;
 
				}
 
				char* getNthValue(char* s){
						MyLNode *temp = head;
						while(temp != NULL){
								if(strcmp(s, head->getName()) == 0){
										return temp->getName();
								}
								temp = temp->getNext();
						}
						return NULL;
				}
 
				int doesNameExist(char* s){
						MyLNode *temp = head;
 
						if(temp == NULL){
								return 0;
						}
 
						while(temp != NULL){
								if(strcmp(s, head->getName()) == 0){
										return 1;
								}
								temp = temp->getNext();
						}
						return 0;
				}
};

class Node{
	private:
		int elem;
		bool visited;
		Node * next;
	public:
		Node(int e, bool v){
			elem = e;
			visited = v;
			next = NULL;
		}
 
		void set_Elem(int e){
			elem = e;
		}
		int get_Elem(){
			return elem;
		}
		void set_Next(Node *n){
			next = n;
		}
		Node * get_Next(){
			return next;
		}
		bool get_Visited(){
			return visited;
		}
		void set_Visited(bool v){
			visited = v;
		}
};
 
 
class Airport{
		private:
				Node * head;
				int size;
		public:
 
				Airport()
				{
					head = NULL;
					size = 10;
				}
				int getSize(){
					return size;
				}
				void incSize(){
					size++;;
				}
				void decSize(){
					size--;
				}
				void nullSize(){
					size = 0;
				}
 
				int contains(int val){
					Node *temp = head;
 
					if(head == NULL){
					return 0;
					}
					while(temp != NULL){
					if(val == temp->get_Elem()){
						return 1;
					}
					temp = temp->get_Next();
					}
					return 0;
					}
 
				
				int isEmpty(){
						if(head == NULL){
								return 1;
						}
						else{
								return 0;
						}
				}
 
 
				void emptyList(){
						head = NULL;
						nullSize();
				}
 
 
				void push(int e, bool v){
						Node *temp = new Node(e, v);
						temp->set_Next(head);
						head = temp;
						incSize();
				}
 
				void pop(int val){
						Node *temp = head;
						Node *prev = temp;
 
						if(isEmpty() == 1){
								return;
						}
 
						while(temp->get_Next() != NULL){
								if(val == temp->get_Elem()){
										prev->set_Next(temp->get_Next());
										temp = NULL;
										decSize();
										return;
								}
								prev = temp;
								temp = temp->get_Next();
						}
						if(val == temp->get_Elem()){
								prev->set_Next(NULL);
								decSize();
								return;
						}
						decSize();
						return;
				}
 
				int top(){
						if(head != NULL){
								return head->get_Elem();
						}
						else{
								return -999;
						}
				}
 
				void markUnvisited(){
						Node *temp = head;
						bool f = false;
 
						if(temp == NULL){
								return;
						}
						while(temp != NULL){
								temp->set_Visited(f);
								temp = temp->get_Next();
						}
						return;
				}
 
 
				void printList(){
						Node * temp = head;
 
						if(isEmpty() == 1){
								printf("List is empty\n");
								return;
						}
 
						while(temp!= NULL){
								printf("%d, ", temp->get_Elem());
								temp = temp->get_Next();
						}
						printf("\n");
						return;
				}
 
 
				Node * headOfList(){
						if(head == NULL){
								return NULL;
						}
						return head;
				}
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//--------------------------------------------------------------------------------------------------------------------
typedef struct mazeStruct{
    char** arr;
    int xsize, ysize;
    int xstart, ystart;
    int xend, yend;
 }maze;

//--------------------------------------------------------------------------------------------------------------------
typedef struct Node{
    int x;
    int y;
    struct Node * next;
 }NODE;


//--------------------------------------------------------------------------------------------------------------------
//Point to the stack of coordinates
typedef NODE * pointer;


//--------------------------------------------------------------------------------------------------------------------
//Check if the stack is empty
int isEmpty(pointer p){
    if (p == NULL){
        return 1; // returns TRUE if empty
    }
    else {
        return 0; // returns FALSE if not empty
    }
 }


//--------------------------------------------------------------------------------------------------------------------
//Push coordinates onto stack
void push(pointer *p, int x, int y){
    pointer temp = (pointer)malloc(sizeof(NODE));
    temp->x = x;
    temp->y = y;
    temp->next = *p;
    *p = temp; 
 }


//--------------------------------------------------------------------------------------------------------------------
//Accesses first set of coordinates of stack
void top(pointer p, int* x, int* y){
    if(p != NULL){
        *x = p->x;
        *y = p->y;
    }
    else{
        printf("Stack is empty\n");
        exit(-1);
    }
 }


//--------------------------------------------------------------------------------------------------------------------
//Remove first set of coordinates on stack
void pop(pointer *p){
    if(*p!= NULL){
        pointer temp = *p;
        *p =(*p)->next;
        free(temp);
    }
 }


//--------------------------------------------------------------------------------------------------------------------
//Empties out entire stack stack one by one until stack is empty
void reset(pointer *p) {
    while (*p != NULL){
        pop(p); //Remove first node until stack is empty
    }
 }


//--------------------------------------------------------------------------------------------------------------------
//Prints the coordinates of the stack
void printStack(pointer p){
    if(p != NULL){
        printf("%d, %d\n ", p->x, p->y);
        p = p->next;
    }
 }


//--------------------------------------------------------------------------------------------------------------------
//Print out the maze
void printGrid(maze m){
    int i,j;
    for (i = 0; i < m.xsize+2; i++)
    {
        for (j = 0; j < m.ysize+2; j++)
            printf ("%c", m.arr[i][j]);
        printf("\n");
    }
 }

//--------------------------------------------------------------------------------------------------------------------
pointer init_stack(maze m){
pointer stack = NULL;
    

    //Push start coordinate onto the stack
    push(&stack, m.xstart, m.ystart);
    int end = 0;


    //End hasn't been reached on empty stack
    while(!isEmpty(stack) && end == 0){
        int x = 0;
        int y= 0;
        

        //Nested loop that iterates through the maze
        top(stack, &x, &y);
       

	//If end is reached, break out of loop
                if(m.xend == x && m.yend == y){
                    end = 1;
                    break;
                }
        
                //Checks if neighboring values are empty and not the end
                //Marks position as visited
                if (m.arr[x][y + 1] == '.' || m.arr[x][y+1] == 'e') {  
                    push(&stack, x, y+1);
                    m.arr[x][y + 1] = 'v';
                    
                    printGrid(m);
                }
                else if (m.arr[x+1][y] == '.' || m.arr[x+1][y]== 'e') {
                    push(&stack, x+1, y);
                    m.arr[x+1][y] = 'v';
                    printGrid(m);
                }
                else if (m.arr[x][y-1] == '.' || m.arr[x][y-1] == 'e') {
                    push(&stack, x, y-1);
                    m.arr[x][y-1] = 'v';
                    printGrid(m);
                }
                else if (m.arr[x-1][y] == '.' || m.arr[x-1][y] == 'e') {
                    push(&stack, x-1, y);
                    m.arr[x-1][y] = 'v';
                    printGrid(m);
                }
       
                //If the neighboring values are not periods, pop the top stack and backtrack
                else {
                    pop(&stack);
                    
                }
    }
    
        return stack;
 }

//--------------------------------------------------------------------------------------------------------------------
/*
//Print out stack in reverse order (cannot get it to work properly)
void reverseStack(pointer *p){ 
  if(p == NULL)
	return;
	else{
	reverseStack(p->next);
	printf("( %d, %d)\n", p->x, p->y);
}
 */
/* while(p != last){
    curr = p;
    while(curr->next != last){
      curr = curr->next;
    }
    printf("( %d, %d)", curr->x, curr->y);
    last = curr;
  }
  printf("\n\n");
}*/



//--------------------------------------------------------------------------------------------------------------------
int main(int argc, char **argv){
    maze m1;
    int xpos, ypos;
    int j;
    FILE *src;
    

    //Verify the proper number of command line arguments
    if(argc != 2) {
        printf("Usage: %s <input file name>\n", argv[0]);
        exit(-1);
    }
    

    //Check to open input file.
    if ( ( src = fopen( argv[1], "r" )) == NULL ){
        printf ( "Can't open input file: %s", argv[1] );
        exit(-1);
    }
    
    
    //Check input that the maze is not 0 or negative integer
    do{
        fscanf(src, "%d %d", &m1.xsize, &m1.ysize);
        if (m1.xsize <= 0 || m1.ysize <= 0){
            fprintf(stderr, "%d %d   <= Invalid: Maze sizes must be greater than 0\n", m1.xsize, m1.ysize);
        }
        else{
            printf("size: %d, %d\n", m1.xsize, m1.ysize);
            break;
        }
    } while(m1.xsize <= 0 || m1.ysize <= 0);
    

    //Check for valid start input
    do{
        fscanf(src, "%d %d", &m1.xstart, &m1.ystart);
        if(m1.xstart > m1.xsize){
            fprintf(stderr, "%d %d   <= Invalid: row %d is outside range from 1 to %d\n", m1.xstart, m1.ystart,  m1.xstart, m1.xsize);
        }
        if(m1.ystart > m1.ysize){
            fprintf(stderr, "%d %d   <= Invalid: column %d is outside range from 1 to %d\n", m1.xstart, m1.ystart,  m1.ystart, m1.ysize);
        }
        else{
            printf("start: %d, %d\n", m1.xstart, m1.ystart);
            break;
        }
    }while(m1.xstart > m1.xsize || m1.ystart > m1.ysize);
    
    
    //Check for valid end input
    do{
        fscanf(src, "%d %d", &m1.xend, &m1.yend);
        if(m1.xend > m1.xsize){
            fprintf(stderr, "%d %d   <= Invalid: row %d is outside range from 1 to %d\n", m1.xend, m1.yend,  m1.xend, m1.xsize);
        }
        if(m1.yend > m1.ysize){
            fprintf(stderr, "%d %d   <= Invalid: column %d is outside range from 1 to %d\n", m1.xend, m1.yend,  m1.yend, m1.ysize);
        }
        if(m1.xend <= m1.xsize && m1.yend <= m1.ysize){
            printf("end: %d, %d\n", m1.xend, m1.yend);
            break;
        }
    }while(m1.xend > m1.xsize || m1.yend > m1.ysize);
   

    //pointer stack = init_stack(m1);
     m1.arr = (char **) malloc (sizeof(char *) * m1.xsize+2);
    int i;
    for (i = 0; i < m1.xsize+2; i++){
        m1.arr[i] = (char *) malloc (sizeof(char) * m1.ysize+2);
    }

 
    for (i = 0; i < m1.xsize+2; i++)
        for (j = 0; j < m1.ysize+2; j++)
            m1.arr[i][j] = '.';


    //Display borders of the maze with stars (*)
    for (i=0; i < m1.xsize+2; i++)
    {
        m1.arr[i][0] = '*';
        m1.arr[i][m1.ysize+1] = '*';
    }
    for (i=0; i < m1.ysize+2; i++)
    {
        m1.arr[0][i] = '*';
        m1.arr[m1.xsize+1][i] = '*';
    }


    //Starting and ending points 
    m1.arr[m1.xstart][m1.ystart] = 's';
    m1.arr[m1.xend][m1.yend] = 'e';

		  
    //Blocked positions in maze 
    while (fscanf (src, "%d %d", &xpos, &ypos) != EOF)
    {
        m1.arr[xpos][ypos] = '*';
    }
    

    //Print out initial maze
    for (i = 0; i < m1.xsize+2; i++)
    {
        for (j = 0; j < m1.ysize+2; j++)
            printf ("%c", m1.arr[i][j]);
        printf("\n");
    }
    
 
    //Initialize stack and add coordinates of path onto the stack
    pointer stack = init_stack(m1);
   

    //If stack is empty, return that there is no path to reach end
    if(isEmpty(stack)){
        printf("Can't reach end.\n");
    }
    
    else{
        printf("\nPath to reach the end of the maze: \n");
        int old_x = -1;
        int old_y = -1;
        pointer temp = stack;
        while (temp != NULL) {
            int x = temp -> x;
            int y = temp -> y ;
            
            if (m1.arr[x][y]!= 'e' && m1.arr[x][y] != 's') {
                if ((x + 1) == old_x) {
                    m1.arr[x][y] = '#';
                }
                else if ((x - 1) == old_x) {
                    m1.arr[x][y] = '#';
                }
                else if ((y + 1) == old_y) {
                    m1.arr[x][y] = '#';
                }
                else if ((y - 1) == old_y) {
                    m1.arr[x][y] = '#';
                }	
                else {
                    printf("\nStack corrdinates: (%d, %d)\n", x, y);
                    exit(-1);
                }
            }
     
            old_x = x;
            old_y = y;
            temp = temp -> next;
        }

        //Print out entire stack
        printf("\nCoordinates for the path are: \n");
        printStack(stack);
        printf("\n");
        
        reset(&stack);
        return 0;
    }        
 }

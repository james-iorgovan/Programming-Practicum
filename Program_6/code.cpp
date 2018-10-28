#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "Airport.cpp"
#include "myList.cpp"


class TravelNetwork
{
 private:
   // Create the Data Members for the Travel Network here
	static Airport* network;
	static myList fileNames; 
	int size; 
 public:
  
 // Use a constructor to initialize the Data Members for Travel Network
 TravelNetwork()
 {
	size = 10;
	int i = 0;
	network = new Airport[1];
	for(i = 0; i < 1; i++){
		network[i] =  Airport();
	}
	fileNames = myList();  

 }
  
 

 // The main loop for reading in input
 void processCommandLoop (FILE* inFile)
 {
  char  buffer[300];
  char* input;

  input = fgets ( buffer, 300, inFile );   // get a line of input
    
  // loop until all lines are read from the input
  while (input != NULL)
  {
    // process each line of input using the strtok functions 
    char* command;
    command = strtok (input , " \n\t");

    printf ("*%s*\n", command);
    
    if ( command == NULL )
      printf ("Blank Line\n");
 
    else if ( strcmp (command, "q") == 0) 
      exit(1);
     
    else if ( strcmp (command, "?") == 0) 
      showCommands();
     
    else if ( strcmp (command, "t") == 0) 
      doTravel();
     
    else if ( strcmp (command, "r") == 0) 
      doResize();

    else if ( strcmp (command, "i") == 0) 
      doInsert();

    else if ( strcmp (command, "d") == 0) 
      doDelete();

    else if ( strcmp (command, "l") == 0) 
      doList();

    else if ( strcmp (command, "f") == 0) 
      doFile();

    else if ( strcmp (command, "#") == 0) 
      ;
     
    else
      printf ("Command is not known: %s\n", command);
     
    input = fgets ( buffer, 300, inFile );   // get the next line of input

  }
 }
 
 void showCommands()
 {
   printf ("The commands for this project are:\n");
   printf ("  q \n");
   printf ("  ? \n");
   printf ("  # \n");
   printf ("  t <int1> <int2> \n");
   printf ("  r <int> \n");
   printf ("  i <int1> <int2> \n");
   printf ("  d <int1> <int2> \n");
   printf ("  l \n");
   printf ("  f <filename> \n");
 }

 void doTravel()
 {
   int val1 = 0;
   int val2 = 0;

   // get an integer value from the input
   char* next = strtok (NULL, " \n\t");
   if ( next == NULL )
   {
     printf ("Integer value expected\n");
     return;
   }
   val1 = atoi ( next );
   if ( val1 == 0 && strcmp (next, "0") != 0)
   {
     printf ("Integer value expected\n");
     return;
   }
   
   // get another integer value from the input
   next = strtok (NULL, " \n\t");
   if ( next == NULL )
   {
     printf ("Integer value expected\n");
     return;
   }
   val2 = atoi ( next );
   if ( val2 == 0 && strcmp (next, "0") != 0)
   {
     printf ("Integer value expected\n");
     return;
   }
   
   
   printf ("Performing the Travel Command from %d to %d\n", 
            val1, val2);

   depthFirstSearch_h(val1, val2);
   
 }
 
 void doResize()
 {
   int val1 = 0;
   int i = 0;

   char* next = strtok (NULL, " \n\t");
   if ( next == NULL )
   {
     printf ("Integer value expected\n");
     return;
   }

   val1 = atoi ( next );
   if ( val1 == 0 && strcmp (next, "0") != 0)
   {
     printf ("Integer value expected\n");
     return;
   }

   for(i = 0; i < network->getSize(); i++){
		network[i].emptyList();
   }

   while(val1 > network->size){
	Airport* newNetwork = new Airport[val1];
	
	for(i = 0; i < val1; i++){
		newNetwork[i] = Airport();
	}
	network = newNetwork;
	
	
   printf ("Performing the Resize Command with %d\n", val1 );
 

   }
}

 void doInsert()
 {

   int val1 = 0;
   int val2 = 0;
   int i = 0;

   char* next = strtok (NULL, " \n\t");
   if ( next == NULL )
   {
     printf ("Integer value expected\n");
     return;
   }

   val1 = atoi ( next );
   if ( val1 == 0 && strcmp (next, "0") != 0)
   {
     printf ("Integer value expected\n");
     return;
   }


   if(val1 > network->getSize() || val1 - 1 < 0){
    printf("%d does not exist within airport network\n", val1);
	return;
   }
   
   if(network[val1 - 1].contains(val2) == 1){
   		printf("Cannot insert duplicate\n");
		return;
	}

   network[val1 - 1].push(val2, false);
   printf("Inserting from %d to %d \n", val1, val2);

 }
 
 void doDelete()
 {
  int val1 = 0;
  int val2 = 0;
  int i = 0;

   char* next = strtok (NULL, " \n\t");
   if ( next == NULL )
   {
     printf ("Integer value expected\n");
     return;
   }

   val1 = atoi ( next );
   if ( val1 == 0 && strcmp (next, "0") != 0)
   {
     printf ("Integer value expected\n");
     return;
   }

   if(val1 > network->getSize() || val1 - 1 < 0){
    printf("%d does not exist within airport network\n", val1);
	return;
   }

   if(val2 - 1 > network->getSize() || val2 - 1 < 0){
    printf("%d does not exist within airport network\n", val2);
	return;
   }

   network[val1 - 1].pop(val2);
   printf("Deleing from %d to %d\n", val1, val2);
 }
 
 void doList()
 {
   int i = 0;
   for(i = 0; i < network->getSize(); i++){
  	printf("%d: ", i+1);
	network[i].printList();
   }
  
 }
 
 void doFile()
 {
   // get a filename from the input
   char* fname = strtok (NULL, " \n\t");
   if ( fname == NULL )
   {
     printf ("Filename expected\n");
     return;
   }
   
   printf ("Performing the File command with file: %s\n", fname);
   
   // next steps:  (if any step fails: print an error message and return ) 
   //  1. verify the file name is not currently in use
   //  2. open the file using fopen creating a new instance of FILE*
   //  3. recursively call processCommandLoop() with this new instance of FILE* as the parameter
   //  4. close the file when processCommandLoop() returns

   if(fileNames.doesNameExist(fname) == 1){
	printf("Name currently exists\n");
	return;
   }

   fname.insertValue(fname);

   FILE *file;
   file = fopen("proj6data1.txt", "w");

   processCommandLoop(file);

   fclose(file);
    

 }


void depthFirstSearch_h(int x, int y){
	int i = 0;

	for(i = 0; i < network.getSize(); i++){
		network[i].markUnvisited();
	}

	if(dfs(x,y) == true){
		printf("You can get from airport %d to %d in one or more flights\n", x, y);
	}
	else{
		printf("You cannot get from airport %d to %d in one or more flights\n", x, y);

	}
}

bool dfs(int a, int b){
	Node c = network[a-1].headOfList();

	if(c == NULL){
		return false;
	}

	while(c != NULL){
		if(c.get_Elem() == b){
			return true;
		}
		if(c.get_Visited() == false){
			c.set_Visited(true);
			if(dfs(c.get_Elem(), b) == true){
				return true;
			}
		}
		c = c.get_Next();
	}
	return false;
} 

};

int main (int argc, char** argv)
{
  // set up the variable inFile to read from standard input
  FILE* inFile = stdin;

  // set up the data needed for the airport adjcency list
  TravelNetwork airportData;
   
  // call the method that reads and parses the input
  airportData.processCommandLoop (inFile);
   
  printf ("Goodbye\n");
  return 1;
 }

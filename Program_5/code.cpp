/*Name: James Iorgovan
*/

#include "proj5Tokens.h"
 
void printCommands();
 
void processExpression (Token inputToken, TokenReader *tr, int debugMode);
 
class myStack{
private:
    Token *darr;
    int size;
    int inUse;
public:
    
    myStack(){
        size = 2;
        darr = new Token[size];
        inUse = 0;
    }
    
    void push(Token t){
        Token *localArr = darr;
        int localInUse = inUse;
        
        if(localInUse == size){
            Token*temp;
            temp = new Token[size + 2];
            for(int i = 0; i < size; i++){
                temp[i] = localArr[i];
            }
            delete [] localArr;
            localArr = temp;
            size += 2;
        }
        localArr[localInUse] = t;
        localInUse++;
        
        inUse = localInUse;
        darr = localArr;
    }
    
    
    Token top(){
        return darr[inUse - 1];
    }
    
    void pop(){
        inUse = inUse -1;
    }
    
    bool isEmpty(){
        if(inUse == 0){
            return true;
        }
        else{
            return false;
        }
    }
};
 
 
 
 
int main(int argc, char *argv[])
{
	
	// Check command line arguments for debugMode
 
	static int debugMode = 0;
	for (int i = 0; i < argc; i++) {
		if (strcmp(argv[i], "-d") == 0) {
			debugMode = 1;
			printf("Debugging information...\n\n");
		}
	}
 
	Token inputToken;
	TokenReader tr;
 
	printf ("Starting expression evaluation program...\n");
	printf ("Enter expression: ");
 
 
	inputToken = tr.getNextToken ();
 
	while (inputToken.equalsType(QUIT) == false)
	{
		// Iterate through line. Obtain first token/
		if(inputToken.equalsType(HELP))
		{
			printCommands();
			tr.clearToEoln();
		}
		else if(inputToken.equalsType(ERROR))
		{
			printf ("Invalid Input - For a list of valid commands, type ?\n");
			tr.clearToEoln();
		}
		else if(inputToken.equalsType(EOLN))
		{
			printf ("Blank Line - Do Nothing\n");
			
		}
		else
		{
			processExpression(inputToken, &tr, debugMode);
		}
 
		printf ("Enter expression: ");
		inputToken = tr.getNextToken ();
	}
 
	printf ("Quitting program...\n");
	return 1;
}
 
 
 
 
void printCommands()
{
	printf ("The commands for this program are:\n\n");
	printf ("q - to quit the program\n");
	printf ("? - to list the accepted commands\n");
	printf ("or any infix mathematical expression using operators of (), *, /, +, -\n");
}
 
 
void processExpression (Token inputToken, TokenReader *tr, int debugMode)
{
    
    // Declare stack head and pointer
    myStack opStack =  myStack();
    myStack valStack = myStack();
    
    //Loop until the expression reaches end
    while (inputToken.equalsType(EOLN) == false)
    {
        // The expression contain a VALUE
        if (inputToken.equalsType(VALUE))
        {
            // debugMode iteration for obtaining value
            if(debugMode == 1){
                printf ("Val: %d, ", inputToken.getValue() );
            }
            // Push iteration of inputToken
            valStack.push(inputToken);
        }
        
        // Check for OPERATOR type
        else if (inputToken.equalsType(OPERATOR))
        {
            // debugMode iteration for obtaining operator
            if(debugMode == 1){
                printf ("OP: %c, ", inputToken.getOperator() );
            }
            
            if(inputToken.getOperator() == '('){
                opStack.push(inputToken);
            }
            
            
            if(inputToken.getOperator() == '+' || inputToken.getOperator() == '-'){
                while(opStack.isEmpty() != 1 &&
                      (opStack.top().getOperator() == '+' ||
                       opStack.top().getOperator() == '-' ||
                       opStack.top().getOperator() == '*' ||
                       opStack.top().getOperator() == '/')){
                          
                          Token op = opStack.top();
                          if(op.getOperator() != '+' && op.getOperator() != '-' &&
                             op.getOperator() != '*' && op.getOperator() != '/'){
                              
                              printf("Operator is not =, -, *, or /.\n");
                              // Return -999 if operator is not valid
                          }
                          opStack.pop();
                          int v2 = valStack.top().getValue();
                          valStack.pop();
                          int v1 = valStack.top().getValue();
                          valStack.pop();
                          
                          Token v3 = Token();
                          
                          int num = 0;
                          if(op.getOperator() == '+'){
                              num = v1 + v2;
                          }
                          if(op.getOperator() == '-'){
                              num = v1 - v2;
                          }
                          if(op.getOperator() == '*'){
                              num = v1 * v2;
                          }
                          if(op.getOperator() == '/'){
                              if(v2 == 0){
                                  printf("Cannot divide by 0.\n");
                                  // Return -999 if val is not divisable by 0
                              }
                              else{
                                  num = v1 / v2;
                              }
                          }
                          v3.setToValue(num);
                          valStack.push(v3);
 
                      }
                
                opStack.push(inputToken);
            }
	// Check that inputToken gets operator and compares it to valid option
            if(inputToken.getOperator() == '*' || inputToken.getOperator() == '/'){
                while(opStack.isEmpty() != 1 &&
                      (opStack.top().getOperator() == '*' ||
                       opStack.top().getOperator() == '/')){
                          Token op = opStack.top();
                          if(op.getOperator() != '+' && op.getOperator() != '-' &&
                             op.getOperator() != '*' && op.getOperator() != '/'){
                              
                              printf("Operator is not =, -, *, or /.\n");
                              // Return -999 if operator is not valid
                          }
                          opStack.pop();
                          int v2 = valStack.top().getValue();
                          valStack.pop();
                          int v1 = valStack.top().getValue();
                          valStack.pop();
                          
                          Token v3 = Token();
                          
                          int num = 0;
                          if(op.getOperator() == '+'){
                              num = v1 + v2;
                          }
                          if(op.getOperator() == '-'){
                              num = v1 - v2;
                          }
                          if(op.getOperator() == '*'){
                              num = v1 * v2;
                          }
                          if(op.getOperator() == '/'){
                              if(v2 == 0){
                                  printf("Cannot divide by 0.\n");
                                  // Return -999 if not divisable by 0
                              }
                              else{
                                  num = v1 / v2;
                              }
                          }
                          v3.setToValue(num);
                          valStack.push(v3);
 
                      }
                opStack.push(inputToken);
            }
            if(inputToken.getOperator() == ')'){
                while(opStack.isEmpty() != 1 && opStack.top().getOperator() != '('){
                    Token op = opStack.top();
                    if(op.getOperator() != '+' && op.getOperator() != '-' &&
                       op.getOperator() != '*' && op.getOperator() != '/'){
                        
                        printf("Operator is not =, -, *, or /\n");
                        //return -999;
                    }
                    opStack.pop();
                    int v2 = valStack.top().getValue();
                    valStack.pop();
                    int v1 = valStack.top().getValue();
                    valStack.pop();
                    
                    Token v3 = Token();
                    
                    int num = 0;
                    if(op.getOperator() == '+'){
                        num = v1 + v2;
                    }
                    if(op.getOperator() == '-'){
                        num = v1 - v2;
                    }
                    if(op.getOperator() == '*'){
                        num = v1 * v2;
                    }
                    if(op.getOperator() == '/'){
                        if(v2 == 0){
                            printf("Cannot divide by 0.\n");
                            // Return -999 if not divisible by 0.
                        }
                        else{
                            num = v1 / v2;
                        }
                    }
                    v3.setToValue(num);
                    valStack.push(v3);
 
                }	// Check if operator stack is empty, else pop stack starting from the top
                if(opStack.isEmpty() == 1){
                    printf("Operator stack is empty.\n");
                }
                else{
                    opStack.pop();
                }
            }
        }
        
        
        // Obtain next token input
        inputToken = tr->getNextToken ();
    }
    
    
    // If function reaches end, do this:
    while(opStack.isEmpty() != 1){
        Token op = opStack.top();
        if(op.getOperator() != '+' && op.getOperator() != '-' &&
           op.getOperator() != '*' && op.getOperator() != '/'){
            
            printf("Operator is not =, -, *, or /.\n");
            // Return -999 if not valid
        }
        opStack.pop();
        int v2 = valStack.top().getValue();
        valStack.pop();
        int v1 = valStack.top().getValue();
        valStack.pop();
        
        Token v3 = Token();
        
        int num = 0;
        if(op.getOperator() == '+'){
            num = v1 + v2;
        }
        if(op.getOperator() == '-'){
            num = v1 - v2;
        }
        if(op.getOperator() == '*'){
            num = v1 * v2;
        }
        if(op.getOperator() == '/'){
            if(v2 == 0){
                printf("Cannot divide by 0.\n");
                // Return -999 if not divisble by 0.
            }
            else{
                num = v1 / v2;
            }
        }
        v3.setToValue(num);
        valStack.push(v3);
 
    }
    if(valStack.isEmpty() == 1){
        printf("Error: value stack is not empty.\n");
    }
    else{
        printf("Top of the value stack: %d\n", valStack.top().getValue());
    }
    
    
    printf ("\n");
}

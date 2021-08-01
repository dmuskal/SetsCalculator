/*The following program serves as an interactive "pocket calculator" for operations on sets. The program receives input from the standard input and then proceeds to disect and analyze the input, and perform the specified commands. The sets that are operated on are defined (using typedef), and contain an integer array of size 4, which provides the set 128 bits to operate on the input value range of 0-127. The program then performs bit operations to execute commands such as read_set, print_set, union_set, intersect_set, sub_set, and symdiff_set on all the sets that are defined. The various sets are printed using the print_set command, and the program does not assume that the user input is valid, and will output a wide variety of error messages according to the user input.*/

#include "set.h" /*header file including constant definitions, definition of the set data type, and function prototypes of functions used throughout the program*/

/*The initialize function takes no input and has a void return type. The function calls the read_set function for each set with only a -1 for the contents of the second input of read_set which will empty the set. Therefore the intialize function initializes all the sets by emptying all the sets*/
void initialize();

set SETA, SETB, SETC, SETD, SETE, SETF; /*define all set variables used in program*/

int main(){
	
	int flagEOF; /*define flagEOF variable to store flag specifying if EOF has been detected or not*/
	char *ptrLine; /*define ptrLine char pointer storing user input in buffer*/
	int index; /*define index variable to increment through user input buffer*/
	flagEOF = NOEOF; /*set EOF flag to NOEOF*/
	
	initialize(); /*call initialize function to initialize all sets to empty sets*/

	while(1)
	{
		printf("Please enter command followed by the desired operands: \n"); /*prompts user input*/
		ptrLine = (char*)calloc(BUFSIZEINIT, sizeof(char)); /*dynamically allocates memory to store user input*/
		flagEOF = getLine(ptrLine); /*calls getLine function with ptrLine pointer as input to store user input into user input buffer and returns flagEOF as a flag to specify if EOF was detected or not*/
		index = ZEROINDEX; /*set index to zero*/
    		while(ptrLine[index] != '\0')
		{
        		printf("%c",ptrLine[index]); /*while end of user input not reached, print out currently indexed character*/
			index++; /*increment index*/
		}
		printf("\n"); /*print out new line after all of user input is printed out*/

		handleLine(ptrLine); /*ptrLine pointer of user input buffer passed to handleLine function to analyze and handle user input*/

		if(flagEOF == DETECTEDEOF)
		{
			printf("Error: Program stopped via EOF command... stop command should be used \n"); /*if flagEOF is set to DETECTEDEOF, print out error message that EOF was detected and break out of while loop*/
			break;
		}
	}

	return 0;
}

/*The initialize function takes no input and has a void return type. The function calls the read_set function for each set with only a -1 for the contents of the second input of read_set which will empty the set. Therefore the intialize function initializes all the sets by emptying all the sets*/
void initialize(){
	int emptyPtr;
	emptyPtr = ENDREADVALUE; /*sets emptyPtr to the ENDREADVALUE which will signal to read_set to end reading variables while the set is empty*/
	read_set(&SETA,&emptyPtr); /*sets SETA to an empty set*/
	read_set(&SETB,&emptyPtr); /*sets SETB to an empty set*/
	read_set(&SETC,&emptyPtr); /*sets SETC to an empty set*/
	read_set(&SETD,&emptyPtr); /*sets SETD to an empty set*/
	read_set(&SETE,&emptyPtr); /*sets SETE to an empty set*/
	read_set(&SETF,&emptyPtr); /*sets SETF to an empty set*/
}


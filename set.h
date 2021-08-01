#include <stdio.h> /*standard input output header file*/
#include <stdlib.h> /*standard library header file*/

#define NUMRANGE 128 /*constant for specifying size of value range in set (0-127)*/ 
#define BUFSIZEINIT 60 /*constant for specifying initial size of character buffer*/
#define INTBUFSIZEINIT 16 /*constant for specifying initial size of integer buffer*/
#define NOEOF 0 /*constant for specifying no EOF detection*/
#define DETECTEDEOF 1 /*constant for specifying EOF detection*/
#define MAXCOMMANDLEN 13 /*constant for specifying maximum length for command*/
#define MAXOPERANDLEN 4 /*constant for specifying maximum length of operand*/
#define ERROR 1 /*constant for specifying error*/
#define NOERROR 0 /*constant for specifying no error*/
#define SETRANGEMAX 127 /*maximum value that can be entered in read_set*/ 
#define SETRANGEMIN -1 /*minimum value that can be entered in read_set*/
#define ENDREADVALUE -1 /*value specifying final integer of read_set*/
#define BITSPERINT 32  /*number of bits in an integer (4 bytes)*/
#define VALUESPERROW 16  /*number of values per row to print in print_set*/
#define FLAGOFF 0 /*constant for specifying flag off*/
#define FLAGON 1 /*constant for specifying flag on*/
#define ZEROINDEX 0  /*constant for setting an index to zero*/
#define SKIPTWOINDICES 2 /*constant for skipping two indices*/
#define STRCMPTRUE 0 /*constant for checking if strcmp function returns true*/
#define NUMINTS 4 /*constant for specifying number of integers for 128 bits*/
#define BIT 1 /*constant for specifying one bit*/

/*definition of set data type using typedef containing an integer array of size 4 to provide 128 bits to store all numbers in the allowed value range*/
typedef struct set{
	int intArray[NUMINTS];
}set;

/*The getLine function has an input of a pointer to a char and returns an integer. For the ptrLine input, memory needs to be dynamically allocated for it prior to the function call, and in the function it is used as a buffer to store user input, and it returns an integer flag specifying if an EOF was detected or not*/
int getLine(char *ptrLine);

/*The handLine function has an input of a pointer to a char and has a void return type. The handleLine function serves as a very important part of the program as it takes the input, which serves as a buffer of the user input that was stored in the variable in the getLine function, and disects the function into command and operands, while checking for errors, and executes all the operations on the variables of type set*/
void handleLine(char *ptrLine);

/*The read_set function has inputs of a pointer to a set and pointer to an integer, and has a void return type. The selectedSet variable represents the set that will be operated on, and the ptrIntegers variable represents the integers that will be stored in the set. The function first clears any previous values in the set and then for the 128 available bits in the set, it stores a 1 corresponding to integers that were input by the user and a 0 elsewhere*/
void read_set(set *selectedSet, int *ptrIntegers); 

/*The print_set function has an input of a pointer to a set and has a void return type. The selectedSet variable represents the set that its contents will be printed out. The print_set function checks all the bits from the range set range of 0 to 127 and prints out the corresponding integer to bits with a 1 value. It prints out a maximum of 16 values per row and prints out a message specifying that the set is empty if no 1s were found in the set*/
void print_set(set *selectedSet);

/*The union_set function has inputs of three pointers to sets and has a void return type. The sets in the selectedSet1 and selectedSet2 variables are the sets that will be used to produce the contents of the set in selectedSet3. In the function, a temporary set variable is used in order to not overwrite values during the calculation in specific cases. The temporary set is set to all zeros and then any bit in selectedSet1 and/or selectedSet2 that is set to 1 is also set to 1 in the resulting temporary set. The selectedSet3 set is then cleared to all 0s and then all bits set to 1 in the temporary set are also set to 1 in the selectedSet3 set*/
void union_set(set *selectedSet1, set *selectedSet2, set *selectedSet3);

/*The intersect_set function has inputs of three pointers to sets and has a void return type. The sets in the selectedSet1 and selectedSet2 variables are the sets that will be used to produce the contents of the set in selectedSet3. In the function, a temporary set variable is used in order to not overwrite values during the calculation in specific cases. The temporary set is set to all zeros and then any bit in selectedSet1 AND selectedSet2 that is set to 1 is also set to 1 in the resulting temporary set. The selectedSet3 set is then cleared to all 0s and then all bits set to 1 in the temporary set are also set to 1 in the selectedSet3 set*/
void intersect_set(set *selectedSet1, set *selectedSet2, set *selectedSet3);

/*The sub_set function has inputs of three pointers to sets and has a void return type. The sets in the selectedSet1 and selectedSet2 variables are the sets that will be used to produce the contents of the set in selectedSet3. In the function, a temporary set variable is used in order to not overwrite values during the calculation in specific cases. The temporary set is set to all zeros and then any bit in selectedSet1 but not in selectedSet2 that is set to 1 is also set to 1 in the resulting temporary set. The selectedSet3 set is then cleared to all 0s and then all bits set to 1 in the temporary set are also set to 1 in the selectedSet3 set*/
void sub_set(set *selectedSet1, set *selectedSet2, set *selectedSet3);

/*The symdiff_set function has inputs of three pointers to sets and has a void return type. The sets in the selectedSet1 and selectedSet2 variables are the sets that will be used to produce the contents of the set in selectedSet3. In the function, a temporary set variable is used in order to not overwrite values during the calculation in specific cases. The temporary set is set to all zeros and then any bit in selectedSet1 OR (NOT AND) selectedSet2 that is set to 1 is also set to 1 in the resulting temporary set. The selectedSet3 set is then cleared to all 0s and then all bits set to 1 in the temporary set are also set to 1 in the selectedSet3 set*/
void symdiff_set(set *selectedSet1, set *selectedSet2, set *selectedSet3);

/*The stop function takes no inputs and has a void return type. The function simply calls exit(0) once it is called and terminates the program*/
void stop();

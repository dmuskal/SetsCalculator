#include "set.h" /*header file including constant definitions, definition of the set data type, and function prototypes of functions used throughout the program*/

/*The read_set function has inputs of a pointer to a set and pointer to an integer, and has a void return type. The selectedSet variable represents the set that will be operated on, and the ptrIntegers variable represents the integers that will be stored in the set. The function first clears any previous values in the set and then for the 128 available bits in the set, it stores a 1 corresponding to integers that were input by the user and a 0 elsewhere*/
void read_set(set *selectedSet, int *ptrIntegers){
	int i;
	/*Sets all bits in the set to 0*/
	for(i=ZEROINDEX; i < NUMRANGE; i++){
		selectedSet->intArray[i/BITSPERINT] &= ~(BIT << (i%BITSPERINT));
	}
	i=ZEROINDEX;
	/*Sets bits corresponding to integers in ptrIntegers buffer to 1 until ENDREADVALUE of -1 detected*/
	while(ptrIntegers[i] != ENDREADVALUE){
		selectedSet->intArray[ptrIntegers[i]/BITSPERINT] |= BIT << (ptrIntegers[i] % BITSPERINT);
		i++;
	}
}

/*The print_set function has an input of a pointer to a set and has a void return type. The selectedSet variable represents the set that its contents will be printed out. The print_set function checks all the bits from the range set range of 0 to 127 and prints out the corresponding integer to bits with a 1 value. It prints out a maximum of 16 values per row and prints out a message specifying that the set is empty if no 1s were found in the set*/
void print_set(set *selectedSet){
	int i;
	int printCounter;
	printCounter = ZEROINDEX;
	/*iterates over bit range of 0 to 127 to print out all integers with corresponding bit set to 1*/
	for(i=ZEROINDEX; i < NUMRANGE; i++){
		if ( (selectedSet->intArray[i/BITSPERINT] & (BIT << (i%BITSPERINT) ) ) ){    
			printf("%d ", i);
			printCounter++;
			if((printCounter % VALUESPERROW == 0) && (printCounter != ZEROINDEX)){
				printf("\n"); /*prints new line every time 16 values have been printed*/
			}
		}
	}
	if(printCounter == ZEROINDEX){
		printf("The set is empty"); /*prints messsage if set is empty*/
	}
	printf("\n");
}

/*The union_set function has inputs of three pointers to sets and has a void return type. The sets in the selectedSet1 and selectedSet2 variables are the sets that will be used to produce the contents of the set in selectedSet3. In the function, a temporary set variable is used in order to not overwrite values during the calculation in specific cases. The temporary set is set to all zeros and then any bit in selectedSet1 and/or selectedSet2 that is set to 1 is also set to 1 in the resulting temporary set. The selectedSet3 set is then cleared to all 0s and then all bits set to 1 in the temporary set are also set to 1 in the selectedSet3 set*/
void union_set(set *selectedSet1, set *selectedSet2, set *selectedSet3){
	set tmpSet;
	int i;
	/*Sets all bits in tmpSet to 0*/
	for(i=ZEROINDEX; i < NUMRANGE; i++){
		tmpSet.intArray[i/BITSPERINT] &= ~(BIT << (i%BITSPERINT));
	}
	/*Iterates over bit range of 0 to 127 to insert 1s in tmpSet where selectedSet1 and/or selectedSet2 bit is set to 1*/
	for(i=ZEROINDEX; i < NUMRANGE; i++){
		if ( (selectedSet1->intArray[i/BITSPERINT] & (BIT << (i%BITSPERINT))) || (selectedSet2->intArray[i/BITSPERINT] & (BIT << (i%BITSPERINT)))){
			tmpSet.intArray[i/BITSPERINT] |= BIT << (i%BITSPERINT);
		}
	}
	/*Sets all bits in selectedSet3 set to 0*/
	for(i=ZEROINDEX; i < NUMRANGE; i++){
		selectedSet3->intArray[i/BITSPERINT] &= ~(BIT << (i%BITSPERINT));
	}
	/*Iterates over bit range of 0 to 127 to insert 1s in bits in selectedSet3 set where 1s are located in tmpSet*/
	for(i=ZEROINDEX; i < NUMRANGE; i++){
		if ( (tmpSet.intArray[i/BITSPERINT] & (BIT << (i%BITSPERINT))) ){
			selectedSet3->intArray[i/BITSPERINT] |= BIT << (i%BITSPERINT);
		}
	}
}

/*The intersect_set function has inputs of three pointers to sets and has a void return type. The sets in the selectedSet1 and selectedSet2 variables are the sets that will be used to produce the contents of the set in selectedSet3. In the function, a temporary set variable is used in order to not overwrite values during the calculation in specific cases. The temporary set is set to all zeros and then any bit in selectedSet1 AND selectedSet2 that is set to 1 is also set to 1 in the resulting temporary set. The selectedSet3 set is then cleared to all 0s and then all bits set to 1 in the temporary set are also set to 1 in the selectedSet3 set*/
void intersect_set(set *selectedSet1, set *selectedSet2, set *selectedSet3){
	set tmpSet;
	int i;
	/*Sets all bits in the set to 0*/
	for(i=ZEROINDEX; i < NUMRANGE; i++){
		tmpSet.intArray[i/BITSPERINT] &= ~(BIT << (i%BITSPERINT));
	}
	/*Iterates over bit range of 0 to 127 to insert 1s in tmpSet where selectedSet1 AND selectedSet2 bit is set to 1*/
	for(i=ZEROINDEX; i < NUMRANGE; i++){
		if ( (selectedSet1->intArray[i/BITSPERINT] & (BIT << (i%BITSPERINT))) && (selectedSet2->intArray[i/BITSPERINT] & (BIT << (i%BITSPERINT)))){
			tmpSet.intArray[i/BITSPERINT] |= BIT << (i%BITSPERINT);
		}
	}
	/*Sets all bits in the set to 0*/
	for(i=ZEROINDEX; i < NUMRANGE; i++){
		selectedSet3->intArray[i/BITSPERINT] &= ~(BIT << (i%BITSPERINT));
	}
	/*Iterates over bit range of 128 to insert 1s in bits in selectedSet3 set where 1s are located in tmpSet*/
	for(i=ZEROINDEX; i < NUMRANGE; i++){
		if ( (tmpSet.intArray[i/BITSPERINT] & (BIT << (i%BITSPERINT))) ){
			selectedSet3->intArray[i/BITSPERINT] |= BIT << (i%BITSPERINT);
		}
	}

}

/*The sub_set function has inputs of three pointers to sets and has a void return type. The sets in the selectedSet1 and selectedSet2 variables are the sets that will be used to produce the contents of the set in selectedSet3. In the function, a temporary set variable is used in order to not overwrite values during the calculation in specific cases. The temporary set is set to all zeros and then any bit in selectedSet1 but not in selectedSet2 that is set to 1 is also set to 1 in the resulting temporary set. The selectedSet3 set is then cleared to all 0s and then all bits set to 1 in the temporary set are also set to 1 in the selectedSet3 set*/
void sub_set(set *selectedSet1, set *selectedSet2, set *selectedSet3){
	set tmpSet;
	int i;
	/*Sets all bits in the set to 0*/
	for(i=ZEROINDEX; i < NUMRANGE; i++){
		tmpSet.intArray[i/BITSPERINT] &= ~(BIT << (i%BITSPERINT));
	}
	/*Iterates over bit range of 0 to 127 to insert 1s in tmpSet where selectedSet1 but not selectedSet2 bit is set to 1*/
	for(i=ZEROINDEX; i < NUMRANGE; i++){
		if ( (selectedSet1->intArray[i/BITSPERINT] & (BIT << (i%BITSPERINT))) && !(selectedSet2->intArray[i/BITSPERINT] & (BIT << (i%BITSPERINT)))){
			tmpSet.intArray[i/BITSPERINT] |= BIT << (i%BITSPERINT);
		}
	}
	/*Sets all bits in the set to 0*/
	for(i=ZEROINDEX; i < NUMRANGE; i++){
		selectedSet3->intArray[i/BITSPERINT] &= ~(BIT << (i%BITSPERINT));
	}
	/*Iterates over bit range of 128 to insert 1s in bits in selectedSet3 set where 1s are located in tmpSet*/
	for(i=ZEROINDEX; i < NUMRANGE; i++){
		if ( (tmpSet.intArray[i/BITSPERINT] & (BIT << (i%BITSPERINT))) ){
			selectedSet3->intArray[i/BITSPERINT] |= BIT << (i%BITSPERINT);
		}
	}

}

/*The symdiff_set function has inputs of three pointers to sets and has a void return type. The sets in the selectedSet1 and selectedSet2 variables are the sets that will be used to produce the contents of the set in selectedSet3. In the function, a temporary set variable is used in order to not overwrite values during the calculation in specific cases. The temporary set is set to all zeros and then any bit in selectedSet1 OR (NOT AND) selectedSet2 that is set to 1 is also set to 1 in the resulting temporary set. The selectedSet3 set is then cleared to all 0s and then all bits set to 1 in the temporary set are also set to 1 in the selectedSet3 set*/
void symdiff_set(set *selectedSet1, set *selectedSet2, set *selectedSet3){
	set tmpSet;
	int i;
	/*Sets all bits in the set to 0*/
	for(i=ZEROINDEX; i < NUMRANGE; i++){
		tmpSet.intArray[i/BITSPERINT] &= ~(BIT << (i%BITSPERINT));
	}
	/*Iterates over bit range of 0 to 127 to insert 1s in tmpSet where selectedSet1 OR (NOT AND) selectedSet2 bit is set to 1*/
	for(i=ZEROINDEX; i < NUMRANGE; i++){
		if ( ((selectedSet1->intArray[i/BITSPERINT] & (BIT << (i%BITSPERINT))) && !(selectedSet2->intArray[i/BITSPERINT] & (BIT << (i%BITSPERINT)))) || (!(selectedSet1->intArray[i/BITSPERINT] & (BIT << (i%BITSPERINT))) && (selectedSet2->intArray[i/BITSPERINT] & (BIT << (i%BITSPERINT))))){
			tmpSet.intArray[i/BITSPERINT] |= BIT << (i%BITSPERINT);
		}
	}
	/*Sets all bits in the set to 0*/
	for(i=ZEROINDEX; i < NUMRANGE; i++){
		selectedSet3->intArray[i/BITSPERINT] &= ~(BIT << (i%BITSPERINT));
	}
	/*Iterates over bit range of 128 to insert 1s in bits in selectedSet3 set where 1s are located in tmpSet*/
	for(i=ZEROINDEX; i < NUMRANGE; i++){
		if ( (tmpSet.intArray[i/BITSPERINT] & (BIT << (i%BITSPERINT))) ){
			selectedSet3->intArray[i/BITSPERINT] |= BIT << (i%BITSPERINT);
		}
	}

}

/*The stop function takes no inputs and has a void return type. The function simply calls exit(0) once it is called and terminates the program*/
void stop(){
	exit(0);
}

#include <string.h> /*string header file*/
#include "set.h" /*header file including constant definitions, definition of the set data type, and function prototypes of functions used throughout the program*/

extern set SETA, SETB, SETC, SETD, SETE, SETF; /*declaration of all set variables used in program*/

/*The checkOperand function takes an input of pointer to char and returns a pointer to set. The function receives a string of the operand name and uses strcmp to check which operand was selected and returns the address of the selected set (operand)*/
set *checkOperand(char *ptrOperand){
	if(strcmp("SETA", ptrOperand) == STRCMPTRUE){
		return &SETA; /*if the entered operand is SETA then return the address of SETA*/
	}
	else if(strcmp("SETB", ptrOperand) == STRCMPTRUE){
		return &SETB; /*if the entered operand is SETB then return the address of SETB*/
	}
	else if(strcmp("SETC", ptrOperand) == STRCMPTRUE){
		return &SETC; /*if the entered operand is SETC then return the address of SETC*/
	}
	else if(strcmp("SETD", ptrOperand) == STRCMPTRUE){
		return &SETD; /*if the entered operand is SETD then return the address of SETD*/
	}
	else if(strcmp("SETE", ptrOperand) == STRCMPTRUE){
		return &SETE; /*if the entered operand is SETE then return the address of SETE*/
	}
	else{
		return &SETF; /*if the entered operand is SETF then return the address of SETF*/
	}
}

/*The validOperand function takes an input of pointer to char and has an int return type. The input points to a string of the operand name and the function uses strcmp to check if the input is equal to any of the possible set names, and returns and integer flag specify NOERROR if it is a valid operand and ERROR if it is an invalid operand*/
int validOperand(char *ptrOperand){
	if(strcmp("SETA", ptrOperand) == STRCMPTRUE){
		return NOERROR; /*if entered operand is equal to string SETA then return NOERROR flag*/
	}
	else if(strcmp("SETB", ptrOperand) == STRCMPTRUE){
		return NOERROR; /*if entered operand is equal to string SETB then return NOERROR flag*/
	}
	else if(strcmp("SETC", ptrOperand) == STRCMPTRUE){
		return NOERROR; /*if entered operand is equal to string SETC then return NOERROR flag*/
	}
	else if(strcmp("SETD", ptrOperand) == STRCMPTRUE){
		return NOERROR; /*if entered operand is equal to string SETD then return NOERROR flag*/
	}
	else if(strcmp("SETE", ptrOperand) == STRCMPTRUE){
		return NOERROR; /*if entered operand is equal to string SETE then return NOERROR flag*/
	}
	else if(strcmp("SETF", ptrOperand) == STRCMPTRUE){
		return NOERROR; /*if entered operand is equal to string SETF then return NOERROR flag*/
	}
	else{
		return ERROR; /*if entered operand is not equal to any of the set names then return ERROR flag*/
	}
}

/*The getLine function has an input of a pointer to a char and returns an integer. For the ptrLine input, memory needs to be dynamically allocated for it prior to the function call, and in the function it is used as a buffer to store user input, and it returns an integer flag specifying if an EOF was detected or not*/
int getLine(char *ptrLine){
	int inputVal; /*int used to store getchar from user*/
	char *tmpPtr; /*temporary pointer used for realloc of ptrLine and check for memory allocation error*/
	int bufSize; /*int used to store size of input buffer*/
	int index; /*int used to index through buffer of input characters*/
	int flagEOF; /*int used for flag of EOF detection*/

	flagEOF = NOEOF; /*set EOF flag to no EOF detected*/
	bufSize = BUFSIZEINIT; /*set buffer size to intial size*/
	index = ZEROINDEX; /*set intial index to zero*/
	while(1)
	{
		/*if condition to check if buffer is full*/
		if(index >= bufSize)
		{
			bufSize = bufSize + BUFSIZEINIT; /*increase buffer size by intial buffer size*/
			tmpPtr = realloc(ptrLine, bufSize*sizeof(char)); /*realloc to dynamically allocate more memory*/
			if(!tmpPtr)
			{
				printf("Memory cannot be allocated"); /*if realloc fails to allocate more memory return error message and exit*/
				exit(0);
			}
			ptrLine = tmpPtr; /*return address of temporary pointer to original pointer to buffer*/
		}
		inputVal = getchar(); /*store input from user from getchar() into inputVal variable*/
		if(inputVal == EOF)
		{
			flagEOF = DETECTEDEOF; /*break from while loop if EOF detected and return flag that EOF was detected*/
			break;
		}
		if(inputVal == '\n')
		{
			break; /*break from while loop if user entered new line*/
		}
		ptrLine[index] = inputVal; /*set current index of buffer equal to the user input*/
		index++; /*increment the index by 1*/
	}
	return flagEOF; /*return if EOF was detected or not*/
}

/*The handLine function has an input of a pointer to a char and has a void return type. The handleLine function serves as a very important part of the program as it takes the input, which serves as a buffer of the user input that was stored in the variable in the getLine function, and disects the function into command and operands, while checking for errors, and executes all the operations on the variables of type set*/
void handleLine(char *ptrLine){
	int inputIndex, commandIndex, commandFlag, operandIndex, operandFlag, intIndex, commaFlag, intBufSize, operandErrorFlag, outOfRangeFlag, extraneousTextFlag, notIntegerFlag, consecutiveCommaFlag, missingCommaFlag, whiteSpaceFlag, illegalCommaFlag; /*define all integer index and flag variables*/
	char *ptrCommand; /*define pointer to user selected command*/
	char *ptrOperand; /*define pointer to user selected operand*/
	int *ptrIntegers; /*define pointer to user selected integers*/
	int *tmpPtr;  /*define temporary pointer used for dyanmic memory allocation error handling*/
	set *selectedSet1;  /*define pointer to first selected set*/
	set *selectedSet2;  /*define pointer to second selected set*/
	set *selectedSet3;  /*define pointer to third selected set*/
	commandFlag = FLAGOFF; /*set flag of command entered to off*/
	operandFlag = FLAGOFF;   /*set flag of operand entered to off*/
	commaFlag = FLAGOFF; /*set flag of comma entered to off*/
	whiteSpaceFlag = FLAGOFF; /*set flag of white space entered to off*/
	inputIndex = ZEROINDEX; /*set input index to zero*/
	commandIndex = ZEROINDEX; /*set command index to zero*/
	operandIndex = ZEROINDEX; /*set operand index to zero*/
	intIndex = ZEROINDEX;  /*set int index to zero*/
	operandErrorFlag = NOERROR;  /*set operand error flag to NOERROR*/
	outOfRangeFlag = NOERROR;  /*set out of range error flag to NOERROR*/
	extraneousTextFlag = NOERROR;  /*set extraneous text error flag to NOERROR*/ 
	notIntegerFlag = NOERROR;  /*set not integer error flag to NOERROR*/
	consecutiveCommaFlag = NOERROR;  /*set consecutive comma error flag to NOERROR*/
	missingCommaFlag = NOERROR;  /*set missing comma error flag to NOERROR*/
	illegalCommaFlag = NOERROR;  /*set illegal comma error flag to NOERROR*/

	intBufSize = INTBUFSIZEINIT; /*set initial size of integer buffer*/

	/*while index has not reached end of input*/
	while(ptrLine[inputIndex] != '\0'){
		/*printf("%c", ptrLine[index]);*/
		/*if input is not white space and command has not yet been received*/
		if(ptrLine[inputIndex] != ' ' && ptrLine[inputIndex] != '\t' && commandFlag == FLAGOFF){
			ptrCommand = (char*)calloc(MAXCOMMANDLEN, sizeof(char)); /*dynamically allocate memory to store command*/
			/*while input is not white space and command character limit not exceeded*/
			while(ptrLine[inputIndex] != ' ' && ptrLine[inputIndex] != '\t' && commandIndex < MAXCOMMANDLEN){
				if(ptrLine[inputIndex] == ','){
					illegalCommaFlag = ERROR; /*if comma entered set illegal comma flag to ERROR*/
				}
				ptrCommand[commandIndex] = ptrLine[inputIndex]; /*set current index of command equal to current index of user input*/
				commandIndex++; /*increment command index*/
				inputIndex++; /*increment input index*/
			}
			commandFlag = FLAGON; /*set command flag to FLAGON to specify that command has been received*/
			if(illegalCommaFlag == ERROR){
				printf("Illegal comma \n"); /*if illegal comma flag has been set to ERROR print error message and break out of while loop*/
				break;
			}
		}
		if(strcmp("stop", ptrCommand) == STRCMPTRUE){
			stop(); /*if stop command has been entered, enter stop function*/
		}
		/*if input is not white space and operand has not yet been received*/
		if(ptrLine[inputIndex] != ' ' && ptrLine[inputIndex] != '\t' && operandFlag == FLAGOFF){
			if(ptrLine[inputIndex] == ','){
				printf("Illegal comma \n"); /*if comma entered print illegal comma error message and break out of while loop*/
				break;
			}
			/*if command is read_set command*/
			if(strcmp("read_set", ptrCommand) == STRCMPTRUE){
				ptrOperand = (char*)calloc(MAXOPERANDLEN, sizeof(char)); /*dynamically allocate memory to store entered operand*/
				/*whie input is not white space and index is less than maximum operand length and end of input has not yet been reached*/
				while(ptrLine[inputIndex] != ' ' && ptrLine[inputIndex] != '\t' && operandIndex < MAXOPERANDLEN && ptrLine[inputIndex] != '\0'){
					ptrOperand[operandIndex] = ptrLine[inputIndex]; /*set currently indexed operand value equal to currently indexed input value*/
					operandIndex++; /*increment operand index*/
					inputIndex++; /*increment input index*/
				}
				operandErrorFlag = validOperand(ptrOperand); /*check if valide operand was entered*/
				if(operandErrorFlag == ERROR){
					printf("Undefined set name \n"); /*if operand is invalid print error message and break out of loop*/
					break;
				}
				/*while end of input has not been reached*/
				while(ptrLine[inputIndex] != '\0'){
					if(ptrLine[inputIndex] == ' ' || ptrLine[inputIndex] == '\t'){
						inputIndex++; /*if input is white space increment input index and continue back to top of loop*/
						continue;
					}
					if(ptrLine[inputIndex] == ','){
						break; /*if comma entered, break out of loop*/
					}
					else{
						missingCommaFlag = ERROR; /*if no comma entered set missing comma flag to error and break out of loop*/
						break; 
					}
				}
				if(missingCommaFlag == ERROR){
					printf("Missing comma \n"); /*if missing comma flag set to ERROR, print error message and break out of loop*/
					break;
				}
				operandFlag = FLAGON; /*set operand flag to FLAGON*/
				ptrIntegers = (int*)calloc(INTBUFSIZEINIT, sizeof(int)); /*dynamically allocate memory to store integer values*/
				/*while end of input has not been reached*/
				while(ptrLine[inputIndex] != '\0'){
					if(ptrLine[inputIndex] == ' ' || ptrLine[inputIndex] == '\t'){
						inputIndex++; /*if input is white space increment input index and continue back to top of loop*/
						continue;
					}
					if(ptrIntegers[intIndex] == ENDREADVALUE){
						extraneousTextFlag = ERROR; /*if input is equal to ENDREADVALUE of -1 set extraneous text flag to ERROR and break out of loop*/
						break;
					}
					if(ptrLine[inputIndex] == ','){
						if(commaFlag == FLAGON){
							consecutiveCommaFlag = ERROR; /*if comma entered and commaFlag already set to FLAGON, set consecutive comma flag to ERROR and break out of loop*/
							break;
						}
						commaFlag = FLAGON; /*if comma entered set comma flag to FLAGON*/
						inputIndex++; /*increment input index*/
						continue;
					}
					if((ptrLine[inputIndex] >= 'a' && ptrLine[inputIndex] <= 'z') || (ptrLine[inputIndex] >= 'A' && ptrLine[inputIndex] <= 'Z') || ptrLine[inputIndex] == '.'){
						notIntegerFlag = ERROR; /*if input is not an integer, set not integer flag to ERROR and break out of loop*/
						break;
					}
					/*if comma flag is on from comma previously entered enter condition*/
					if(commaFlag == FLAGON){
						if(intIndex >= intBufSize){
							intBufSize = intBufSize + INTBUFSIZEINIT; /*if integer index is greater than integer buffer size, increase integer buffer size by the intial size*/
							tmpPtr = (int*)realloc(ptrIntegers, intBufSize*sizeof(int)); /*use realloc to dyanmically allocate more memory to store more integers entered by user*/ 
							if(!tmpPtr){
								printf("Failed to allocate memory"); /*if realloc failed to allocate memory, then print error message and exit from program*/
								exit(0);
							}
							ptrIntegers = tmpPtr; /*return address of temporary pointer to original pointer to integer buffer*/
						}
						ptrIntegers[intIndex] = atoi(&(ptrLine[inputIndex])); /*converts currently indexed user input to integer and stores in the integer buffer*/
						if(ptrIntegers[intIndex] == ENDREADVALUE){
							inputIndex = inputIndex + SKIPTWOINDICES; /*if integer value is equal to the ENDREADVALUE of -1, then increment inputIndex by two (past the -1 input (two chars))*/
							commaFlag = FLAGOFF; /*sets comma flag to FLAGOFF*/
							continue; 
						}
						if(ptrIntegers[intIndex] > SETRANGEMAX || ptrIntegers[intIndex] < SETRANGEMIN){
							outOfRangeFlag = ERROR; /*if integer entered by user is out of the -1 to 127 range then set out of range flag to ERROR and break out of while loop*/
							break;
						}
						intIndex++; /*increment intIndex*/
						inputIndex++; /*increment inputIndex*/
						commaFlag = FLAGOFF; /*set comma flag to FLAGOFF*/
						continue;
					}
					inputIndex++; /*increment inputIndex*/
				}
				if(outOfRangeFlag == ERROR){
					printf("Invalid set member – value out of range \n"); /*if out of range flag is set to ERROR print error message and break out of loop*/
					break;
				}
				if(extraneousTextFlag == ERROR){
					printf("Extraneous text after end of command \n"); /*if extraneous text flag is set to ERROR print error message and break out of loop*/
					break;
				}
				if(consecutiveCommaFlag == ERROR){
					printf("Multiple consecutive commas \n"); /*if consecutive comma flag is set to ERROR print error message and break out of loop*/
					break;
				}
				if(notIntegerFlag == ERROR){
					printf("Invalid set member – not an integer \n"); /*if not integer flag is set to ERROR print error message and break out of loop*/
					break;
				}
				if(ptrIntegers[intIndex] != ENDREADVALUE){
					printf("List of set members is not terminated correctly \n"); /*if final integer value is not equal to the ENDREADVALUE of -1, print error message and break out of loop*/
					break;
				}
				operandErrorFlag = validOperand(ptrOperand); /*check to see if entered operand is valid operand*/
				if(operandErrorFlag == ERROR){
					printf("Undefined set name \n"); /*if operand error flag is set to ERROR print error message and break out of loop*/
					break;
				}
				selectedSet1 = checkOperand(ptrOperand); /*uses checkOperand function to return the address of the set that is input as a string in ptrOperand*/
				read_set(selectedSet1, ptrIntegers); /*calls read_set function with the user selected set and integer values as inputs*/
				free(ptrOperand); /*frees the ptrOperand pointer*/
			}
			/*if command is print_set command*/
			else if(strcmp("print_set", ptrCommand) == STRCMPTRUE){
				ptrOperand = (char*)calloc(MAXOPERANDLEN, sizeof(char)); /*dynamically allocate memory to store entered operand*/
				while(ptrLine[inputIndex] != '\0'){
					if(ptrLine[inputIndex] == ' ' || ptrLine[inputIndex] == '\t'){
						inputIndex++; /*if input is white space increment input index and continue back to top of loop*/
						continue;
					}
					if(operandIndex >= MAXOPERANDLEN){
						extraneousTextFlag = ERROR; /*if operandIndex is greater than or equal to the maximum length of operand than set the extraneous text flag to ERROR and break out of loop*/
						break;
					}
					ptrOperand[operandIndex] = ptrLine[inputIndex]; /*set currently indexed operand value equal to currently indexed input value*/
					operandIndex++; /*increment operandIndex*/
					inputIndex++; /*increment inputIndex*/
				}
				operandFlag = FLAGON; /*set operandFlag to FLAGON*/
				operandErrorFlag = validOperand(ptrOperand); /*check to see if entered operand is valid operand*/
				if(operandErrorFlag == ERROR){
					printf("Undefined set name \n"); /*if operand error flag is set to ERROR print error message and break out of loop*/
					break;
				}
				if(extraneousTextFlag == ERROR){
					printf("Extraneous text after end of command \n"); /*if extraneous text flag is set to ERROR print error message and break out of loop*/
					break;
				}
				selectedSet1 = checkOperand(ptrOperand); /*uses checkOperand function to return the address of the set that is input as a string in ptrOperand*/
				print_set(selectedSet1); /*call print_set function with the user selected set as input*/
				free(ptrOperand); /*frees the ptrOperand pointer*/
			}
			/*if command is union_set command or intersect_set or sub_set or symdiff_set*/
			else if((strcmp("union_set", ptrCommand) == STRCMPTRUE) || (strcmp("intersect_set", ptrCommand) == STRCMPTRUE) || (strcmp("sub_set", ptrCommand) == STRCMPTRUE) || (strcmp("symdiff_set", ptrCommand) == STRCMPTRUE)){
				char *ptrOperand1; /*define pointer to first user selected operand*/
				char *ptrOperand2; /*define pointer to second user selected operand*/
				char *ptrOperand3; /*define pointer to third user selected operand*/
				ptrOperand1 = (char*)calloc(MAXOPERANDLEN, sizeof(char)); /*dynamically allocate memory to store entered first operand*/
				while(ptrLine[inputIndex] != '\0'){
					if(ptrLine[inputIndex] == ' ' || ptrLine[inputIndex] == '\t'){
						inputIndex++; /*if input is white space increment input index, set white space flag to FLAGON and continue back to top of loop*/
						whiteSpaceFlag = FLAGON;
						continue;
					}
					/*if operandIndex is greater than or equal to maximum operand length*/
					if(operandIndex >= MAXOPERANDLEN){
						if(ptrLine[inputIndex] != ','){
							if(whiteSpaceFlag == FLAGON){
								missingCommaFlag = ERROR; /*if input is not a commag and the white space flag is set to FLAGON, set missing commag flag to ERROR*/
							}
							else{
								operandErrorFlag = ERROR; /*if input is not a comma and the white space flag is not set to FLAGON, set operand error flag to ERROR*/
							}
							
						}
						break;
					}
					whiteSpaceFlag = FLAGOFF; /*set white space flag to off*/
					ptrOperand1[operandIndex] = ptrLine[inputIndex]; /*set currently indexed operand value equal to currently indexed input value*/
					operandIndex++; /*increment operandIndex*/
					inputIndex++; /*increment inputIndex*/
				}
				if(missingCommaFlag == ERROR){
					printf("Missing comma \n"); /*if missing comma flag is set to ERROR print error message and break out of loop*/
					break;
				}
				if(operandErrorFlag == ERROR){
					printf("Undefined set name \n"); /*if operand error flag is set to ERROR print error message and break out of loop*/
					break;
				}
				whiteSpaceFlag = FLAGOFF; /*set white space flag to FLAGOFF*/
				operandFlag = FLAGON; /*set operand flag to FLAGON*/
				operandIndex = ZEROINDEX; /*set operand index to zero index*/
				operandErrorFlag = validOperand(ptrOperand1); /*check to see if entered operand is valid operand*/
				if(operandErrorFlag == ERROR){
					printf("Undefined set name \n"); /*if operand error flag is set to ERROR print error message and break out of loop*/
					break;
				}
				ptrOperand2 = (char*)calloc(MAXOPERANDLEN, sizeof(char)); /*dynamically allocate memory to store entered second operand*/
				while(ptrLine[inputIndex] != '\0'){
					if(missingCommaFlag == ERROR || operandErrorFlag == ERROR){
						break; /*break out of loop if missing comma flag or operand error flag set to ERROR*/
					}
					if(ptrLine[inputIndex] == ' ' || ptrLine[inputIndex] == '\t'){
						inputIndex++; /*if input is white space increment input index and continue back to top of loop*/
						continue;
					}
					if(ptrLine[inputIndex] == ','){
						if(commaFlag == FLAGON){
							consecutiveCommaFlag = ERROR; /*if input is comma and comma flag is already set to FLAGON, set consecutive commag flag to ERROR and break out of loop*/
							break;
						}
						commaFlag = FLAGON; /*if input is comma set comma flag to FLAGON*/
						inputIndex++; /*increment inputIndex*/
						continue;
					}
					/*if comma flag is set to FLAGON*/
					if(commaFlag == FLAGON){
						/*while end of input not reached*/
						while(ptrLine[inputIndex] != '\0'){
							if(ptrLine[inputIndex] == ' ' || ptrLine[inputIndex] == '\t'){
								whiteSpaceFlag = FLAGON; /*if input is white space, set white space flag to FLAGON, increment input index, and continue back to top of loop*/
								inputIndex++;
								continue;
							}
							/*if operandIndex is greater than or equal to maximum operand length*/
							if(operandIndex >= MAXOPERANDLEN){
								if(ptrLine[inputIndex] != ','){
									if(whiteSpaceFlag == FLAGON){
										missingCommaFlag = ERROR; /*if input is not a comma and white space flag is set to FLAGON, set missing comma flag to ERROR*/
									}
									else{
										operandErrorFlag = ERROR; /*if input is not a comma and white space flag is not set to FLAGON, set operand error flag to ERROR*/
									}
							
								}
								break;

							}
							whiteSpaceFlag = FLAGOFF; /*set white space flag to FLAGOFF*/
							ptrOperand2[operandIndex] = ptrLine[inputIndex]; /*set currently indexed operand value equal to currently indexed input value*/
							operandIndex++; /*increment operandIndex*/
							inputIndex++; /*increment inputIndex*/
							}
						commaFlag = FLAGOFF; /*set comma flag to FLAGOFF*/
						break;
					}
					inputIndex++;
				}
				operandIndex = ZEROINDEX; /*set operandIndex to zero index*/
				if(operandErrorFlag == ERROR){
					printf("Undefined set name \n"); /*if operand error flag is set to ERROR print error message and break out of loop*/
					break;
				}
				if(missingCommaFlag == ERROR){
					printf("Missing comma \n"); /*if missing comma flag is set to ERROR print error message and break out of loop*/
					break;
				}
				if(consecutiveCommaFlag == ERROR){
					printf("Multiple consecutive commas \n"); /*if consecutive comma flag is set to ERROR print error message and break out of loop*/
					break;
				}
				operandErrorFlag = validOperand(ptrOperand2); /*check to see if entered operand is valid operand*/
				if(operandErrorFlag == ERROR){
					printf("Undefined set name \n"); /*if operand error flag is set to ERROR print error message and break out of loop*/
					break;
				}
				ptrOperand3 = (char*)calloc(MAXOPERANDLEN, sizeof(char)); /*dynamically allocate memory to store entered operand*/
				while(ptrLine[inputIndex] != '\0'){
					if(ptrLine[inputIndex] == ' ' || ptrLine[inputIndex] == '\t'){
						inputIndex++; /*if input is white space increment input index and continue back to top of loop*/
						continue;
					}
					if(ptrLine[inputIndex] == ','){
						if(commaFlag == FLAGON){
							consecutiveCommaFlag = ERROR; /*if input is comma and comma flag is already set to FLAGON, set consecutive comma flag to ERROR and break out of loop*/
							break;
						}
						commaFlag = FLAGON; /*if input is comma set comma flag to FLAGON*/
						inputIndex++; /*increment inputIndex*/
						continue;
					}
					/*if comma flag is set to FLAGON*/
					if(commaFlag == FLAGON){
						/*while end of input has not been reached*/
						while(ptrLine[inputIndex] != '\0'){
							if(ptrLine[inputIndex] == ' ' || ptrLine[inputIndex] == '\t'){
								inputIndex++; /*if input is white space increment inputIndex and continue to top of loop*/
								continue;
							}
							if(operandIndex >= MAXOPERANDLEN){
								extraneousTextFlag = ERROR; /*if operandIndex is greater than the maximum operand length, set extraneous text flag to ERROR and break out of loop*/
								break;
							}
							ptrOperand3[operandIndex] = ptrLine[inputIndex]; /*set currently indexed operand value equal to currently indexed input value*/
							operandIndex++; /*increment operandIndex*/
							inputIndex++; /*increment inputIndex*/
							}
						commaFlag = FLAGON; /*set comma flag to FLAG ON*/
						break;
					}
					inputIndex++; /*increment inputIndex*/
				}
				if(consecutiveCommaFlag == ERROR){
					printf("Multiple consecutive commas \n"); /*if consecutive comma flag is set to ERROR print error message and break out of loop*/
					break;
				}
				if(extraneousTextFlag == ERROR){
					printf("Extraneous text after end of command \n"); /*if extraneous text flag is set to ERROR print error message and break out of loop*/
					break;
				}
				if((strcmp("", ptrOperand3) == STRCMPTRUE)){
					printf("Missing parameter \n"); /*if third operand is empty than print out missing parameter error message*/
					break;
				}
				operandErrorFlag = validOperand(ptrOperand3); /*check to see if entered operand is valid operand*/
				if(operandErrorFlag == ERROR){
					printf("Undefined set name \n"); /*if operand error flag is set to ERROR print error message and break out of loop*/
					break;
				}

				selectedSet1 = checkOperand(ptrOperand1); /*uses checkOperand function to return the address of the set that is input as a string in ptrOperand1*/
				selectedSet2 = checkOperand(ptrOperand2); /*uses checkOperand function to return the address of the set that is input as a string in ptrOperand2*/
				selectedSet3 = checkOperand(ptrOperand3); /*uses checkOperand function to return the address of the set that is input as a string in ptrOperand3*/

				if(strcmp("union_set", ptrCommand) == STRCMPTRUE){
					union_set(selectedSet1,selectedSet2,selectedSet3); /*if user inputted command is equal to union_set then call union_set function with the three selected sets as inputs to the function*/
				}
				if(strcmp("intersect_set", ptrCommand) == STRCMPTRUE){
					intersect_set(selectedSet1,selectedSet2,selectedSet3); /*if user inputted command is equal to intersect_set then call intersect_set function with the three selected sets as inputs to the function*/
				}
				if(strcmp("sub_set", ptrCommand) == STRCMPTRUE){
					sub_set(selectedSet1,selectedSet2,selectedSet3); /*if user inputted command is equal to sub_set then call sub_set function with the three selected sets as inputs to the function*/
				}
				if(strcmp("symdiff_set", ptrCommand) == STRCMPTRUE){
					symdiff_set(selectedSet1,selectedSet2,selectedSet3); /*if user inputted command is equal to symdiff_set then call symdiff_set function with the three selected sets as inputs to the function*/
				}
				free(ptrOperand1); /*frees the ptrOperand1 pointer*/
				free(ptrOperand2); /*frees the ptrOperand2 pointer*/
				free(ptrOperand3); /*frees the ptrOperand3 pointer*/
			}
			else if(strcmp("stop", ptrCommand) == STRCMPTRUE){
				stop(); /*if command is stop command enter stop function*/
			}
			else{
				printf("Undefined command name \n"); /*if command is not one of the command options than print error message and break out of loop*/
				break;
			}
		}
		inputIndex++; /*increment inputIndex*/
	}
}





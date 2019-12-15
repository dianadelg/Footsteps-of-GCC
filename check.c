#include <stdio.h>
#include <stdlib.h>

int strLength=0;
int tokenCount=0;
int end=0;
int start=0;
int exprCount=0; //updated every time something is sent into parse eval -- start at 1 if issue
int logCount=0; //updated based on operator
int arithCount=0; //updated based on operator
int ended=0;
int semiSpace=0;


char* substring(int start, int end, char* expr){

	

//takes the original string and gets the substring to be returned
	int newStr = end- start + 2; //null term and additional space
	char* subString = (char *)malloc(newStr * sizeof(char));
	
	//printf("START INDEX : %d \t END INDEX : %d\n", startIndex, endIndex);
	int i=0;

	for(i=0; i<newStr; i++){

		if( i == newStr-1){
	
			subString[i] = '\0';

		}else{
		
			subString[i]=expr[start+i];
		
		}

	}

	return subString;
	
	

}

void parseEval (int* intArr, char**stringArr, int start, int count){
	int idk=intArr[sizeof(intArr)/sizeof(intArr[0]) - 1];
	//printf("idk : %d\n",idk);
	int d=start;
	//int exprType=0;  // 1 for arith, 2 for log
	int arithOp=0;
	int logOp=0;
	//int exprType=0; //1 = arith, 2 = log, 3 = NOT
	ended=0;

	for(d=start; d<=count;d++){
		if(d==start){
			if(intArr[d]==-1){
				//means first item is unidentified thing
				printf("Error: Scan error in expression %d : unknown identifier\n", exprCount);
				printf("\"%s\"\n",stringArr[d]);
				if(idk==d){
					printf("Error: Scan error in expression %d : incomplete expression\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);
				}
				//printf("unknown identifier. reset parser.\n");
			}else if(intArr[d]==1 || intArr[d]==6){
				//means first number or first true/false
				//printf("idk is : %d\n",idk);
				if(idk==d){
					//meaning last index
					if(ended!=1){
					//printf("Error: Scan error in expression %d : missing operator\n", exprCount);
					//printf("\"%s\"\n",stringArr[d]);
					}
					if(end==0){printf("Error: Scan error in expression %d : incomplete expression\n", exprCount);
						printf("\"%s\"\n",stringArr[d]);
					}
					
				}
			}else if(intArr[d]==2){
				if(idk==d){
					//meaning last index
					if(ended!=1){
					//printf("Error: Scan error in expression %d : missing operand\n", exprCount);
					//printf("\"%s\"\n",stringArr[d]);
					}
					if(end==0){printf("Error: Scan error in expression %d : incomplete expression\n", exprCount);
						printf("\"%s\"\n",stringArr[d]);
					}
					
				}
				printf("Error: Scan error in expression %d : unexpected operator\n", exprCount);
				printf("\"%s\"\n",stringArr[d]);
				//printf("error. arith operator in first thing.\n");
				arithCount++;
			}else if(intArr[d]==3){
				if(idk==d){
					//meaning last index
					if(ended!=1){
					//printf("Error: Scan error in expression %d : missing operand\n", exprCount);
					//printf("\"%s\"\n",stringArr[d]);
					}
					if(end==0){printf("Error: Scan error in expression %d : incomplete expression\n", exprCount);
						printf("\"%s\"\n",stringArr[d]);
					}			
				}
				printf("Error: Scan error in expression %d : unexpected operator\n", exprCount);
				printf("\"%s\"\n",stringArr[d]);
				//printf("error. log operator in first thing.\n");
				//printf("count : %d\n",logCount);				
				logCount++;
				//printf("count : %d\n",logCount);
			}else if(intArr[d]==5){
				if(idk==d){
					//meaning last index
					if(ended!=1){
					//printf("Error: Scan error in expression %d : missing operand\n", exprCount);
					//printf("\"%s\"\n",stringArr[d]);
					}
					if(end==0){printf("Error: Scan error in expression %d : incomplete expression\n", exprCount);
						printf("\"%s\"\n",stringArr[d]);
					}
					
				}
				//means not
				//exprType=3; not yet
				// just check if 2 things were correct to see if expression ended or not. Do this when 2nd trye false is found or the one after not is found
				//printf("here\n");
				
				logCount++;
				//printf("count : %d\n",logCount);
				 
			}else{
				if(intArr[d]=='\0'){
					//if null terminator, just an empty string
					printf("Error: Scan error in expression %d : missing expression\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);
				}else{
					printf("Error: Scan error in expression %d : incomplete expression\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);
				}
			}
		}else{

			//iterating
			if(intArr[d]==-1){
				//means item is unidentified thing
				if(intArr[d-1]==2){
					//if before it is arithmetic op : + a
					printf("Error: Scan error in expression %d : unknown operand\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);
					//printf("unknown operand\n");				
				}else if(intArr[d-1]==1){
					//if number before it is a first number : 1 a
					printf("Error: Scan error in expression %d : unknown operator\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);
					//printf("unknown operator\n");
				}else if(intArr[d-1]==3){
					//before it is an AND/OR : OR a
					printf("Error: Scan error in expression %d : unknown operand\n" , exprCount);
					printf("\"%s\"\n",stringArr[d]);
					//printf("unknown operand\n");
				}else if(intArr[d-1]==5){
					//before is a NOT : NOT a
					printf("Error: Scan error in expression %d : unknown operand\n" , exprCount);
					printf("\"%s\"\n",stringArr[d]);					
					//printf("unknown operand\n");
				}else if(intArr[d-1]==6){
					//before is a first true/false: true a
					printf("Error: Scan error in expression %d : unknown operator\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);
					//printf("unknown operator\n");
				}else if(intArr[d-1]==7){
					//before is a second true/false: AND true a
					if(ended==0){
						printf("Error: Scan error in expression %d : expression should have ended\n", exprCount);
						printf("\"%s\"\n",stringArr[d]);
					//	printf("expression should have ended\n", exprCount);
						ended=1;
					}
					printf("Error: Scan error in expression %d : unknown operand\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);
					//printf("unknown operand\n"); //might be unknown identifier
					//must reset the parser now -- do something here
				}else if(intArr[d-1]==13){
					//follows a second number: + 2 a
					if(ended==0){
						printf("Error: Scan error in expression %d : expression should have ended\n", exprCount);
						printf("\"%s\"\n",stringArr[d]);
						//printf("expression should have ended\n");
						ended=1;
					}
					printf("Error: Scan error in expression %d : unknown operand\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);
					//printf("unknown operand\n"); //possibly identifier
				}else if(intArr[d-1]==-1){
					//unidentifiable follows unidentifiable: 1 a a or a a
					//THIS IS WHERE WE CHECK
					int dia=0;
					int isOperator=0;

					
					for(dia=d-1;dia>=start;dia--){
						if(intArr[dia]==1 || intArr[dia]==6){
							//means if we find first number
							isOperator=1;
							break;
						}
						if(intArr[dia]==2 || intArr[dia]==3 || intArr[dia]==5){
							isOperator=2; //means operand
							break;
						}
					}

					if(ended==1){
						printf("Error: Scan error in expression %d : unexpected operator\n", exprCount);
						printf("\"%s\"\n",stringArr[d]);
					}else if(isOperator==1){
						//keep going backwards until you see either an operator or an operand and determine output that way
						printf("Error: Scan error in expression %d : unexpected operator\n", exprCount);
						printf("\"%s\"\n",stringArr[d]);
					}else if(isOperator==2){
						printf("Error: Scan error in expression %d : unexpected operand\n", exprCount);
						printf("\"%s\"\n",stringArr[d]);
					}else{
						if(ended==1){
							printf("Error: Scan error in expression %d : unknown operand\n", exprCount);
							printf("\"%s\"\n",stringArr[d]);
						}else{
							printf("Error: Scan error in expression %d : unknown identifier\n", exprCount);
							printf("\"%s\"\n",stringArr[d]);
						}
					}
					
					//printf("unknown identifier\n");
					//reset parser
				}else{
					//follows a null
					printf("Error: Scan error in expression %d : unknown identifier\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);
					//printf("unknown identifier\n");
				}
			}else if(intArr[d]==1){
				//means first number 
				if((idk)==d && (intArr[d-1]!=5)){
					//meaning last index
					if(ended!=1){
					//printf("Error: Scan error in expression %d : missing operator\n", exprCount);
					//printf("\"%s\"\n",stringArr[d]);
					}
					
				}
				if(intArr[d-1]==2){
					//if before it is arithmetic op : + 1
					printf("Error: Scan error in expression %d : unexpected operator\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);
					if(ended==1){
						printf("Error: Scan error in expression %d : unexpected operator\n", exprCount);
						printf("\"%s\"\n",stringArr[d]);	
					}
					//printf("unexpected operator\n");				
				}else if(intArr[d-1]==1){
					printf("Error: Scan error in expression %d : unexpected operand\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);
					//if number before it is a first number : 1 1
					//printf("unexpected operand\n");
				}else if(intArr[d-1]==3){
					//before it is an AND/OR : OR 1
					printf("Error: Scan error in expression %d : unexpected operand\n", exprCount);
				printf("\"%s\"\n",stringArr[d]);
					//printf("unexpected operand\n");
				}else if(intArr[d-1]==5){
					//before is a NOT : NOT 1
					printf("Error: Scan error in expression %d : unexpected operand\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);
					//printf("unexpected operand\n");
				}else if(intArr[d-1]==6){
					//before is a first true/false: true 1
					printf("Error: Scan error in expression %d : unexpected operand\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);
					//printf("unexpected operand\n");
				}else if(intArr[d-1]==7){
					//before is a second true/false: AND true 1
					if(ended==0){
						printf("expression should have ended\n");
						ended=1;
					}
					printf("Error: Scan error in expression %d : unexpected operand\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);
					//printf("unexpected operand\n");
					//must reset the parser now -- do something here
				}else if(intArr[d-1]==13){
					//follows a second number: + 2 1
					if(ended==0){
						//printf("expression should have ended\n", exprCount);
						printf("Error: Scan error in expression %d : expression should have ended\n", exprCount);
						printf("\"%s\"\n",stringArr[d]);
						ended=1;
					}
					
					printf("Error: Scan error in expression %d : unexpected operand\n", exprCount);
				printf("\"%s\"\n",stringArr[d]);
					//printf("unexpected operand\n");
				}else if(intArr[d-1]==-1){
					//unidentifiable follows unidentifiable: a 1 or b 1
					//okay for now
					//reset parser
					//printf("Error: Scan error in expression %d : unexpected operand\n", exprCount);
					//printf("\"%s\"\n",stringArr[d]);
				}else{
					//follows a null
					//idk what to do in this case
					printf("Error: Scan error in expression %d : unexpected operand\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);
					//printf("Unexpected operand\n");
				}
			}else if(intArr[d]==2){
				//arith operator +-/*
				if(ended==0){arithCount++;}
				
				//ADD HERE
				if((idk)==d){
					//meaning last index
					//printf("idk : %d\n", idk);
					if(ended!=1){
					//printf("Error: Scan error in expression %d : missing operand\n", exprCount);
					//printf("\"%s\"\n",stringArr[d]);
					}
					
				}

				if(intArr[d-1]==2){
					//if before it is arithmetic op : + *
					printf("Error: Scan error in expression %d : unexpected operator\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);
					//printf("unexpected operator\n");				
				}else if(intArr[d-1]==1){
					//this is good
					if(ended==1){
						printf("Error: Scan error in expression %d : unexpected operator\n", exprCount);
						printf("\"%s\"\n",stringArr[d]);	
					}
				}else if(intArr[d-1]==3){
					//before it is an AND/OR : OR *
					printf("Error: Scan error in expression %d : unexpected operator\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);
					//printf("unexpected operator\n");
				}else if(intArr[d-1]==5){
					//before is a NOT : NOT *
					printf("Error: Scan error in expression %d : unexpected operator\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);
					//printf("unexpected operator\n");
				}else if(intArr[d-1]==6){
					//before is a first true/false: true *
					printf("Error: Scan error in expression %d : unexpected operator\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);
					//printf("unexpected operator\n");
				}else if(intArr[d-1]==7){
					//before is a second true/false: AND true *
					if(ended==0){
						arithCount--;
						printf("Error: Scan error in expression %d : expression was not ended\n", exprCount);
						printf("\"%s\"\n",stringArr[d]);
						//printf("expression should have ended\n");
						ended=1;
					}
					printf("Error: Scan error in expression %d : unexpected operator\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);
					//printf("unexpected operator\n");
					//must reset the parser now -- do something here
				}else if(intArr[d-1]==13){
					//follows a second number: + 2 *
					if(ended==0){
						arithCount--;
						printf("Error: Scan error in expression %d : expression was not ended\n", exprCount);
						printf("\"%s\"\n",stringArr[d]);
						//printf("expression should have ended\n");
						ended=1;
					}
					printf("Error: Scan error in expression %d : unexpected operator\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);
					//printf("unexpected operator\n");
				}else if(intArr[d-1]==-1){
					//unidentifiable follows unidentifiable: 1 a * or a *
					//printf("unexpected operator\n");
					printf("Error: Scan error in expression %d : unexpected operator\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);
					//reset parser
				}else{
					//follows a null
					printf("Error: Scan error in expression %d : unexpected operator\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);
					//printf("unknown identifier\n");
				}
			}else if(intArr[d]==3){
				if((idk)==d){
					//meaning last index
					//printf("ended: %d\n", ended);
					if(ended==1){
					
					//printf("Error: Scan error in expression %d : missing operand\n", exprCount);
					//printf("\"%s\"\n",stringArr[d]);
					}
					
				}
				if(ended==0){logCount++;
					//printf("count : %d\n",logCount);				
				}
				if(intArr[d-1]==2){
					//if before it is arithmetic op : + AND
					printf("Error: Scan error in expression %d : unexpected operator\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);
					//printf("unexpected operator\n");				
				}else if(intArr[d-1]==1){
					//if number before it is a first number : 1 AND
					printf("Error: Scan error in expression %d : unexpected operator\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);					
					//printf("unexpected operator\n");
				}else if(intArr[d-1]==3){
					//before it is an AND/OR : OR AND
					printf("Error: Scan error in expression %d : unexpected operator\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);
					//printf("unexpected operator\n");
				}else if(intArr[d-1]==5){
					//before is a NOT : NOT AND
					printf("Error: Scan error in expression %d : unexpected operator\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);
					//printf("unexpected operator\n");
				}else if(intArr[d-1]==6){
					//before is a first true/false: true AND
					//this is good
					if(ended==1){
						//printf("here? diana\n");
						printf("Error: Scan error in expression %d : unexpected operand\n", exprCount);
						printf("\"%s\"\n",stringArr[d]);	
					}
				}else if(intArr[d-1]==7){
					//before is a second true/false: AND true AND
					//printf("here? diana\n");
					if(ended==0){
						logCount--;
						printf("Error: Scan error in expression %d : expression should have ended\n", exprCount);
						printf("\"%s\"\n",stringArr[d]);
						//printf("expression should have ended\n");
						ended=1;
					}
					if(ended==1){printf("Error: Scan error in expression %d : unexpected operator\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);
					}
					//printf("unexpected operator\n");
					//must reset the parser now -- do something here
				}else if(intArr[d-1]==13){
					//follows a second number: + 2 AND
					if(ended==0){
						logCount--;
						printf("Error: Scan error in expression %d : expression should have ended\n", exprCount);
						printf("\"%s\"\n",stringArr[d]);
						//printf("expression should have ended\n");
						ended=1;
					}
					printf("Error: Scan error in expression %d : unexpected operator\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);
					//printf("unexpected operator\n");
				}else if(intArr[d-1]==-1){
					//unidentifiable follows unidentifiable: 1 a AND or a AND
					printf("Error: Scan error in expression %d : unexpected operator\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);					
					//printf("unexpected operator\n");
					//reset parser
				}else{
					//follows a null
					printf("Error: Scan error in expression %d : unexpected operator\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);
					//printf("unknown identifier\n");
				}
			}else if(intArr[d]==5){ //LEFT OFF HERE
				//means not
				//exprType=3; not yet
				// just check if 2 things were correct to see if expression ended or not. Do this when 2nd trye false is found or the one after not is found
				if((idk)==d){
					//meaning last index if
					if(ended!=1){
						//printf("Error: Scan error in expression %d : missing operand\n", exprCount);
						//printf("\"%s\"\n",stringArr[d]);
					}
				}
				if(ended==0){logCount++; //THE ERROR IS HERE
				//printf("count : %d\n",logCount);
				}
					if(intArr[d-1]==2){
					//if before it is arithmetic op : + NOT
					printf("Error: Scan error in expression %d : unexpected operator\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);
					//printf("unexpected operator\n");				
				}else if(intArr[d-1]==1){
					//if number before it is a first number : 1 NOT
					printf("Error: Scan error in expression %d : unexpected operator\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);
					//printf("unexpected operator\n");
				}else if(intArr[d-1]==3){
					//before it is an AND/OR : OR NOT
					printf("Error: Scan error in expression %d : unexpected operator\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);
					//printf("unexpected operator\n");
				}else if(intArr[d-1]==5){
					//before is a NOT : NOT NOT
					printf("Error: Scan error in expression %d : unexpected operator\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);
					//printf("unexpected operator\n");
				}else if(intArr[d-1]==6){
					//before is a first true/false: true NOT
					printf("Error: Scan error in expression %d : unexpected operator\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);
					//printf("unexpected operator\n");
				}else if(intArr[d-1]==7){
					//before is a second true/false: AND true NOT
					if(ended==0){
						logCount--;
						printf("Error: Scan error in expression %d : expression should have ended\n", exprCount);
						printf("\"%s\"\n",stringArr[d]);
						//printf("expression should have ended\n");
						ended=1;
						
					}
					printf("Error: Scan error in expression %d : unexpected operator\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);
					printf("unexpected operator\n");
					//must reset the parser now -- do something here
				}else if(intArr[d-1]==13){
					//follows a second number: + 2 NOT
					if(ended==0){
						logCount--;
						printf("Error: Scan error in expression %d : expression should have ended\n", exprCount);
						printf("\"%s\"\n",stringArr[d]);
						//printf("expression should have ended\n");
						ended=1;
					}
					printf("Error: Scan error in expression %d : unexpected operator\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);
					//printf("unexpected operator\n");
				}else if(intArr[d-1]==-1){
					//unidentifiable follows unidentifiable: 1 a NOT or a NOT
					//okay
					//reset parser
					//printf("Error: Scan error in expression %d : unexpected operator\n", exprCount);
					//printf("\"%s\"\n",stringArr[d]);
					//okay for now
					//if(ended==0){logCount++;
					//printf("count : %d\n",logCount);}//if expression should have ended -- log/arith counts do not get updated
				}else{
					//follows a null
					printf("Error: Scan error in expression %d : unexpected operator\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);
					//printf("unknown identifier\n");
				}
				
			} else if(intArr[d]==13){
				//second number
				if(intArr[d-1]==2){
					//if before it is arithmetic op : + 5
					//good		
					if(ended==1){
						printf("Error: Scan error in expression %d : unexpected operand\n", exprCount);
						printf("\"%s\"\n",stringArr[d]);	
					}		
				}else if(intArr[d-1]==1){
					//if number before it is a first number : 1 5
					printf("Error: Scan error in expression %d : unexpected operand\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);
					//printf("unexpected operand\n");
				}else if(intArr[d-1]==3){
					//before it is an AND/OR : OR 5
					printf("Error: Scan error in expression %d : unexpected operand\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);
					//printf("unexpected operand\n");
				}else if(intArr[d-1]==5){
					//before is a NOT : NOT 5
					printf("Error: Scan error in expression %d : unexpected operand\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);
					//printf("unexpected operand\n");
				}else if(intArr[d-1]==6){
					//before is a first true/false: true 5
					printf("Error: Scan error in expression %d : unexpected operand\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);
					//printf("unexpected operand\n");
				}else if(intArr[d-1]==7){
					//before is a second true/false: AND true 5
					if(ended==0){
						printf("Error: Scan error in expression %d : expression should have ended\n", exprCount);
						printf("\"%s\"\n",stringArr[d]);
						//printf("expression should have ended\n");
						ended=1;
					}
					printf("Error: Scan error in expression %d : unexpected operand\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);					
					//printf("unexpected operand\n");
					//must reset the parser now -- do something here
				}else if(intArr[d-1]==13){
					//follows a second number: + 2 5
					if(ended==0){
						printf("Error: Scan error in expression %d : expression should have ended\n", exprCount);
						printf("\"%s\"\n",stringArr[d]);
						//printf("expression should have ended\n");
						ended=1;
					}
					printf("Error: Scan error in expression %d : unexpected operand\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);
					//printf("unexpected operand\n");
				}else if(intArr[d-1]==-1){
					//unidentifiable follows unidentifiable: 1 a 5 or a 5
					printf("Error: Scan error in expression %d : unexpected operand\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);
					//printf("unexpected operand\n"); // this case will never happen!
				}else{
					//follows a null
					printf("Error: Scan error in expression %d : unexpected operand\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);
					//printf("unknown identifier\n");
				}
			}else if(intArr[d]==6){
				//a first true/false
				if((idk)==d){
					//meaning last index
					if(ended!=1){
					//printf("Error: Scan error in expression %d : missing operator\n", exprCount);
					//printf("\"%s\"\n",stringArr[d]);
					}
					
				}
				if(intArr[d-1]==2){
					//if before it is arithmetic op : + true
					printf("Error: Scan error in expression %d : unexpected operand\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);
					//printf("unexpected operand\n");				
				}else if(intArr[d-1]==1){
					//if number before it is a first number : 1 true
					//printf("unexpected operand\n");
					printf("Error: Scan error in expression %d : unexpected operand\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);
				}else if(intArr[d-1]==3){
					//before it is an AND/OR : OR true
					//printf("unexpected operand\n");
					//this case will never happen
					printf("Error: Scan error in expression %d : unexpected operand\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);
				}else if(intArr[d-1]==5){
					//before is a NOT : NOT true
					//printf("unexpected operand\n");
					//good
					if(ended==1){
						printf("Error: Scan error in expression %d : unexpected operand\n", exprCount);
						printf("\"%s\"\n",stringArr[d]);	
					}
				}else if(intArr[d-1]==6){
					//before is a first true/false: true true
					//printf("unexpected operand\n");
					printf("Error: Scan error in expression %d : unexpected operand\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);
				}else if(intArr[d-1]==7){
					//before is a second true/false: AND true true
					if(ended==0){
						printf("Error: Scan error in expression %d : expression should have ended\n", exprCount);
						printf("\"%s\"\n",stringArr[d]);
						//printf("expression should have ended\n");
						ended=1;
					}
					printf("Error: Scan error in expression %d : unexpected operand\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);
					//printf("unexpected operand\n");
					//must reset the parser now -- do something here
				}else if(intArr[d-1]==13){
					//follows a second number: + 2 true
					if(ended==0){
						printf("Error: Scan error in expression %d : expression should have ended\n", exprCount);
						printf("\"%s\"\n",stringArr[d]);
						//printf("expression should have ended\n");
						ended=1;
					}
					//printf("unexpected operand\n");
					printf("Error: Scan error in expression %d : unexpected operand\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);
				}else if(intArr[d-1]==-1){
					//unidentifiable follows unidentifiable: 1 a true or a true
					//okay
					//reset parser
					//printf("Error: Scan error in expression %d : unexpected operand\n", exprCount);
					//printf("\"%s\"\n",stringArr[d]);
				}else{
					//follows a null
					//printf("unknown identifier\n");
					printf("Error: Scan error in expression %d : unexpected operand\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);
				}
			}else if(intArr[d]==7){
				//current is a second true/false
				if(intArr[d-1]==2){
					//if before it is arithmetic op : + true /this case will never happen
					//printf("unexpected operator\n");		
					printf("Error: Scan error in expression %d : unexpected operator\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);		
				}else if(intArr[d-1]==1){
					//if number before it is a first number : 1 true //this case will never happen
					//printf("unexpected operator\n");
					printf("Error: Scan error in expression %d : unexpected operator\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);
				}else if(intArr[d-1]==3){
					//before it is an AND/OR : OR true
					//this is good
					if(ended==1){
						printf("Error: Scan error in expression %d : unexpected operand\n", exprCount);
						printf("\"%s\"\n",stringArr[d]);	
					}
				}else if(intArr[d-1]==5){
					//before is a NOT : NOT true //this case will never happen
					//printf("unexpected operator\n");
					printf("Error: Scan error in expression %d : unexpected operator\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);
				}else if(intArr[d-1]==6){
					//before is a first true/false: true true
					//printf("unexpected operator\n"); //this case will never happen
					printf("Error: Scan error in expression %d : unexpected operator\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);
				}else if(intArr[d-1]==7){
					//before is a second true/false: AND true true
					if(ended==0){
						//printf("expression should have ended\n");
						printf("Error: Scan error in expression %d : expression should have ended\n", exprCount);
						printf("\"%s\"\n",stringArr[d]);
						ended=1;
					}
					printf("Error: Scan error in expression %d : unexpected operator\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);
					//printf("unexpected operand\n");
					//must reset the parser now -- do something here
				}else if(intArr[d-1]==13){
					//follows a second number: + 2 true
					if(ended==0){
						//printf("expression should have ended\n");
						printf("Error: Scan error in expression %d : expression should have ended\n", exprCount);
						printf("\"%s\"\n",stringArr[d]);
						ended=1;
					}
					printf("Error: Scan error in expression %d : unexpected operator\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);
					//printf("unexpected operator\n");
				}else if(intArr[d-1]==-1){
					//unidentifiable follows unidentifiable: 1 a NOT or a NOT //this case will never happen
					//okay
					//reset parser
					printf("Error: Scan error in expression %d : unexpected operator\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);
				}else{
					//follows a null
					printf("Error: Scan error in expression %d : unexpected operator\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);
					//printf("unknown identifier\n");
				}

			}
			else {
				if(intArr[d]=='\0'){
					//if null terminator, just an empty string
					printf("Error: Scan error in expression %d : expression incomplete\n", exprCount);
					printf("\"%s\"\n",stringArr[d]);
				}else{
					//printf("this is a space!\n"); //check this
					//is it unexpected operator or operand?? -- do the loop thing
					int dia=0;
					int isOperator=0;
					for(dia=d-1;dia<start;dia++){
						if(intArr[dia]==1 || intArr[dia]==6){
							//means if we find first number
							isOperator=1;
							break;
						}
						if(intArr[dia]==2 || intArr[dia]==3 || intArr[dia]==5){
							isOperator=2; //means operand
							break;
						}
					}

					if(ended==1){
						printf("Error: Scan error in expression %d : unexpected operator\n", exprCount);
						printf("\"%s\"\n",stringArr[d]);
					}else if(isOperator==1){
						//keep going backwards until you see either an operator or an operand and determine output that way
						printf("Error: Scan error in expression %d : unexpected operator\n", exprCount);
						printf("\"%s\"\n",stringArr[d]);
					}else if(isOperator==2){
						printf("Error: Scan error in expression %d : unexpected operand\n", exprCount);
						printf("\"%s\"\n",stringArr[d]);
					}
					//printf("Error: Scan error in expression %d : unexpected operator\n", exprCount);
					//printf("\"%s\"\n",stringArr[d]);
				}
			}





			} //end of else loop -- means done looking at segment
			
			
	} //end of for loop -- means done with block.

	
// need space cases, ; cases, and what happens if missing things
// expression wasn't ended cases
// printed might not be corrected
//log and arith count might not be correct
// quotes formatting error is a problem -- escape key and new line error
//change parse and scan error based on type

	//printf("expression count: %d\n", exprCount);
	exprCount++;
	
		
	//printf("\n");


	

	
	return;

}

int chunkEval (int* intArr, char*stringArr, int count){

	//takes the current string and returns a flag based on what is found at current index
	//NUMBERS ARE AS FOLLOWS:
	/*
 *	       -2 : null/empty string
	       -1 : error, unidentifiable thing 
 *		0 : spaces
 *		1 : first numbers 0-9
	       13 : second numbers 0-9
 *		2 : operator + / - *
 *		3 : first AND/OR
		5 : NOT
 *		6 : first true/false
		7 : second true/false
	       
 * 	*/

	int p=0;
	int len = 0;
	while(stringArr[len]!='\0'){
		len++;
	}

	int isFirstElement=-1;
	//int [] is used to check for the first and second operand
	//count is used to determine position in the array
	/*if(count==0){
		//means first element
		isFirstElement=1
	} //means if the first element is -1
*/ //don't even need this, just check the count
	int isNum = 1;
	
	 if(len==1&&(stringArr[0]=='+' || stringArr[0]=='-' || stringArr[0]=='/' || stringArr[0]=='*')){
			
			return 2;
	}else if(len==3 && (stringArr[0]=='A' && stringArr[1] == 'N' && stringArr[2]=='D')){
			
			return 3;
	}else if(len==3 &&(stringArr[0]=='N' && stringArr[1] =='O' && stringArr[2]=='T')){
			
			return 5;
	}else if(len==2 && (stringArr[0]=='O' && stringArr[1]=='R')){
			
			return 3;
	}else if(len==4 && (stringArr[0]=='t' && stringArr[1]=='r' && stringArr[2] == 'u' && stringArr[3]=='e')){
			//in here, do an if else based on position in the char code array
			if(intArr[count-1]==3){
				//means it follows an AND or an OR
				
				return 7;
			}

			else{
				
				return 6;}
	}else if(len==5 && (stringArr[0]=='f' && stringArr[1]=='a' && stringArr[2] == 'l' && stringArr[3] == 's' && stringArr[4] == 'e')){
			if(intArr[count-1]==3){
				//means it follows an AND or an OR
				
				return 7;
			}else{
				
				return 6;
				
			}
	}else if(stringArr[0]==' '){
			
			return 0;
	}else{
		for(p=0; p<len; p++){
			if(stringArr[p]!='1' &&  stringArr[p]!='2' && stringArr[p]!='3' && stringArr[p]!='4' && stringArr[p]!='5' && stringArr[p]!='6' && stringArr[p]!='7' && stringArr[p]!='8' && stringArr[p]!='9' & stringArr[p]!='0'){
				isNum = 0;
				//return -1;
			}
		}
		//break here
		if(isNum == 1 && len>=1){
			//valid number
			if(intArr[count-1]==2){
				//means it follows an operator
				
				return 13;
			}else{
				
				return 1;
			}
		}else{
			//means it is not a chunk of all numbers 
			//parse more errors here to determine exactly what the error is if else if else until last else is just that we dont know what it is, ret -1
			//int errorIs=-1; //will change based on what error is found
				//means unidentifiable thing
				if(stringArr[0]!='\0'){
						return -1;				
				}
				else{
						return -2;
				}
			}
		} 
	
}

void length (char* expr){

	
	while(expr[strLength]!='\0'){
		strLength++;
	}
	return;
} //argv1 string length

void tokenC (char* expr){
int x=0;
for(x=0;x<=strLength;x++){
		if(expr[x]=='\0'){
			tokenCount++;
			if(x==0){
				end=x;
			}else{
				end=x-1;
			}
		
		}else if(expr[x]==';'){
			
			if(x==0){
				end=x;
			}else{
				end=x-1;
			}
			tokenCount++;
	
			
			start=x+1;
			if(expr[start]==' '){
				start++;
				x++;
			}else{
				//printf("error, no space after semicolon\n");
			}
			
		}else if(expr[x]==' '){
			
			tokenCount++;
			if(x==0){
				end=x;
			}else{
				end=x-1;
			}
			start=x+1;
		}else{
			end=x;
		}
	}

}



int main (int argc, char **argv){

	if(argc >2){
		printf("too many arguments\n");
		return -1;
	}

	char* expr=argv[1];

	if(expr[0]=='\0'){
		//print the error
	printf("Error: Scan error in expression 0: incomplete expression\n");
	printf("Found 1 expressions: 0 logical and 0 arithmetic\n");
		return 0;
	} 

	//printf("value of argv1: %s\n",expr);

	

	int x=0;
	length(expr);
	tokenC(expr);
	//printf("Number of tokens: %d\n", tokenCount);
	start=0;
	end=0;
	int count=0;
	int startIndex=0;
	//int splitEnd=0; //first and last index to split the thing

	int* codeArray = malloc(tokenCount*sizeof(int));
	char**stringArray = (char**) malloc (tokenCount * sizeof (char*));
	
	for(x=0;x<=strLength;x++){
		if(expr[x]=='\0'){
			//tokenCount++;
			if(x==0){
				end=x;
			}else{
				end=x-1;
			}
			//ends expression and overall parse
			//printf("End of line.\n");
			//evaluate the expression
			char* temp = substring(start, end, expr);
			//use temp, return number, put in array
			//int chunkEval (int* intArr, char*temp, int count)
			int hold = chunkEval(codeArray, temp, count);
			codeArray[count]=hold;



			int p=0;
			int len = 0;
			while(temp[len]!='\0'){
				len++;
			}
			stringArray[count]=(char*)malloc((len+1)*(sizeof(char)));
			for(p=0;p<len;p++){
				stringArray[count][p]=temp[p];
			}
			stringArray[count][len+1]='\0';
			//since at the end of expression, parse the elements you have here

			//int* intArr, char**stringArr, int token, int count
			//(int* intArr, char**stringArr, int start, int count)
			
						
			parseEval(codeArray, stringArray, startIndex, count);
			count++;

			
			


			//printf("Value of token: %s\n",temp);
			//int* codeArray = malloc(tokenCount*sizeof(int));
	 		//char**stringArray = (char**) malloc (tokenCount * sizeof (char*));
			
			//return 0;
		}else if(expr[x]==';'){
			//end expression only
			//printf("Ends expression%c\n", expr[x]);
			if(x==0){
				end=x;
			}else{
				end=x-1;
			}
			//tokenCount++;
			char* temp = substring(start, end, expr);
			int hold = chunkEval(codeArray, temp, count);
			codeArray[count]=hold;
			
			int p=0;
			int len = 0;
			while(temp[len]!='\0'){
				len++;
			}
			stringArray[count]=(char*)malloc((len+1)*(sizeof(char)));
			for(p=0;p<len;p++){
				stringArray[count][p]=temp[p];
			}
			stringArray[count][len+1]='\0';
			
			//count++;
			//startIndex=count;		
			//printf("count : %d     start index: %d\n", count, startIndex);	
			//count++;			
			parseEval(codeArray, stringArray, startIndex, count);
			count++;
			
			startIndex=count; //might have to change based on if there is a space or not
			
				
			
			//printf("Value of token: %s\n",temp);
			//int* codeArray = malloc(tokenCount*sizeof(int));
	 		//char**stringArray = (char**) malloc (tokenCount * sizeof (char*));
			
			start=x+1;
			if(expr[start]==' '){
				start++;
				x++;
			}else{
				//error, no space after semicolon
				if(semiSpace==1){
					printf("Error: Scan error in expression %d : expression wasn't ended\n", exprCount);
					printf("\"%s\"\n","");
				}
				//printf("error, no space after semicolon\n"); //giving a null char so add this too, good
			}
			
		}else if(expr[x]==' '){
			//printf("Ends token%c\n", expr[x]);
			//tokenCount++;
			if(x==0){
				end=x;
			}else{
				end=x-1;
			}
			//add token to char array
			char* temp = substring(start, end, expr);
			int hold = chunkEval(codeArray, temp, count);
			codeArray[count]=hold;
			// TRY TO PUT THIS IN OWN METHOD
			int p=0;
			int len = 0;
			while(temp[len]!='\0'){
				len++;
			}
			stringArray[count]=(char*)malloc((len+1)*(sizeof(char)));
			for(p=0;p<len;p++){
				stringArray[count][p]=temp[p];
			}
			stringArray[count][len+1]='\0';

			
			count++;
			
			//printf("Value of token: %s\n",temp);
			//int* codeArray = malloc(tokenCount*sizeof(int));
	 		//char**stringArray = (char**) malloc (tokenCount * sizeof (char*));
			//this is a problem 
			
			start=x+1;
		}else{
			end=x;
		}
	}


	printf("Found %d expressions: %d logical and %d arithmetic.\n", exprCount, logCount, arithCount);
// he said you can print this at the end
	/*int dia=0;
	for(dia=0;dia<tokenCount;dia++){
		printf("%s has code: %d\n", stringArray[dia], codeArray[dia]);
	}*/
	
	free(codeArray);
	free(stringArray);

	//free code array and free string array
	


	return 0;
}

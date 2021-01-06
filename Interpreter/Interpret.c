#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "interpreterLogic.h"

int main(int argc, char* argv[])
{

	int currentLineNo = 0; //Contain line number of instruction being executed.

	char* allStatements[100]; // Will contain all the statements of given file
	int totalLines = 0; // total lines of statement in given file
	char currentInstruction[50]; // current instruction of file we will be processing

	FILE* filePointer= fopen("ex3.asm", "r"); // Opening the test case file
	
	if (filePointer)
	{
		//Read the file line by line and then copy each line in our Array.
		while (fgets(currentInstruction, 50, filePointer) != NULL)	//checking if we have reached end of file
		{
			allStatements[totalLines] = (char*)calloc(50, sizeof(char));	//allocating memory
			strcpy(allStatements[totalLines], currentInstruction);	//copying current read instruction into array
			totalLines++;		//increasing count of statement read 
		}
		//Now executing instruction 
		while (currentLineNo < totalLines)
		{
			char temp[50]="";
			strcpy(temp, allStatements[currentLineNo]);//Copying one statement at a time for execution 
			processInstruction(temp, &currentLineNo); //Now time to execute that instruction
		}
		fclose(filePointer); // freeing resource 
		for (int i = 0; i < totalLines; i++)
			free(allStatements[i]);

	}
	else
	{
		printf("Error.File cannot be opened\n");
	}
}

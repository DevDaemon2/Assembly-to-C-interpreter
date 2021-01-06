#ifndef interpretLogic_H
#define interpretLogic_H
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<string.h>
#include <stdlib.h>
int ax = 0, bx = 0, cx = 0, dx = 0;
//This function will return instruction mapping with file instruction.
int decideInstructionLogic(char* str)
{
	if (strcmp(str, "read") == 0)
		return 0;
	else if (strcmp(str, "add") == 0)
		return 1;
	else if (strcmp(str, "sub") == 0)
		return 2;
	else if (strcmp(str, "div") == 0)
		return 3;
	else if (strcmp(str, "mul") == 0)
		return 4;
	else if (strcmp(str, "jmp") == 0)
		return 5;
	else if (strcmp(str, "je") == 0)
		return 6;
	else if (strcmp(str, "jg") == 0)
		return 7;
	else if (strcmp(str, "jl") == 0)
		return 8;
	else if (strcmp(str, "jne") == 0)
		return 9;
	else if (strcmp(str, "jge") == 0)
		return 10;
	else if (strcmp(str, "jle") == 0)
		return 11;
	else if (strcmp(str, "print") == 0)
		return 12;
	else if (strcmp(str, "mov") == 0)
		return 13;
	else
		return -1;
}

// Will return address of mentioned register in any instruction.
int* getRegisterAddress(char* str)
{
	if (strcmp(str, "ax") == 0||strcmp(str, "ax\n") == 0)
		return &ax;
	else if (strcmp(str, "bx") == 0 || strcmp(str, "bx\n") == 0)
		return &bx;
	else if (strcmp(str, "cx") == 0 || strcmp(str, "cx\n") == 0)
		return &cx;
	else if (strcmp(str, "dx") == 0 || strcmp(str, "dx\n") == 0)
		return &dx;
	return &ax;
}


void processInstruction(char* str, int* controlLine)
{
	int temp;//again a temp variable
	char t[50]; // for temporary storage of our instruction string. 
	strcpy(t, str); //copying our string in s
	// Now breaking the string and getting its name to determine the switch case.
	int instructionNumber = decideInstructionLogic(strtok(t, " "));
	int jumpLine; // will contain the value of lineNumber that control where to go after execution of any jump statement
	int parameter1 = *controlLine;  // this will contain our first parameter if its a constant
	int* parameter2 = &temp; // this will contain second parameter whether a constant or register.

	char* instruction;
	switch (instructionNumber)
	{
	case 0:// read instruction
	{
		char*reg=strtok(NULL, " ");
		
		if (strcmp(reg, "ax\n") == 0 || strcmp(reg, "ax") == 0)
			scanf("%d",&ax);
		else if (strcmp(reg, "bx\n") == 0 || strcmp(reg, "bx") == 0)
			scanf("%d", &bx);
		else if (strcmp(reg, "cx\n") == 0 || strcmp(reg, "cx") == 0)
			scanf("%d", &cx);
		else
			scanf("%d", &dx);

		*controlLine = *controlLine + 1;
		break;
	}
	case 1: // add instruction
	{
		instruction = strtok(NULL, " ");
		if (sscanf(instruction, "%d", &parameter1) <= 0)
		{
			int* reg1 = getRegisterAddress(instruction);
			parameter2 = getRegisterAddress(strtok(NULL, " "));
			*parameter2 = *parameter2 + *reg1;
		}
		else
		{
			parameter2 = getRegisterAddress(strtok(NULL, " "));
			*parameter2 = *parameter2 + parameter1;
		}
		*controlLine = *controlLine + 1;
		break;
	}
	case 2:// sub instruction
	{
		instruction = strtok(NULL, " ");
		if (sscanf(instruction, "%d", &parameter1) <= 0)
		{
			int* reg1 = getRegisterAddress(instruction);
			parameter2 = getRegisterAddress(strtok(NULL, " "));
			*parameter2 = (*parameter2) - (*reg1);
		}
		else
		{
			parameter2 = getRegisterAddress(strtok(NULL, " "));
			*parameter2 = (*parameter2) - parameter1;
		}
		*controlLine = *controlLine + 1;
		break;
	}
	case 3://div instruction
	{
		instruction = strtok(NULL, " ");
		if (sscanf(instruction, "%d", &parameter1) <= 0)
		{
			int* reg1 = getRegisterAddress(instruction);
			parameter2 = getRegisterAddress(strtok(NULL, " "));
			*parameter2 = (*parameter2) / (*reg1);
		}
		else
		{
			parameter2 = getRegisterAddress(strtok(NULL, " "));
			*parameter2 = *parameter2 / parameter1;
		}
		*controlLine = *controlLine + 1;
		break;
	}
	case 4: // mul instruction 
	{
		instruction = strtok(NULL, " ");
		if (sscanf(instruction, "%d", &parameter1) <= 0)
		{
			int* reg1 = getRegisterAddress(instruction);
			parameter2 = getRegisterAddress(strtok(NULL, " "));
			*parameter2 = (*parameter2) * (*reg1);
		}
		else
		{
			parameter2 = getRegisterAddress(strtok(NULL, " "));
			*parameter2 = *parameter2 * parameter1;
		}
		*controlLine = *controlLine + 1;
		break;
	}
	case 5:// jmp statement
	{
		instruction = strtok(NULL, " ");
		sscanf(instruction, "%d", &parameter1);
		*controlLine = parameter1;
		break;
	}
	case 6: //Je instruction
	{
		instruction = strtok(NULL, " ");
		sscanf(instruction, "%d", &jumpLine); //storing line number for jumping to that line

		instruction = strtok(NULL, " "); // getting first parameter as a string
		if (sscanf(instruction, "%d", &parameter1) <= 0) //If first parameter=register
		{
			int* reg1 = getRegisterAddress(instruction); //  getting that first parameter.
			instruction = strtok(NULL, " ");// getting second parameter as a string
			if (sscanf(instruction, "%d", parameter2) <= 0)// if second parameter=register
			{
				parameter2 = getRegisterAddress(instruction);
				(*reg1 == *parameter2) ? (*controlLine = jumpLine) : (*controlLine = *controlLine + 1);
			}
			else// if second parameter=constant
			{
				(*reg1 == *parameter2) ? (*controlLine = jumpLine) : (*controlLine = *controlLine + 1);
			}
		}
		else  //if first parameter=constant value
		{
			instruction = strtok(NULL, " "); // getting second parameter as a string
			if (sscanf(instruction, "%d", parameter2) <= 0) // if second parameter=register
			{	// je logic
				parameter2 = getRegisterAddress(instruction);
				(parameter1 == *parameter2) ? (*controlLine = jumpLine) : (*controlLine = *controlLine + 1);
			}
			else // if second parameter=constant
			{		// je logic
				(parameter1 == *parameter2) ? (*controlLine = jumpLine) : (*controlLine = *controlLine + 1);
			}

		}
		break;
	}
	case 7://jg instruction case 7-11 logics are same as that of 6
	{
		instruction = strtok(NULL, " ");
		sscanf(instruction, "%d", &jumpLine);
		instruction = strtok(NULL, " ");
		if (sscanf(instruction, "%d", &parameter1) <= 0)
		{
			int* reg1 = getRegisterAddress(instruction);
			instruction = strtok(NULL, " ");
			if (sscanf(instruction, "%d", parameter2) <= 0)
			{
				parameter2 = getRegisterAddress(instruction);
				(*reg1 > * parameter2) ? (*controlLine = jumpLine) : (*controlLine = *controlLine + 1);
			}
			else
			{
				(*reg1 > * parameter2) ? (*controlLine = jumpLine) : (*controlLine = *controlLine + 1);
			}
		}
		else
		{
			instruction = strtok(NULL, " ");
			if (sscanf(instruction, "%d", parameter2) <= 0)
			{
				parameter2 = getRegisterAddress(instruction);
				(parameter1 > * parameter2) ? (*controlLine = jumpLine) : (*controlLine = *controlLine + 1);
			}
			else
			{
				(parameter1 > * parameter2) ? (*controlLine = jumpLine) : (*controlLine = *controlLine + 1);
			}
		}
		break;
	}
	case 8://jl instruction
	{
		instruction = strtok(NULL, " ");
		sscanf(instruction, "%d", &jumpLine);
		instruction = strtok(NULL, " ");
		if (sscanf(instruction, "%d", &parameter1) <= 0)
		{
			int* reg1 = getRegisterAddress(instruction);
			instruction = strtok(NULL, " ");
			if (sscanf(instruction, "%d", parameter2) <= 0)
			{
				parameter2 = getRegisterAddress(instruction);
				(*reg1 < *parameter2) ? (*controlLine = jumpLine) : (*controlLine = *controlLine + 1);
			}
			else
			{
				(*reg1 < *parameter2) ? (*controlLine = jumpLine) : (*controlLine = *controlLine + 1);
			}
		}
		else
		{
			instruction = strtok(NULL, " ");
			if (sscanf(instruction, "%d", parameter2) <= 0)
			{
				parameter2 = getRegisterAddress(instruction);
				(parameter1 < *parameter2) ? (*controlLine = jumpLine) : (*controlLine = *controlLine + 1);
			}
			else
			{
				(parameter1 < *parameter2) ? (*controlLine = jumpLine) : (*controlLine = *controlLine + 1);
			}
		}
		break;
	}
	case 9://jne instruction			
	{
		instruction = strtok(NULL, " ");
		sscanf(instruction, "%d", &jumpLine);
		instruction = strtok(NULL, " ");
		if (sscanf(instruction, "%d", &parameter1) <= 0)
		{
			
			int* reg1 = getRegisterAddress(instruction);
			instruction = strtok(NULL, " ");
			if (sscanf(instruction, "%d", parameter2) <= 0)
			{//jne logic
				parameter2 = getRegisterAddress(instruction);
				(*reg1 != *parameter2) ? (*controlLine = jumpLine) : (*controlLine = *controlLine + 1);
			}
			else
			{//jne logic
				(*reg1 != *parameter2) ? (*controlLine = jumpLine) : (*controlLine = *controlLine + 1);
			}
		}
		else
		{
			instruction = strtok(NULL, " ");
			if (sscanf(instruction, "%d", parameter2) <= 0)
			{//jne logic
				parameter2 = getRegisterAddress(instruction);
				(parameter1 != *parameter2) ? (*controlLine = jumpLine) : (*controlLine = *controlLine + 1);
			}
			else
			{//jne logic
				(parameter1 != *parameter2) ? (*controlLine = jumpLine) : (*controlLine = *controlLine + 1);
			}

		}
		break;
	}
	case 10://jge instruction
	{
		instruction = strtok(NULL, " ");
		sscanf(instruction, "%d", &jumpLine);
		instruction = strtok(NULL, " ");
		if (sscanf(instruction, "%d", &parameter1) <= 0)
		{
			int* reg1 = getRegisterAddress(instruction);
			instruction = strtok(NULL, " ");
			if (sscanf(instruction, "%d", parameter2) <= 0)
			{
				parameter2 = getRegisterAddress(instruction);
				(*reg1 > * parameter2) ? (*controlLine = jumpLine) : (*controlLine = *controlLine + 1);
			}
			else
			{
				(*reg1 >= *parameter2) ? (*controlLine = jumpLine) : (*controlLine = *controlLine + 1);
			}
		}
		else
		{
			instruction = strtok(NULL, " ");
			if (sscanf(instruction, "%d", parameter2) <= 0)
			{
				parameter2 = getRegisterAddress(instruction);
				(parameter1 >= *parameter2) ? (*controlLine = jumpLine) : (*controlLine = *controlLine + 1);
			}
			else
			{
				(parameter1 >= *parameter2) ? (*controlLine = jumpLine) : (*controlLine = *controlLine + 1);
			}
		}
		break;
	}
	case 11://jle instruction
	{
		instruction = strtok(NULL, " ");
		sscanf(instruction, "%d", &jumpLine);
		instruction = strtok(NULL, " ");
		if (sscanf(instruction, "%d", &parameter1) <= 0)
		{
			int* reg1 = getRegisterAddress(instruction);
			instruction = strtok(NULL, " ");
			if (sscanf(instruction, "%d", parameter2) <= 0)
			{
				parameter2 = getRegisterAddress(instruction);
				(*reg1 <= *parameter2) ? (*controlLine = jumpLine) : (*controlLine = *controlLine + 1);
			}
			else
			{
				(*reg1 <= *parameter2) ? (*controlLine = jumpLine) : (*controlLine = *controlLine + 1);
			}
		}
		else
		{
			instruction = strtok(NULL, " ");
			if (sscanf(instruction, "%d", parameter2) <= 0)
			{
				parameter2 = getRegisterAddress(instruction);
				(parameter1 <= *parameter2) ? (*controlLine = jumpLine) : (*controlLine = *controlLine + 1);
			}
			else
			{
				(parameter1 <= *parameter2) ? (*controlLine = jumpLine) : (*controlLine = *controlLine + 1);
			}
		}
		break;
	}
	case 12://print instruction
	{
		instruction = strtok(NULL, " ");
		if (sscanf(instruction, "%d", &parameter1) > 0)
		{
			printf("%d", parameter1);
		}
		else // if it contains a register then printing it
		{
			if (strcmp(instruction, "ax\n") == 0|| strcmp(instruction, "ax") == 0)
				printf("%d", ax);
			else if (strcmp(instruction, "bx\n") == 0 || strcmp(instruction, "bx") == 0)
				printf("%d", bx);
			else if (strcmp(instruction, "cx\n") == 0 || strcmp(instruction, "cx") == 0)
				printf("%d", cx);
			else if (strcmp(instruction, "dx\n") == 0 || strcmp(instruction, "dx") == 0)
				printf("%d", dx);
		}
		*controlLine = *controlLine + 1;
		break;
	}
	case 13: //mov statement.
	{
		instruction = strtok(NULL, " ");//get first operand as a string.
		if (sscanf(instruction, "%d", &parameter1) > 0) // if its a number/constant then store its value in parameter1
		{
			instruction = strtok(NULL, " "); // now get second operand as a string.
			if (strcmp(instruction, "ax\n") == 0 || strcmp(instruction, "ax") == 0)
				ax = parameter1;
			else if (strcmp(instruction, "bx\n") == 0 || strcmp(instruction, "bx") == 0)
				bx = parameter1;
			else if (strcmp(instruction, "cx\n") == 0 || strcmp(instruction, "cx") == 0)
				cx = parameter1;
			else if (strcmp(instruction, "dx\n") == 0 || strcmp(instruction, "dx") == 0)
				dx = parameter1;
		}
		else
		{
			int* reg1 = getRegisterAddress(instruction); // If first operand is also a register than get its address
			// now get second operand as a string which is a register 
			parameter2 = getRegisterAddress(strtok(NULL, " "));
			*parameter2 = *reg1;//mov statement
		}
		*controlLine = *controlLine + 1; //now moving to next instruction
		break;
	}
	default:
	{
		*controlLine = *controlLine + 1;
		break;
	}
	}
}

#endif

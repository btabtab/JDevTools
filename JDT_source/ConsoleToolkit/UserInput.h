#ifndef USER_INPUT_H
#define USER_INPUT_H

#include <stdio.h>
#include <stdlib.h>

#define INPUT_BUFFER_LENGTH 50

char* getInputBuffer()
{
	static char buffer[INPUT_BUFFER_LENGTH] = "";
	return buffer;
}

char* readInputFromUser()
{
	// printf("ApPlot \\ ");
	setTextColour(MAGENTA);
	printf("Smash:" TEXT_COLOUR_RED____ " \\ " TEXT_COLOUR_GREEN__ "$ ");
	setTextColour(CYAN);
	scanf("%s", getInputBuffer());
	setTextColour(WHITE);
	getInputBuffer()[INPUT_BUFFER_LENGTH - 1] = '\0';
	return getInputBuffer();
}

void resetString(char* str)
{
	// sprintf(str, "");
	// printf("reset\n");
	strcpy(str, "");
}

void resetInputBuffer()
{
	resetString(getInputBuffer());
}

#endif
#ifndef SCRIPT_LOADING_H
#define SCRIPT_LOADING_H
/*
	The file extension is ".proot".
*/
#include <stdlib.h>
#include <stdio.h>

#include "ConsoleColours.h"

typedef struct RootScript
{
	FILE* file;
}
RootScript;

RootScript* getCurrentScriptFile()
{
	static RootScript root_script;
	return &root_script;
}

void loadScriptFile(char* name)
{
	setTextColour(CYAN);
	printf("loading: %s\n", name);
	setTextColour(WHITE);
	getCurrentScriptFile()->file = fopen(name, "r");
}

int getFileSize()
{
	fseek(getCurrentScriptFile()->file, 0L, SEEK_END);
	int sz = ftell(getCurrentScriptFile()->file);
	rewind(getCurrentScriptFile()->file);
	return sz;
}

void printFileContents()
{
	int file_size = getFileSize();

	char temp[file_size];
	fscanf(getCurrentScriptFile()->file, "%s", temp);

	for(int f_i = 0; f_i != file_size; f_i++)
	{
		printf("%c", temp[f_i]);
	}
}

#endif
#ifndef CONSOLECONTROLPANEL
#define CONSOLECONTROLPANEL

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct ArgumentContainer
{
	int argc;
	char **argv;
}
ArgumentContainer;

typedef struct TerminalSettings
{
	ArgumentContainer program_arguments;
	bool logging_to_file;
	bool double_spaced_draw;
	bool disable_characters;
	bool verbose_output;
}
TerminalSettings;

TerminalSettings* getTerminalSettings();
void printApplicationArguments(ArgumentContainer arguments);
TerminalSettings parseArgumentsForProgram(ArgumentContainer arguments);

TerminalSettings* getTerminalSettings()
{
	static TerminalSettings terminal_settings;
	return &terminal_settings;
}

void printApplicationArguments(ArgumentContainer arguments)
{
	printf("\nArguments: %d\n", arguments.argc);

	for(int i = 0; i != arguments.argc; i++)
	{
		printf("%d: %s\n", i, arguments.argv[i]);
	}

}

TerminalSettings parseArgumentsForProgram(ArgumentContainer arguments)
{
	TerminalSettings ret;
	printApplicationArguments(arguments);
	if(arguments.argc == 1)
	{
		return ret;
	}
	if(!strcmp(arguments.argv[1], "help"))
	{
		printf("Available arguments are:\n\
		help - show available arguments\n\
		logging_output_to_file - outputs program log to file.\n\
		double_spaced - if a character pixel is an empty space (' ') it will be drawn twice.\n\
		disable_chars - Disables having non empty space (' ') as a character for drawing.\n\
		verbose - Sets logging to verbose and outputting as much as possible.\n\
		");
		exit(0);
	}

	for(int i = 0; i != arguments.argc; i++)
	{
		if(!ret.logging_to_file){ret.logging_to_file = (!strcmp(arguments.argv[i], "logging_output_to_file"));}
		if(!ret.double_spaced_draw){ret.double_spaced_draw = (!strcmp(arguments.argv[i], "double_spaced"));}
		if(!ret.disable_characters){ret.disable_characters = (!strcmp(arguments.argv[i], "disable_chars"));}
		if(!ret.disable_characters){ret.verbose_output = (!strcmp(arguments.argv[i], "verbose"));}
	}
	ret.program_arguments = arguments;
	return ret;
}

#endif
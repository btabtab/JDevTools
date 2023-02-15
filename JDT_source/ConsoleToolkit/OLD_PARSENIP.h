#ifndef PARSE_NIP_H
#define PARSE_NIP_H
/*
	Yes, the name of this file is a pun.
*/

#include <stdlib.h>
#include <inttypes.h>
#include <errno.h>
#include <string.h>

#include "UserInput.h"

typedef struct ParseNipCommand
{
	char instruction_name[INPUT_BUFFER_LENGTH];
	int parameters_detected;
	char parameter_buffer[(INPUT_BUFFER_LENGTH - 10)][5];
}
ParseNipCommand;

void printParseNipCommand(ParseNipCommand* parsenip_command)
{
	printf("parameters: %d\n", parsenip_command->parameters_detected);
	if(!parsenip_command)
	{
		return;
	}
	setTextColour(YELLOW);
	printf("%s", parsenip_command->instruction_name);
	
	setTextColour(CYAN);
	printf("(");

	for(int i = 0; i != 5; i++)
	{
		setTextColour(RED);
		printf("[%d]: ", i);
		setTextColour(GREEN);
		// setTextColour(YELLOW);
		printf("{%s}", parsenip_command->parameter_buffer[i]);
		if(i != (4))
		{
			setTextColour(BLUE);
			printf(", ");
		}
	}
	setTextColour(CYAN);
	printf(")\n");
	setTextColour(WHITE);
}

void resetParsnipCommand(ParseNipCommand* pnc)
{
	if(!pnc)
	{
		return;
	}

	printParseNipCommand(pnc);
	printf("reset\n");
	resetString(pnc->instruction_name);
	for (int i = 0; i != 5; i++)
	{
		resetString(pnc->parameter_buffer[i]);
	}
	pnc->parameters_detected = 0;
	printParseNipCommand(pnc);
}

int getIndexOfCharacter(char* string_to_search, char search_char, int chars_to_skip/*'weeyh2t' - silvie*/)
{
	for(int i = 0; i != INPUT_BUFFER_LENGTH; i++)
	{
		if(string_to_search[i] == search_char)
		{
			if(!chars_to_skip)
			{
				return i;
			}
			chars_to_skip--;
		}
	}
	return INPUT_BUFFER_LENGTH;
}

int getLastIndexOfCharacter(char search_char, int chars_to_skip/*'weeyh2t' - silvie*/)
{
	for(int i = INPUT_BUFFER_LENGTH; i != -1; i--)
	{
		if(getInputBuffer()[i] == search_char)
		{
			if(chars_to_skip--)
			{
				return i;
			}
		}
	}
	return INPUT_BUFFER_LENGTH;
}

int countPresenceOfCharacter(char* str, char search_char)
{
	int count = 0;
	for(int i = 0; i != INPUT_BUFFER_LENGTH; i++)
	{
		count += (getInputBuffer()[i] == search_char);
	}
	return count;
}

typedef struct ParseNipErrors
{
	bool parenthesis_missing;
	bool parenthesis_misordered;

	bool paramter_is_empty;
}
ParseNipErrors;

bool printParseNipErrors(ParseNipErrors parsenip_errors, ParseNipCommand* parse_nip_command)
{
	setTextColour(RED);
	if(parsenip_errors.parenthesis_missing)
	{
		printf("'(' count: %d\n", countPresenceOfCharacter(getInputBuffer(), '('));
		printf("')' count: %d\n", countPresenceOfCharacter(getInputBuffer(), ')'));
		printf("ERROR> Parenthesis missing.\n");
		setTextColour(RESET);
		return true;
	}
	if(parsenip_errors.parenthesis_misordered)
	{
		printf("ERROR> Parenthesis misordered.\n");
		setTextColour(RESET);
		return true;
	}
	setTextColour(RESET);
	return false;
}

ParseNipErrors checkForParenthsisError()
{
	ParseNipErrors ret = { 0 };
	ret.parenthesis_missing = (countPresenceOfCharacter(getInputBuffer(), '(') == 0) || (countPresenceOfCharacter(getInputBuffer(), ')') == 0);
	ret.parenthesis_misordered = ((getIndexOfCharacter(getInputBuffer(), '(', 0) > getIndexOfCharacter(getInputBuffer(), ')', 0)) * 1);
	return ret;
}

ParseNipErrors checkParametersForErrors()
{
	ParseNipErrors ret = { 0 };
	return ret;
}

char* grabTextFromPosToPos(char* text_buff, int start, int stop, char* copy_buffer)
{
	if(stop == start)
	{
		printf("??????\n");
	}
	if(stop < start)
	{
		int swap = start;
		start = stop;
		stop = swap;
	}
	for(int i = 1; (start + i) != stop; i++)
	{
		copy_buffer[i - 1] = text_buff[start + i];
	}
	return copy_buffer;
}

/*
This is to be indexed like an
array (0 == first parameter).
*/
char* getParameter(int parameter_to_get, ParseNipCommand* parsenip_command)
{
	resetString(parsenip_command->parameter_buffer[parameter_to_get]);
	int start, stop;
	if(parameter_to_get == 0)
	{
		// printf("(: %d\n", getIndexOfCharacter(getInputBuffer(), '(', 0));
		start = getIndexOfCharacter(getInputBuffer(), '(', 0);
	}
	else
	{
		start = getIndexOfCharacter(getInputBuffer(), ',', parameter_to_get - 1);
	}
	if(parsenip_command->parameters_detected == (parameter_to_get + 1))
	{
		// printf("): %d\n", getIndexOfCharacter(getInputBuffer(), ')', 0));
		stop = getIndexOfCharacter(getInputBuffer(), ')', 0);
	}
	else
	{
		stop = getIndexOfCharacter(getInputBuffer(), ',', parameter_to_get);
	}
	grabTextFromPosToPos(getInputBuffer(), start, stop, parsenip_command->parameter_buffer[parameter_to_get]);

	// printf("sta: %d, sto: %d, str: %s\n", start, stop, ret);

	return parsenip_command->parameter_buffer[parameter_to_get];
}

bool readParsenipCommand(ParseNipCommand* parsenip_command)
{
	if(!parsenip_command)
	{
		return false;
	}

	resetParsnipCommand(parsenip_command);
	if(printParseNipErrors(checkForParenthsisError(), parsenip_command))
	{
		printParseNipCommand(parsenip_command);
		return false;
	}

	int command_index_tracker = 0;
	int parameter_start_index = getIndexOfCharacter(getInputBuffer(), '(', 0);
	for(/**/; command_index_tracker != parameter_start_index; command_index_tracker++)
	{
		parsenip_command->instruction_name[command_index_tracker] = getInputBuffer()[command_index_tracker];
		if(getInputBuffer()[command_index_tracker+1] == '(')
		{
			break;
		}
	}
	parsenip_command->parameters_detected = countPresenceOfCharacter(getInputBuffer(), ',') + 1;

	if(getInputBuffer()[parameter_start_index + 1] == ')')
	{
		parsenip_command->parameters_detected = 0;
	}

	// printf("parameters in function: %d\n", parsenip_command.parameters_detected);
	for(int current_param = 0; current_param != parsenip_command->parameters_detected; current_param++)
	{
		printf("parameter[%d]: %s\n", current_param, getParameter(current_param, parsenip_command));
		sprintf(parsenip_command->parameter_buffer[current_param], "%s", getParameter(current_param, parsenip_command));
	}
	return true;
}

int stringToInt(char* input)
{
	//Source: https://stackoverflow.com/questions/7021725/how-to-convert-a-string-to-integer-in-c
	return strtoumax(input, NULL, 10);
}

# endif
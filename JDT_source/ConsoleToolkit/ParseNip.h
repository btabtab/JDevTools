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
#include "PlotsWrapper.h"

#define PARSENIP_PARAMETER_COUNT 5

typedef struct ParseNipCommand
{
	int parameters_detected;
	char instruction_name[INPUT_BUFFER_LENGTH];
	char parameter_buffer[(INPUT_BUFFER_LENGTH - 10)][PARSENIP_PARAMETER_COUNT];
}
ParseNipCommand;

typedef struct ParseNipErrors
{
	bool parenthesis_missing;
	bool parenthesis_misordered;

	bool paramter_is_empty;
}
ParseNipErrors;

//prints out 'parsenip_command'.
void printParseNipCommand(ParseNipCommand* parsenip_command);
//clears the contents of 'pnc'.
void resetParsnipCommand(ParseNipCommand* pnc);
//gets the Xth time (X = 'chars_to_skip') a character appears in 'string_to_search'.
int getIndexOfCharacter(char* string_to_search, char search_char, int chars_to_skip/*'weeyh2t' - silvie*/);
//gets the last time 'search_char' appears in 'str'.
int getLastIndexOfCharacter(char* str, char search_char, int chars_to_skip/*'weeyh2t' - silvie*/);
//counts how many times the character in 'str' occurs.
int countPresenceOfCharacter(char* str, char search_char);
//prints the errors in the command.
bool printParseNipErrors(ParseNipErrors parsenip_errors, ParseNipCommand* parse_nip_command);
//returns the error information relating to parenthesies.
ParseNipErrors checkForParenthsisError(char* string);
//returns the error information relating to parameters.
ParseNipErrors checkParametersForErrors(char* string);
//returns the parsenip error struct that tracks errors.
ParseNipErrors checkStringForErrors(char* string);
//this returns true if there is a single error in the input.
bool isErrorInCommand(ParseNipErrors errors);
//copies the text in between 'start' and 'stop' in 'text_buf' into 'copy_buffer'.
void grabTextFromPosToPos(char* text_buff, int start, int stop, char* copy_buffer);
//gets the Xth parameter (X = 'parameter_to_get') from command 'parsenip_command'.
void getParameter(ParseNipCommand* parsenip_command, int parameter_to_get, char* copy_to_buffer);
//returns false if the command had an error.
bool readParsenipCommand(ParseNipCommand* parsenip_command, char* string);
//no idea what this is? who wrote it? why is it here? what can / does / is it meant to do??????
int stringToInt(char* input);

//definitions:

//prints out 'parsenip_command'.
void printParseNipCommand(ParseNipCommand* parsenip_command)
{
	printf("command: %s > ", parsenip_command->instruction_name);
	printf("parameters: %d: \n", parsenip_command->parameters_detected);
	for(int i = 0; i != PARSENIP_PARAMETER_COUNT; i++)
	{
		setTextColour(i + 2);
		printf(" [%d]: %s |", i, parsenip_command->parameter_buffer[i]);
	}
	setTextColour(RESET);
	printf("\n");

}
//clears the contents of 'pnc'.
void resetParsnipCommand(ParseNipCommand* pnc)
{
	sprintf(pnc->instruction_name, " ");
	for(int i = 0; i != PARSENIP_PARAMETER_COUNT; i++){sprintf(pnc->parameter_buffer[i], " ");}
	pnc->parameters_detected = 0;
}
//gets the Xth time (X = 'chars_to_skip') a character appears in 'string_to_search'. Returns -1 if failed to find.
int getIndexOfCharacter(char* string_to_search, char search_char, int chars_to_skip/*'weeyh2t' - silvie*/)
{
	for(int i = 0; string_to_search[i] != '\0'; i++)
	{
		if(string_to_search[i] == search_char)
		{
			if(!(chars_to_skip--))
			{
				// printf("char: %c, position: %d\n", search_char, i);
				return i;
			}
		}
	}
	printf(" getIndexOfCharacter fail to find %c in %s.\n", search_char, string_to_search);
	return -1;
}
//gets the last time 'search_char' appears in 'str'. Returns -1 if failed to find.
int getLastIndexOfCharacter(char* str, char search_char, int chars_to_skip/*'weeyh2t' - silvie*/)
{
	return -1;
}
//counts how many times the character in 'str' occurs.
int countPresenceOfCharacter(char* str, char search_char)
{
	int count = 0;
	for(int i = 0; str[i] != '\0'; i++)
	{
		count += (str[i] == search_char);
	}
	return count;
}
//prints the errors in the command.
bool printParseNipErrors(ParseNipErrors parsenip_errors, ParseNipCommand* parse_nip_command)
{
	return false;
}
//returns the error information relating to parenthesies.
ParseNipErrors checkForParenthsisError(char* string)
{
	return (ParseNipErrors){ 0 };
}
//returns the error information relating to parameters.
ParseNipErrors checkParametersForErrors(char* string)
{
	return (ParseNipErrors){ 0 };
}
ParseNipErrors checkStringForErrors(char* string)
{
	ParseNipErrors ret = checkForParenthsisError(string);
	ret.paramter_is_empty = checkParametersForErrors(string).paramter_is_empty;
	return ret;
}
bool isErrorInCommand(ParseNipErrors errors)
{
	return (errors.paramter_is_empty || errors.parenthesis_misordered || errors.parenthesis_missing);
}
//copies the text in between 'start' and 'stop' in 'text_buf' into 'copy_buffer'.
void grabTextFromPosToPos(char* text_buff, int start, int stop, char* copy_buffer)
{
	int i_end = 0;
	for(int i = start; i < stop || text_buff[i] != '\0'; i++)
	{
		i_end = (i - start);
		// printf("i_end/ %d\n", i_end);
		copy_buffer[i] = text_buff[i_end];
	}
	copy_buffer[stop] = '\0';
}
void getStringBetweenChars(char* string, char* copy_to_buffer, char a, char b, int l_skip, int r_skip, int range_shift)
{
	char temp[40] = "";
	int start = (getIndexOfCharacter(string, a, l_skip) + 1), finish = getIndexOfCharacter(string, b, r_skip);
	for(int i = start; i != finish; i++)
	{
		// printf("getStringBetweenChars: string[%d]: <%c>\n", i, string[i]);
		temp[i - start] = string[i];
	}
	temp[finish - start] = '\0';
	sprintf(copy_to_buffer, "%s", temp);
	// printf("string [%s] from between [%d] and [%d] from [%s]", copy_to_buffer, start_char, end_char, string);
}

void getStringBetweenParenthesis(char* string, char* copy_to_buffer)
{
	char temp[40] = "";
	getStringBetweenChars(string, temp, '(', ')', 0, 0, 0);
	sprintf(copy_to_buffer, "{%s}", temp);
}
//�
void copyParameterXIntoBuffer(char* input, char* buffer, int x, int x_limit)
{
	sprintf(buffer, "");
	// printf("input: %s\n", input);
	//no params
	if(!x_limit){return;}
	//x is 0
	if(!x)		{if(x_limit == 1){getStringBetweenChars(input, buffer, '{', '}', 0, 0, 0); printf("!x > | %s |\n", buffer); return;}}
	
	//x is the last parameter
	if(x_limit == (x+1)){getStringBetweenChars(input, buffer, ',', '}', x - 1, 0, 0); printf("x_limit == x+1 > | %s |\n", buffer); return;}

	if(x){getStringBetweenChars(input, buffer, ',', ',', x - 1, x, 0); printf("x > | %s |\n", buffer); return;}

	//x is the first parameter
	{getStringBetweenChars(input, buffer, '{', ',', 0, 0, 0); 		printf(" > | %s |\n", buffer); return;}
	return;
}
//gets the Xth parameter (X = 'parameter_to_get') from command 'parsenip_command'.
void getParameterFromInput(ParseNipCommand* parsenip_command, int parameter_to_get, char* input)
{
	//This is a temporary buffer to store a text to break down the process of extracting parameters.
	char temp[30] = "", copy_buff[30] = "";
	getStringBetweenParenthesis(input, copy_buff);

	// printf("copy buffer %s\n", copy_buff);
	// setTextColour(BLUE);
	// printf("copy_buff = { %s }\n", copy_buff);
	// setTextColour(GREEN);
	// printf("(parsenip_command->parameters_detected - 1) = %d, parameter_to_get = %d\n", (parsenip_command->parameters_detected - 1), parameter_to_get);
	// setTextColour(RESET);

	copyParameterXIntoBuffer(copy_buff, temp, parameter_to_get, parsenip_command->parameters_detected);
	sprintf(parsenip_command->parameter_buffer[parameter_to_get], "%s", temp);
}
int countParameters(char* string)
{
	int ret = (countPresenceOfCharacter(string, ',') + 1) * ((string[getIndexOfCharacter(string, '(', 0) + 1] != ')'));
	return ret;
}
//returns false if the command had an error.
bool readParsenipCommand(ParseNipCommand* parsenip_command, char* string)
{
	// printf("--%s\n( :%d\n) :%d\n", string, getIndexOfCharacter(string, '(', 0), getIndexOfCharacter(string, ')', 0));
	grabTextFromPosToPos(string, 0, getIndexOfCharacter(string, '(', 0), parsenip_command->instruction_name);
	parsenip_command->parameters_detected = countParameters(string);

	for(int i = 0; i != parsenip_command->parameters_detected; i++)
	{
		// setTextColour(RED);
		// printf("AAAAAAAAAAA %d\n", parsenip_command->parameters_detected);
		// setTextColour(RESET);

		getParameterFromInput(parsenip_command, i, string);
		// writeStringIntoPlotGraph(1 + i, 1 + i, parsenip_command->parameter_buffer[i], false);
	}

	char temp_string[INPUT_BUFFER_LENGTH] = "";
	grabTextFromPosToPos(string, getIndexOfCharacter(string, '(', 0), getIndexOfCharacter(string, ')', 0), temp_string);

	// printf("--%s(%s)", parsenip_command->instruction_name, temp_string);
	// writeStringIntoPlotGraph(0, 0, parsenip_command->instruction_name, false);
	return true;
}

//no idea what this is? who wrote it? why is it here? what can / does / is it meant to do??????
int stringToInt(char* input)
{
	//Source: https://stackoverflow.com/questions/7021725/how-to-convert-a-string-to-integer-in-c
	return strtoumax(input, NULL, 10);
}

# endif
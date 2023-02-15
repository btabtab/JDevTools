#ifndef CONSOLE_COLOUR
#define CONSOLE_COLOUR

#include <stdio.h>
#include <stdlib.h>

#include "ToolkitConsoleControlPanel.h"

#define TEXT_COLOUR_RESET__ "\033[0;0m"/*1*/
#define TEXT_COLOUR_BLACK__ "\033[0;30m"/*3*/
#define TEXT_COLOUR_RED____ "\033[0;31m"/*2*/
#define TEXT_COLOUR_GREEN__ "\033[0;32m"/*4*/
#define TEXT_COLOUR_YELLOW_ "\033[0;33m"/*5*/
#define TEXT_COLOUR_BLUE___ "\033[0;34m"/*6*/
#define TEXT_COLOUR_MAGENTA "\033[0;35m"/*7*/
#define TEXT_COLOUR_CYAN___ "\033[0;36m"/*8*/
#define TEXT_COLOUR_WHITE__ "\033[0;37m"/*9*/

#define SCREEN_COLOUR_RESET__ "\033[0;0m"/*1*/
#define SCREEN_COLOUR_BLACK__ "\033[0;40m"/*3*/
#define SCREEN_COLOUR_RED____ "\033[0;41m"/*2*/
#define SCREEN_COLOUR_GREEN__ "\033[0;42m"/*4*/
#define SCREEN_COLOUR_YELLOW_ "\033[0;43m"/*5*/
#define SCREEN_COLOUR_BLUE___ "\033[0;44m"/*6*/
#define SCREEN_COLOUR_MAGENTA "\033[0;45m"/*7*/
#define SCREEN_COLOUR_CYAN___ "\033[0;46m"/*8*/
#define SCREEN_COLOUR_WHITE__ "\033[0;47m"/*9*/


const char text_colour_codes[9][9] =
{
	TEXT_COLOUR_RESET__,
	TEXT_COLOUR_RED____,
	TEXT_COLOUR_BLACK__,
	TEXT_COLOUR_GREEN__,
	TEXT_COLOUR_YELLOW_,
	TEXT_COLOUR_BLUE___,
	TEXT_COLOUR_MAGENTA,
	TEXT_COLOUR_CYAN___,
	TEXT_COLOUR_WHITE__
};

const char screen_colour_codes[10][9] =
{
	SCREEN_COLOUR_RESET__,
	SCREEN_COLOUR_RED____,
	SCREEN_COLOUR_BLACK__,
	SCREEN_COLOUR_GREEN__,
	SCREEN_COLOUR_YELLOW_,
	SCREEN_COLOUR_BLUE___,
	SCREEN_COLOUR_MAGENTA,
	SCREEN_COLOUR_CYAN___,
	SCREEN_COLOUR_WHITE__,
	SCREEN_COLOUR_RED____,
};

enum Colours
{
	RESET,
	RED,
	BLACK,
	GREEN,
	YELLOW,
	BLUE,
	MAGENTA,
	CYAN,
	WHITE,
	/*
	If the pixel is this then it will not be
	rendered at all if layering is in effect.
	*/
	INVISIBLE,
};

void setTextColour(int chosen_colour)
{
	if(getTerminalSettings()->logging_to_file)
	{
		return;
	}
	printf("%s", text_colour_codes[chosen_colour]);
}
void setScreenColour(int chosen_colour)
{
	if(getTerminalSettings()->logging_to_file)
	{
		return;
	}
	printf("%s", screen_colour_codes[chosen_colour]);
}
#endif
#ifndef ERROR_SNIFFING
#define ERROR_SNIFFING

#include "ConsoleToolkit/ConsoleColours.h"

void sniffForError(char* error_catch_message)
{
	printf(TEXT_COLOUR_RED____ "\n%s\n" TEXT_COLOUR_RESET__, error_catch_message);
}

#endif
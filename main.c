#include <stdio.h>
#include <stdlib.h>

#include "JDT_source/ConsoleToolkit/ToolkitConsoleControlPanel.h"
#include "JDT_source/ConsoleToolkit/ConsoleDraw.h"
#include "JDT_source/DemoSRCcode/LinkedListDemo.h"

#include "JDT_source/DemoSRCcode/StarDemo.h"

#include "JDT_source/ConsoleToolkit/SillyDrawFunctions.h"

#include "JDT_source/ErrorSniffing.h"

#include "JDT_source/DemoSRCcode/RainDemo.h"

#include "JDT_source/ConsoleToolkit/ParseNip.h"

#include "JDT_source/ConsoleToolkit/ProgramCommands.h"

void baseDemo(int argc, char *argv[]);

bool ApPlotCycle()
{
	getPlotsBuffer();
	// resetString(getInputBuffer());
	ParseNipCommand pncommand;
	resetParsnipCommand(&pncommand);
	if(readParsenipCommand(&pncommand, readInputFromUser()))//"writeText(3,4,hello,true)"))
	{
		printParseNipCommand(&pncommand);
		executeParsnenipFunctions(&pncommand);
		resetParsnipCommand(&pncommand);
	}
	return true;
}

int main(int argc, char *argv[])
{
	system("tput reset");
	setTextColour(YELLOW);
	printf("ApPlot Math graphing Demo\n \
	Using Parsenip version 0.1\n \
	for help with commands type 'help'.\n");
	ArgumentContainer arg_container = (ArgumentContainer){argc, argv};
	initConsoleDrawing(getPlotsBuffer(), &arg_container);
	setTextColour(RESET);
	// printf("\n%s\n%s\n", getInputBuffer(), getInstructionID());
	resetConsole(0);
	about();
	getPlotsBuffer();
	while(ApPlotCycle())
	{
	}
	drawPlotsBuffer();
	return 0;
	rainDemo((ArgumentContainer){argc, argv});
}

void baseDemo(int argc, char *argv[])
{
	printf("δOSc\n");
}
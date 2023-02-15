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
	readInputFromUser();
	if(readParsenipCommand(&pncommand, getInputBuffer()))
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
	resetConsole(1);
	ArgumentContainer arguments = (ArgumentContainer){argc, argv};
	(*getTerminalSettings()) = parseArgumentsForProgram(arguments);
	VBuffer buffer;
	initVbuffer(&buffer, VBUFFER_WIDTH);

	for(int i = 0; i != WHITE << 1; i++)
	{
		resetConsole(1);
		drawLine_naiveAlgorithm(&buffer, (Point){10 - i, i}, (Point){15 + i, 15 + (i << 1)}, newPixel((1 + i) % WHITE, ' '));
		// drawRectangleFilled(&buffer, (Point){0, 0}, (Point){15, 15}, RED);
		drawBuffer(&buffer, true, true);
	}

	printf("\ndone:\n");
	// fillVbufferWithColours(&buffer[0]);
	// sortVbufferColours(&buffer[0]);
	printApplicationArguments((ArgumentContainer){argc, argv});
	printf("δOSc\n");
}
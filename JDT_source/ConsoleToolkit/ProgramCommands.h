#ifndef PROGRAM_COMMANDS_H
#define PROGRAM_COMMANDS_H

#include "PlotsWrapper.h"
#include "ParseNip.h"
#include "ScriptLoading.h"
#include "../FancyWancyDrawDemo.h"

void plotsCommands(ParseNipCommand* command);
void plotsHelp();
void genericHelp();
void about();
void genericCommands(ParseNipCommand* command);

void about()
{
	resetConsole(0);
	setTextColour(BLUE);
	printf("There are several help topics, such as:\n\
	Generic - This is the basic toolkit that comes with the DeltaDex Environment.\n\
	Plots - This is the drawing and graphing library.\n\
	The 'help()' command can be useful if you want to see what's available.\n\
	You can also use the name of a topic for the parameter to get\ninformation regarding it.\n");
	setTextColour(WHITE);

}

void help(ParseNipCommand* command)
{
	setTextColour(YELLOW);
	if(!strcmp(command->parameter_buffer[0], "plots"))
	{
		plotsHelp();
		return;
	}
	if(!strcmp(command->parameter_buffer[0], "generic"))
	{
		genericHelp();
		return;
	}
	printf("instruction list:\n");
	setTextColour(GREEN);
	plotsHelp();
	genericHelp();
	setTextColour(WHITE);
}

void executeParsnenipFunctions(ParseNipCommand* command)
{
	// return;
	printf("Executing Parsenip Command...\n");
	if(!strcmp(command->instruction_name, "help") || !strcmp(command->instruction_name, "H!"))
	{
		help(command);
		return;
	}
	if(!strcmp(command->instruction_name, "about") || !strcmp(command->instruction_name, "ABT"))
	{
		about();
		return;
	}
	plotsCommands(command);
	genericCommands(command);

	printf("\n");
	resetInputBuffer();

}

void plotsHelp()
{
	printf("Plots Help:\n");
	printf("\tplot(x,y)\n");
	printf("\tdrawLine(x1,y1,x2,y2)\n");
	printf("\tclearPlotsBuffer()\n");
	printf("\treDrawBuffer()\n");
	printf("\tflipBuffer()");
}

void genericHelp()
{
	printf("\trecurse()\n");
	printf("\treCompileAndRun()\n");
	printf("\tclearScreen()\n");
}

void genericCommands(ParseNipCommand* command)
{
	if(!strcmp(command->instruction_name, "exit"))
	{
		printf("Exiting program...\n");
		exit(0);
	}
	//This will run the program inside of itself.
	if(!strcmp(command->instruction_name, "recurse"))
	{
		printf("running the program again...");
		system("./main.exe");
		// exit(0);
	}
	if(!strcmp(command->instruction_name, "reCompileAndRun"))
	{
		system("./buildCfile.sh");
		// exit(0);
	}
	if(!strcmp(command->instruction_name, "clearScreen"))
	{
		printf("clearing screen\n");
		resetConsole(0);
	}
	if(!strcmp(command->instruction_name, "printFile"))
	{
		printf("printing: %s\n", command->parameter_buffer[0]);
		loadScriptFile(command->parameter_buffer[0]);
		printFileContents();
	}
	if(!strcmp(command->instruction_name, "system"))
	{
		system(command->parameter_buffer[0]);
	}
}
#include "Xiaolin_Wu_LineAlgorithm.h"

void plotsCommands(ParseNipCommand* command)
{
	if(!strcmp(command->instruction_name, "plot") || !strcmp(command->instruction_name, "^^") || !strcmp(command->instruction_name, "xy"))
	{
		printf(" Plotting:\n");
		plot(stringToInt(command->parameter_buffer[0]), stringToInt(command->parameter_buffer[1]), true);
		return;
	}
	if(!strcmp(command->instruction_name, "drawLine") || !strcmp(command->instruction_name, "$$") || !strcmp(command->instruction_name, "xyxy"))
	{
		Point a = {stringToInt(command->parameter_buffer[0]), stringToInt(command->parameter_buffer[1])}, b = {stringToInt(command->parameter_buffer[2]), stringToInt(command->parameter_buffer[3])};
		printf("drawing line from {%d, %d}to {%d, %d}\n", a.x, a.y, b.x, b.y);
		plotLine(a.x, a.y, b.x, b.y, true);
		return;
	}
	if(!strcmp(command->instruction_name, "clearPlotsBuffer"))
	{
		plotsResetBuffer();
		return;
	}
	
	if(!strcmp(command->instruction_name, "flipBuffer"))
	{
		if(!command->parameters_detected || 1 < command->parameters_detected)
		{
			sniffForError("Invalid parameter amount: ");
			setTextColour(YELLOW);
			printf("%d instead of 1", command->parameters_detected);
			setTextColour(RESET);
			return;
		}
		if(command->parameter_buffer[0][0] != 'x' && command->parameter_buffer[0][0] != 'y')
		{
			setTextColour(RED);
			printf("Axis not set for command!\n");
			setTextColour(RESET);
			return;
		}
		printf("flipping along the %c axis", command->parameter_buffer[0][0]);
		invertPlotsBuffer(command->parameter_buffer[0][0]);
		drawPlotsBuffer();
		return;
	}

	if(!strcmp(command->instruction_name, "writeText"))
	{
		if(command->parameters_detected < 4)
		{
			setTextColour(RED);
			printf("Not enough parameters");
			setTextColour(RESET);
		}
		writeStringIntoPlotGraph(	stringToInt(command->parameter_buffer[0]),
									stringToInt(command->parameter_buffer[1]),
									command->parameter_buffer[2],
									(!strcmp(command->parameter_buffer[3], "true")));
									return;
	}
	
	if(!strcmp(command->instruction_name, "DMO"))
	{
		printf("fancy demo:\n");
		fancyDrawingDemo();
		return;
	}
	if(!strcmp(command->instruction_name, "DL"))
	{
		spXiaolinDraw(getPlotsBuffer(), 0, 0, 30, 0, *currentPixelData());
		drawPlotsBuffer();
	}
}
#endif
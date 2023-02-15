#ifndef RAIN_DEMO_H
#define RAIN_DEMO_H

#include "../ConsoleToolkit/ConsoleDraw.h"
#include "../ConsoleToolkit/ConsoleColours.h"
#include "../ConsoleToolkit/SillyDrawFunctions.h"
#include "../ConsoleToolkit/SpecialBufferOperations.h"

void drawBackground(VBuffer* buffer)
{
	fillBufferWithPixels(buffer, newPixel(GREEN, ':'));
	drawRectangleFilled(buffer, (Point){0, VBUFFER_WIDTH / 3}, (Point){VBUFFER_WIDTH, VBUFFER_WIDTH}, newPixel(CYAN, ' '));
	updateScreen(buffer, 0);
}

void rainDemo(ArgumentContainer args)
{
	VBuffer buffer;
	initConsoleDrawing(&buffer, &args);

	// fillBufferWithPixels(&buffer, newPixel(YELLOW, ' '));

	drawBackground(&buffer);

	int timer = 5;
	while (timer - 1)
	{
		timer--;
		{
		}
		updateScreen(&buffer, 3);
	}

}

#endif
#ifndef FANCY_DRAW_DEMO_H
#define FANCY_DRAW_DEMO_H

#include "ConsoleToolkit/PlotsWrapper.h"
#include "ConsoleToolkit/Xiaolin_Wu_LineAlgorithm.h"

#include "ConsoleToolkit/ShapesDrawing.h"

void fancyDrawingDemo()
{
	// printf("fancyDrawingDemo");
	// writeStringIntoPlotGraph(1,1,"hello world!", false);

	for(int ix = 0, iy = getPlotsBuffer()->width - 1; ix != getPlotsBuffer()->width; ix++, iy--)
	{
		// if(ix != getPlotsBuffer()->width - 1)
		{
			(*currentPixelData()) = newPixel(RED, ' ');
			plot(ix, iy, false);
		}

	}

	(*currentPixelData()) = newPixel(BLUE, '-');
	spXiaolinDraw(getPlotsBuffer(), 0, 0, getPlotsBuffer()->width, 0, (*currentPixelData()));
	spXiaolinDraw(getPlotsBuffer(), 0, 0, 0, getPlotsBuffer()->width, (*currentPixelData()));

	drawRectangle(newPoint(5, 6), newDimension(6, 8));

	(*currentPixelData()) = newPixel(YELLOW, '-');
	drawRectangle(newPoint(8, 9), newDimension(6, 8));

	(*currentPixelData()) = newPixel(MAGENTA, '*');
	drawStar(newPoint(22, 22));

	(*currentPixelData()) = newPixel(GREEN, '@');
	drawTriangle(newPoint(10, 20), newPoint(20, 20), newPoint(20, 10));

	drawPlotsBuffer();
}

#endif
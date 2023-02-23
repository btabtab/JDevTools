#ifndef FANCY_DRAW_DEMO_H
#define FANCY_DRAW_DEMO_H

#include "ConsoleToolkit/PlotsWrapper.h"
#include "ConsoleToolkit/Xiaolin_Wu_LineAlgorithm.h"

void fancyDrawingDemo()
{
	// printf("fancyDrawingDemo");
	// writeStringIntoPlotGraph(1,1,"hello world!", false);

	(*currentPixelData()) = newPixel(BLUE, '-');
	spXiaolinDraw(getPlotsBuffer(), 0, 0, getPlotsBuffer()->width, 0);
	spXiaolinDraw(getPlotsBuffer(), 0, 0, 0, getPlotsBuffer()->width);


	for(int ix = 0, iy = getPlotsBuffer()->width - 1; ix != getPlotsBuffer()->width; ix++, iy--)
	{
		// if(ix != getPlotsBuffer()->width - 1)
		{
			(*currentPixelData()) = newPixel(RED, ' ');
			plot(ix, iy, false);
		}

	}
	drawPlotsBuffer();
}

#endif
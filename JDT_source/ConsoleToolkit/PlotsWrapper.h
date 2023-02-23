#ifndef PLOTS_WRAPPER_H
#define PLOTS_WRAPPER_H

#include "ConsoleDraw.h"
#include "Xiaolin_Wu_LineAlgorithm.h"

VBuffer* getPlotsBuffer()
{
	static VBuffer buffer;
	
	static bool is_buffer_initialised = false;
	if(!is_buffer_initialised)
	{
		initVbuffer(&buffer, 30);
		is_buffer_initialised = true;
	}

	return &buffer;
}
PixelData* currentPixelData()
{
	static PixelData pixel;
	
	static bool is_initialised = false;
	if(!is_initialised)
	{
		pixel = newPixel(WHITE, ' ');
		is_initialised = true;
	}

	return &pixel;
}
void drawPlotsBuffer()
{
	// resetConsole(1);
	drawBuffer(getPlotsBuffer(), true, true);
}
void plot(int x, int y, bool redraw)
{
	drawPixelToBufferFromPoint(getPlotsBuffer(), (*currentPixelData()), (Point){x, y});
	if(redraw)
	{
		drawPlotsBuffer();
	}
}
void plotLine(int x_start, int y_start, int x_end, int y_end, bool redraw_buffer)
{
	if(VBUFFER_WIDTH < x_start || VBUFFER_WIDTH < y_start || VBUFFER_WIDTH < x_end || VBUFFER_WIDTH < y_end)
	{
		setTextColour(RED);
		printf("target is OOB\n");
		setTextColour(RESET);
		return;
	}
	spXiaolinDraw(getPlotsBuffer(), x_start, y_start, x_end, y_end, (*currentPixelData()));
	// drawLine_naiveAlgorithm(getPlotsBuffer(), (Point){x_start, y_start}, (Point){x_end, y_end}, *currentPixelData());
	
	if(redraw_buffer)
	{
		drawPlotsBuffer();
	}
}

void writeStringIntoPlotGraph(int x, int y, char* string, bool redraw_graph)
{
	printTextIntoBuffer(getPlotsBuffer(), x, y, YELLOW, string);
	if(redraw_graph)
	{
		drawPlotsBuffer();
	}
}

void invertPlotsBuffer(char mode)
{
	flipBufferContents(getPlotsBuffer(), mode);
}
void flipPlotsBufferOnYAxis()
{
}
void flipPlotsBufferOnXAxis()
{
}

void plotsResetBuffer()
{
	initVbuffer(getPlotsBuffer(), VBUFFER_WIDTH);
}

#endif
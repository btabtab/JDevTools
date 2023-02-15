#ifndef EXTRA_DRAW_FUNCTIONS_H
#define EXTRA_DRAW_FUNCTIONS_H

#include <stdint.h>

#include "ConsoleDraw.h"
#include "ConsoleColours.h"

#include "../ErrorSniffing.h"

void fillVbufferWithColours(VBuffer* buffer);
void sortVbufferColours(VBuffer* buffer);
bool sortVbufferColoursPass(VBuffer* buffer);


void fillVbufferWithColours(VBuffer* buffer)
{
	int seed = ~(0);
	
	int limiter = VBUFFER_DIMENSIONS;
	while(seed && limiter)
	{
		buffer->data[seed % VBUFFER_DIMENSIONS] = newPixel(seed % WHITE, ' ');
		seed = ((seed ^ seed << 9 ) >> 1);
		limiter--;
	}
}
void sortVbufferColours(VBuffer* buffer)
{
	int passes = 0;
	while (!sortVbufferColoursPass(buffer))
	{
		passes++;
		printf("Passes: %d\n", passes);
	}
}

bool sortVbufferColoursPass(VBuffer* buffer)
{
	PixelData pixel_buffer;
	bool is_sort_finished = true;
	for(int i = 0; i != ((buffer->width * buffer->width) - 1); i++)
	{
		if(buffer->data[i].screen_colour < buffer->data[i + 1].screen_colour)
		{
			pixel_buffer = buffer->data[i];
			buffer->data[i] = buffer->data[i+1];
			buffer->data[i+1] = pixel_buffer;
			is_sort_finished = false;
		}
	}
	return is_sort_finished;
}

void fillWithPattern(VBuffer* buffer, int offset_x, int offset_y, int screen_colour)
{
	Point inc = {offset_x, offset_y}, dec = { 0 };

	for(int i = 0, j = 0; i != VBUFFER_WIDTH; i++)
	{
		drawPixelToBufferFromPoint(buffer, newPixel(screen_colour, ' '), (Point){offset_x + i, offset_y + j});
		j++;
	}
}

char* getNumberAsHexChar(int num)
{
	static char buff[5] = "";
	sprintf(buff, "%x", num);
	return buff;
}

/*
	source for help with algorithm:
		https://en.wikipedia.org/wiki/Line_drawing_algorithm
*/
void drawLine_naiveAlgorithm(VBuffer* buffer, Point start, Point finish, PixelData pixel)
{
	int dx = finish.x - start.x;
	int dy = finish.y - start.y;
	drawPixelToBufferFromPoint(buffer, pixel, start);
	drawPixelToBufferFromPoint(buffer, pixel, finish);
	for(int x = start.x; x != finish.x; x++)
	{
		int y = start.y + dy * (x - start.x) / (dx + (dx == 0));
		
		int buff_text_index = 0;
		if(y > 0x0f){buff_text_index++;}
		drawPixelToBufferFromPoint(buffer, pixel, (Point){x, y});
	}
}

void drawLineJaive(VBuffer* buffer, Point start, Point finish, int screen_colour)
{

	/*
		This tracks the previous point to
		draw in the missing pixels
	*/
	Point last_point = { 0 };

	int dx = finish.x - start.x;
	int dy = finish.y - start.y;
	for(int x = start.x; x != finish.x; x++)
	{
		int y = start.y + dy * (x - start.x) / dx;

		int buff_text_index = 0;
		if(y > 0x0f){buff_text_index++;}
		Point next_point = {x, y};
		drawPixelToBufferFromPoint(buffer, newPixel(screen_colour, ' '), next_point);
	}
}

void drawRectangleFilled(VBuffer* buffer, Point start, Point finish, PixelData pixel_to_write)
{
	drawPixelToBufferFromPoint(buffer, pixel_to_write, start);
	drawPixelToBufferFromPoint(buffer, pixel_to_write, finish);

	for(int i_x = finish.x - start.x; i_x != -1; i_x--)
	{
		for(int i_y = finish.y - start.y; i_y != -1; i_y--)
		{
			drawPixelToBufferFromPoint(buffer, pixel_to_write, (Point){i_x, i_y});
		}
	}
}
void fillBufferWithPixels(VBuffer* buffer, PixelData pixel_to_fill_screen_with)
{
	drawRectangleFilled(buffer, (Point){0, 0}, (Point){VBUFFER_WIDTH, VBUFFER_WIDTH}, pixel_to_fill_screen_with);
}

void updateScreen(VBuffer* buffer, int delay)
{
	resetConsole(delay);
	drawBuffer(buffer, true, true);
}

#endif
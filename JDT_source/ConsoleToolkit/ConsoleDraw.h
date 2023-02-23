#ifndef CONSOLE_DRAW_H
#define CONSOLE_DRAW_H

#include <stdlib.h>
#include <stdio.h>
#include "ToolkitConsoleControlPanel.h"
#include "ConsoleColours.h"

typedef struct PixelData
{
	int screen_colour;
	char character;
}
PixelData;

PixelData newPixel(int screen_colour, char character)
{
	if(!getTerminalSettings()->disable_characters)
	{
		return (PixelData){screen_colour, character};
	}
	return (PixelData){screen_colour, ' '};
}

#define VBUFFER_WIDTH		(30)
//30 by 30 grid.
#define VBUFFER_DIMENSIONS 	(VBUFFER_WIDTH*VBUFFER_WIDTH)

typedef struct VBuffer
{
	int width;
	PixelData data[VBUFFER_DIMENSIONS];
}
VBuffer;

void drawBuffer(VBuffer* buffer, bool draw_border, bool lettered);

void initVbuffer(VBuffer* vbuffer, int width)
{
	printf("init: %p\n", vbuffer);
	vbuffer->width = width;
	printf("width: %d\n", vbuffer->width);
	for(int i = 0; i != vbuffer->width * vbuffer->width; i++)
	{
		vbuffer->data[i] = newPixel(BLACK, ' ');
	}
	// drawBuffer(vbuffer, true);
}

/*
Clears the screen using the linux command 'tput reset'.
The parameter: (int) 'sleep_time' is the amount of time
to wait before the screen actually clears. This is to
allow for the image to actually show before clearing it
off of the screen.
*/
void resetConsole(int sleep_time)
{
	char command_buffer[40];
	sprintf(command_buffer, "sleep 0.%d\n", sleep_time);
	printf("\n");
	system(command_buffer);
	system("tput reset\n");
}

void drawPixel(PixelData data)
{
	setScreenColour(data.screen_colour);
	printf("%c", data.character);
	if(getTerminalSettings()->double_spaced_draw)
	{
		printf("%c", data.character);
	}
}

PixelData getPixelDataFromBuffer(VBuffer* buffer, int x, int y)
{
	//i = x + width*y;
	if(x < 0){x *= -1;}
	if(y < 0){y *= -1;}
	return buffer->data[x + buffer->width * y];
}
typedef struct Point
{
	int x;
	int y;
}
Point, Dimensions;

Point newPoint(int x, int y)
{
	return (Point){x, y};
}
Dimensions newDimension(int width, int height)
{
	return (Dimensions){width, height};
}

int getClampedInt(int target, int min, int max)
{
	if(target 	< min	)
	{
		return min;
	}
	if(max 		< target)
	{
		return max;
	}
	return target;
}
int getWrappedInt(int target, int min, int max)
{
	if(target 	< min	)
	{
		return max - target;
	}
	if(max 		< target)
	{
		return min + (target - max);
	}
	return target;
}
void printPointInfo(Point* point)
{
	printf("x: %d, y: %d\n", point->x, point->y);
}
void handlePointWrapping(Point* point, bool* did_point_x_get_wrapped, bool* did_point_y_get_wrapped, int width)
{
	if(did_point_x_get_wrapped)
	{
		*did_point_x_get_wrapped = (point->x != getWrappedInt(point->x, 0, width-1));
	}
	if(did_point_y_get_wrapped)
	{
		*did_point_y_get_wrapped = (point->y != getWrappedInt(point->y, 0, width-1));
	}
	point->x = getWrappedInt(point->x, 0, width-1);
	point->y = getWrappedInt(point->y, 0, width-1);
}
void handlePointClamping(Point* point, bool* did_point_x_get_wrapped, bool* did_point_y_get_wrapped, int width)
{
	if(did_point_x_get_wrapped)
	{
		*did_point_x_get_wrapped = (point->x != getWrappedInt(point->x, 0, width-1));
	}
	if(did_point_y_get_wrapped)
	{
		*did_point_y_get_wrapped = (point->y != getWrappedInt(point->y, 0, width-1));
	}
	point->x = getClampedInt(point->x, 0, width-1);
	point->y = getClampedInt(point->y, 0, width-1);
}

int getArrayAccessFromPoint(Point point, int width)
{
	return point.x + width * point.y;
}
//returns the old value.
PixelData setPixelDataToBuffer(VBuffer* buffer, int x, int y, PixelData new_value)
{
	int double_array_to_single_array = getArrayAccessFromPoint((Point){x, y}, buffer->width);
	PixelData old = newPixel(WHITE, ' ');
	old = buffer->data[double_array_to_single_array];
	buffer->data[double_array_to_single_array] = new_value;
	//i = x + width*y;
	return old;
}
PixelData drawPixelToBufferFromPoint(VBuffer* buffer, PixelData pixel, Point point)
{
	handlePointWrapping(&point, NULL, NULL, buffer->width);
	handlePointClamping(&point, NULL, NULL, buffer->width);
	return setPixelDataToBuffer(buffer, point.x, point.y, pixel);
}

void drawBorderTop(bool draw_border, int buffer_width, bool lettered_top)
{
	if(getTerminalSettings()->double_spaced_draw){draw_border *= 2;}
	if(draw_border)
	{
		printf("\t");
		printf("/");
		if(lettered_top)
		{
			for(int i = 0; i != 2; i++)
			{
				for(int j = 0; j != buffer_width; j++)
				{
					char temp[3] = "";
					sprintf(temp, "%02d", j);
	
					if(getTerminalSettings()->double_spaced_draw)
					{
						setScreenColour(BLUE + !!(j % 2));
						printf(" ");
						setScreenColour(RESET);
					}
					printf("%c", temp[i]);
				}
				setScreenColour(RESET);
				char end_char[3] = {"\\|"};
				printf("%c\n", end_char[i]);
				if(!i)
				{
					printf("\t|");
				}
			}
		}
		else
		{
			printf("`");
			for(int i = 1; i != buffer_width - 1; i++)
			{
				printf("`");
			}
			printf("`");
			printf("\\");
		}
	}
}
void drawBorderBottom(bool draw_border, int buffer_width)
{
	if(draw_border)
	{
		printf("\t");
		printf("\\");
		printf("_");
		for(int i = 1; i != (buffer_width * (draw_border + draw_border)) - 1; i++)
		{
			printf("_");
		}
		printf("_");
		printf("/");
	}
	printf("\n");
}

void drawBufferContents(VBuffer* buffer, bool draw_border)
{
	for(int x = 0; x != buffer->width; x++)
	{
		printf("%02d\t", x);
		if(draw_border){printf("|");}
		for(int y = 0; y != buffer->width; y++)
		{
			// printf("x %d y %d\n", x, y);
			drawPixel(
						buffer->data[getArrayAccessFromPoint((Point){y, x}, buffer->width)]
					);
		}
		setScreenColour(RESET);

		if(draw_border){printf("|");}
		printf("\n");
	}
}

void drawBuffer(VBuffer* buffer, bool draw_border, bool lettered)
{

	printf("\ndrawBuffer %p\n", (void*)buffer);

	drawBorderTop(draw_border, buffer->width, lettered);
	drawBufferContents(buffer, draw_border);
	drawBorderBottom(draw_border, buffer->width);
}

void initConsoleDrawing(VBuffer* buffer, ArgumentContainer* args)
{
    (*getTerminalSettings()) = parseArgumentsForProgram(*args);
    initVbuffer(buffer, VBUFFER_WIDTH);
    resetConsole(0);
    drawBuffer(buffer, true, true);
}

void printTextIntoBuffer(VBuffer* buffer, int x, int y, int colour, char* str)
{
	for(int i = 0; str[i] != '\0'; i++)
	{
		if(str[i] == '\n' || (x + i) == buffer->width)
		{
			x -= i;
			y++;
		}
		drawPixelToBufferFromPoint(buffer, newPixel(colour, str[i]), (Point){x + i, y});
	}
}
#include "../ErrorSniffing.h"
void flipBufferContents(VBuffer* vbuffer, char mode)
{
	VBuffer temp;
	initVbuffer(&temp, vbuffer->width);
	for(int x = 0; x != vbuffer->width; x++)
	{
		for(int y = 0; y != vbuffer->width; y++)
		{
			drawPixelToBufferFromPoint(&temp, getPixelDataFromBuffer(vbuffer, ((vbuffer->width - 1) * (mode == 'x')) - x, ((vbuffer->width - 1) * (mode == 'y')) - y), (Point){x, y});
		}
	}
	for(int i = 0; i != vbuffer->width * vbuffer->width; i++)
	{
		vbuffer->data[i] = temp.data[i];
	}
	initVbuffer(&temp, vbuffer->width);
}

void saveBufferToDisk(char* filename)
{
	FILE* file = fopen(filename, "w+");
}

#endif
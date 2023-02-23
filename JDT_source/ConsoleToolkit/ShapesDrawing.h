#ifndef SHAPE_DRAWING_H
#define SHAPE_DRAWING_H

#include "PlotsWrapper.h"

void drawRectangle(Point top_left, Dimensions dimensions)
{
	for(int x = top_left.x; x != top_left.x + dimensions.x; x++)
	{
		plot(x, top_left.y, false);
		plot(x, top_left.y + dimensions.y, false);
	}
	
	for(int y = top_left.y + 1; y != top_left.y + dimensions.y; y++)
	{
		plot(top_left.x, y, false);
		plot((top_left.x + dimensions.x) - 1, y, false);
	}
}

void drawStar(Point center)
{
	plot(center.x, center.y - 1, false);
	
	plot(center.x + 2, center.y, false);
	plot(center.x + 1, center.y, false);
	plot(center.x, center.y, false);
	plot(center.x - 1, center.y, false);
	plot(center.x - 2, center.y, false);

	plot(center.x + 1, center.y + 1, false);
	plot(center.x, center.y + 1, false);
	plot(center.x - 1, center.y + 1, false);

	plot(center.x + 2, center.y + 2, false);
	plot(center.x - 2, center.y + 2, false);
}

void drawTriangle(Point a, Point b, Point c)
{
	plotLine(a.x, a.y, b.x, b.y, false);
	(*currentPixelData()) = newPixel(currentPixelData()->screen_colour + 1, currentPixelData()->character - 1);
	plotLine(c.x, c.y, a.x, a.y, false);
	(*currentPixelData()) = newPixel(currentPixelData()->screen_colour + 3, currentPixelData()->character - 2);
	plotLine(b.x, b.y, c.x, c.y, false);
}

#endif
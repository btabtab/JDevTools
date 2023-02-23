#ifndef XIAOLIN_WU_DRAW_H
#define XIAOLIN_WU_DRAW_H

#include "ConsoleDraw.h"

#include <math.h>

/*
	Directly taken from: https://en.wikipedia.org/wiki/Xiaolin_Wu%27s_line_algorithm
	Like, I just copied the psuedocode and ported it to C.
*/

void plotADV(VBuffer* buffer, float x, float y, PixelData pixel, float brightness)
{
	drawPixelToBufferFromPoint(buffer, newPixel(!pixel.screen_colour, pixel.character), (Point){x, y});
	// plot the pixel at (x, y) with brightness c (where 0 ≤ c ≤ 1);
}

// integer part of x
int ipart(float x)
{
	return (int)x;
}

// float round(float x)
// {
// 	return ipart(x + 0.5);
// }

// fractional part of x
float fpart(float x)
{
	return x - ipart(x);
}

float rfpart(float x)
{
	return 1 - fpart(x);
}

void swap(float* a, float* b)
{
	float c = *a;
	(*a) = (*b);
	(*b) = c;
}

void spXiaolinDraw(VBuffer* buffer, float x0,float y0,float x1,float y1)
{
	bool steep = fabsf(y1 - y0) > fabs(x1 - x0);
	
	if(steep)
	{
		swap(&x0, &y0);
		swap(&x1, &y1);
	}
	if(x0 > x1)
	{
		swap(&x0, &x1);
		swap(&y0, &y1);
	}
	
	int dx = x1 - x0;
	int dy = y1 - y0;

	float gradient;

	if (dx == 0.0)
	{
		gradient = 1.0;
	}
	else
	{
		gradient = dy / dx;
	}

	// handle first endpoint
	float xend = roundf(x0);
	float yend = y0 + gradient * (xend - x0);
	float xgap = rfpart(x0 + 0.5);
	float xpxl1 = xend; // this will be used in the main loop
	float ypxl1 = ipart(yend);

	if(steep)
	{
		plotADV(buffer, ypxl1,   xpxl1, newPixel(rfpart(yend) * xgap, ' '), 0);
		plotADV(buffer, ypxl1+1, xpxl1,  newPixel(fpart(yend) * xgap, ' '), 0);
	}
	else
	{
		plotADV(buffer, xpxl1, ypxl1  , newPixel(rfpart(yend) * xgap, ' '), 0);
		plotADV(buffer, xpxl1, ypxl1+1,  newPixel(fpart(yend) * xgap, ' '), 0);
	}
	float intery = yend + gradient; // first y-intersection for the main loop
	
	// handle second endpoint
	xend = roundf(x1);
	yend = y1 + gradient * (xend - x1);
	xgap = fpart(x1 + 0.5);
	float xpxl2 = xend; //this will be used in the main loop
	float ypxl2 = ipart(yend);
	if(steep)
	{
		plotADV(buffer, ypxl2  , xpxl2, newPixel(rfpart(yend) * xgap, ' '), 0);
		plotADV(buffer, ypxl2+1, xpxl2,  newPixel(fpart(yend) * xgap, ' '), 0);
	}
	else
	{
		plotADV(buffer, xpxl2, ypxl2,  newPixel(rfpart(yend) * xgap, ' '), 0);
		plotADV(buffer, xpxl2, ypxl2+1, newPixel(fpart(yend) * xgap, ' '), 0);
	}
	
	// main loop
	if(steep)
	{
		for(int x = xpxl1 + 1; x != xpxl2 - 1; x++)
		{
			plotADV(buffer, ipart(intery)  , x, newPixel(rfpart(intery) * xgap, ' '), 0);
			plotADV(buffer, ipart(intery)+1, x,  newPixel(fpart(intery) * xgap, ' '), 0);
			intery = intery + gradient;
		}
	}
	else
	{
		// for( x from xpxl1 + 1 to xpxl2 - 1 do)
		for(int x = xpxl1 + 1; x != xpxl2 - 1; x++)
		{
			plotADV(buffer, x, ipart(intery),  newPixel(rfpart(intery) * xgap, ' '), 0);
			plotADV(buffer, x, ipart(intery)+1, newPixel(fpart(intery) * xgap, ' '), 0);
			intery = intery + gradient;
		}
	}
}

#endif
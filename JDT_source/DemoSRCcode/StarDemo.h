#ifndef STARDEMO_H
#define STARDEMO_H

#include "../ConsoleToolkit/ConsoleDraw.h"

void drawStarTileOnVbuffer(VBuffer* buffer, int start_x, int start_y)
{
    for(int x = 0; x != 5; x++)
    {
        for(int y = 0; y != 5; y++)
        {
            buffer->data[(start_x + x) + (buffer->width * (start_y + y))] = newPixel(YELLOW, 'O');
        }
    }
}

#endif
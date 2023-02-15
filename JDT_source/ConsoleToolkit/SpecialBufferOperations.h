#ifndef SPECIAL_BUFFER_OPERATIONS_H
#define SPECIAL_BUFFER_OPERATIONS_H

#include "ConsoleDraw.h"

PixelData searchForFirstCharacter(VBuffer* buffer, char target_char)
{
    for(int i = VBUFFER_DIMENSIONS; i != -1; i--)
    {
        if(buffer->data[i].character == target_char)
        {
            return buffer->data[i];
        }
    }
    return newPixel(0, 0);
}

PixelData searchForFirstColour(VBuffer* buffer, int target_colour)
{
    for(int i = VBUFFER_DIMENSIONS; i != -1; i--)
    {
        if(buffer->data[i].screen_colour == target_colour)
        {
            return buffer->data[i];
        }
    }
    return newPixel(0, 0);
}

void replaceAllInstanceOfColoursInBuffer(VBuffer* buffer, int old_colour, int new_colour)
{
    for(int i = VBUFFER_DIMENSIONS; i != -1; i--)
    {
        if(buffer->data[i].screen_colour == old_colour)
        {
            buffer->data[i].screen_colour = new_colour;
        }
    }
}

#endif
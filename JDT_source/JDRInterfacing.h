#ifndef JDR_INTERFACE_H
#define JDR_INTERFACE_H

#include "../JDevRendering/jdr_base_functions.h"

#include "ConsoleToolkit/PlotsWrapper.h"

void jdr_plot(int x, int y, Colour colour)
{
    setScreenColour((int)colour);
    plot(x, y, false);
}
void jdr_clearScreen()
{
    plotsResetBuffer();
}

#endif
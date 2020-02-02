#ifndef _pos2d_h
#define _pos2d_h

#include "numerics.h"

struct Pos2D
{
    Pos2D(int xPos, int yPos) : x(xPos), y(yPos) {}
    Ui x, y;
};

#endif /* _pos2d_h */
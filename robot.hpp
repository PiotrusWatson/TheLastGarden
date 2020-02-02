#ifndef _robot_hpp
#define _robot_hpp

#include <string>
using namespace std;


struct Robot
{
    enum Direction : int
    {
        UP, DOWN, LEFT, RIGHT
    };

    Robot() : x(0), y(0), energy(0) {}
    Robot(int xPos, int yPos) : x(xPos), y(yPos), energy(0) {}
    
    int x, y, energy;
    int dir;
};



#endif _robot_hpp
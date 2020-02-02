#ifndef robot_h
#define robot_h

#include <string>
#include "tiles.hpp"
#include "tilemap.h"
using namespace std;


struct Robot
{
    enum Direction : int
    {
        UP, DOWN, LEFT, RIGHT, NONE
    };

    Robot() : x(9), y(2), energy(20), seeds(3), oldDir(NONE), dir(RIGHT){}
    Robot(int xPos, int yPos) : x(xPos), y(yPos), energy(0) {}
    
    int x, y, energy, seeds;
    int dirx = 0, diry = 0;
    int dir, oldDir;

    void move(int direction, Tilemap<Ground> & g, Tilemap<Plant> & p, Tilemap<Obstacle> & o);

    //simple substraction on the energy
    int loseEnergy(int amount);
};



#endif 
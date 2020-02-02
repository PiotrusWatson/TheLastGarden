#ifndef robot_h
#define robot_h

#include <string>
#include "tiles.hpp"
using namespace std;


struct Robot
{
    enum Direction : int
    {
        UP, DOWN, LEFT, RIGHT, NONE
    };

    Robot() : x(5), y(5), energy(20), seeds(3), oldDir(NONE), dir(RIGHT){}
    Robot(int xPos, int yPos) : x(xPos), y(yPos), energy(0) {}
    
    int x, y, energy, seeds;
    int dirx, diry;
    int dir, oldDir;

    void move(int direction, vector<vector<Ground>> g, vector<vector<Plant>> p, vector<vector<Obstacle>> o);

    //simple substraction on the energy
    int loseEnergy(int amount);
};



#endif 
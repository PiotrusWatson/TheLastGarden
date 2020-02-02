#include <string>
#include <vector>
#include "robot.hpp"

using namespace std;

void Robot::move(int direction)
{
    
    
    switch(direction){
        case Direction::UP: 
            if (oldDir == direction) x -= 1;  
            dirx = x-1; diry = y;
            break;
        case Direction::DOWN: 
            if (oldDir == direction) x += 1;
            dirx = x+1; diry = y;
            break; 
        case Direction::LEFT: 
            if (oldDir == direction) y -= 1;
            dirx = x; diry = y-1;
            break; 
        case Direction::RIGHT: 
            if (oldDir == direction) y += 1;
            dirx = x; diry = y+1;
            break; 
        default:
            break;
    }

    if(oldDir != direction)
    {
        oldDir = direction;
    }
    

    
};


int Robot::loseEnergy(int amount){
    energy -= amount;
    return energy; 
};



#include <string>
#include <vector>
#include "robot.hpp"
#include "tiles.hpp"

using namespace std;

void Robot::move(int direction, vector<vector<Ground>> g, vector<vector<Plant>> p, vector<vector<Obstacle>> o)
{
    
    
    switch(direction){
        case Direction::UP: 
            if (oldDir == direction && isWalkable(dirx, diry, g, p, o)) x -= 1;  
            dirx = x-1; diry = y;
            break;
        case Direction::DOWN: 
            if (oldDir == direction && isWalkable(dirx, diry, g, p, o)) x += 1;
            dirx = x+1; diry = y;
            break; 
        case Direction::LEFT: 
            if (oldDir == direction && isWalkable(dirx, diry, g, p, o)) y -= 1;
            dirx = x; diry = y-1;
            break; 
        case Direction::RIGHT: 
            if (oldDir == direction && isWalkable(dirx, diry, g, p, o)) y += 1;
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



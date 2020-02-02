#include <string>
#include <vector>
#include "robot.hpp"
#include "tiles.hpp"
#include "tilemap.h"
#include "debug.h"

using namespace std;

void Robot::move(int direction, Tilemap<Ground> g, Tilemap<Plant> p, Tilemap<Obstacle> o)
{
    Ground * g2 = g.get(dirx, diry);
    if (g2 == nullptr) MX_LOG(dirx << ", " << diry);

    Ground ground = *(g.get(dirx, diry));
    Plant plant = *(p.get(dirx, diry));
    Obstacle obstacle = *(o.get(dirx, diry));

    switch(direction){
        case Direction::UP: 
            if (oldDir == direction && isWalkable(ground, plant, obstacle)) x -= 1;  
            dirx = x-1; diry = y;
            break;
        case Direction::DOWN: 
            if (oldDir == direction && isWalkable(ground, plant, obstacle)) x += 1;
            dirx = x+1; diry = y;
            break;
        case Direction::LEFT: 
            if (oldDir == direction && isWalkable(ground, plant, obstacle)) y -= 1;
            dirx = x; diry = y-1;
            break; 
        case Direction::RIGHT: 
            if (oldDir == direction && isWalkable(ground, plant, obstacle)) y += 1;
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



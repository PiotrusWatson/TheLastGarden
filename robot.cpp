#include <string>
#include <vector>
#include <stdlib.h>
#include "robot.hpp"
#include "tiles.hpp"
#include "tilemap.h"
#include "debug.h"

using namespace std;

void Robot::move(int direction, Tilemap<Ground> & g, Tilemap<Plant> & p, Tilemap<Obstacle> & o)
{
    Ground ground = *(g.get(diry, dirx));
    Plant plant = *(p.get(diry, dirx));
    Obstacle obstacle = *(o.get(diry, dirx));

    

    switch(direction){
        case Direction::UP: 
            if (oldDir == direction && isWalkable(ground, plant, obstacle)) 
            {
                x -= 1; 
                count++;
            }  
            dirx = x-1; diry = y;
            break;
        case Direction::DOWN: 
            if (oldDir == direction && isWalkable(ground, plant, obstacle)){ x += 1;count++;}
            dirx = x+1; diry = y;
            break;
        case Direction::LEFT: 
            if (oldDir == direction && isWalkable(ground, plant, obstacle)) {y -= 1; count++;}
            dirx = x; diry = y-1;
            break; 
        case Direction::RIGHT: 
            if (oldDir == direction && isWalkable(ground, plant, obstacle)) {y += 1;count++;}
            dirx = x; diry = y+1;
            break; 
        default:
            break;
    }

    if(oldDir != direction)
    {
        oldDir = direction;
    }
    
    if(count>5){
        for(int i=0; i<11; i++){
            for(int j=0; j<11; j++){
                switch(*(p.get(i, j)))
                {
                    case Plant::LANDSEED: 
                        p.set(i,j,Plant::LANDSMALL);
                        break;
                    case Plant::LANDSMALL: 
                        p.set(i,j,Plant::LANDBIG);
                        break;
                    case Plant::WATERSEED: 
                        p.set(i,j,Plant::WATERSMALL);
                        break;
                    case Plant::WATERSMALL: 
                        p.set(i,j,Plant::WATERBIG);
                        break;
                    default:
                    break;
                    
                }
            }    
        }
        count = 0;
    }
    
};


int Robot::loseEnergy(int amount){
    energy -= amount;
    return energy; 
};

void Robot::plantTree(Tilemap<Ground> & g, Tilemap<Plant> & p)
{
    Ground ground = *(g.get(diry, dirx));



    if(ground == Ground::ALIVE)
    {
        int random = rand()%2;

        random == 1 ? p.set(diry, dirx, Plant::LANDSEED) : p.set(diry, dirx, Plant::WATERSEED);  
        
    }
}



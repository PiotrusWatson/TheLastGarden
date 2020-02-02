#include <string>
#include <vector>
#include "robot.hpp"

using namespace std;

void Robot::move(){
    //require pressing twice the same direction to move
    if(oldDir != dir)
    {
        oldDir = dir;
    }
    else
    {
        switch(dir)
        {
            case Direction::UP: x -= 1; 
                break;
            case Direction::DOWN: x += 1;
                break; 
            case Direction::LEFT: y -= 1;
                break; 
            case Direction::RIGHT: y += 1;
                break; 
            default:
                break;

        }
        
        loseEnergy(4);
        oldDir = NONE;
    }
};

int Robot::loseEnergy(int amount){
    energy -= amount;
    return energy; 
}

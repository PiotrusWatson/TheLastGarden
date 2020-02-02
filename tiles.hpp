#ifndef _tiles_hpp
#define _tiles_hpp

#include <string>
using namespace std;


enum class Ground { ALIVE, 
    DEAD, 
    FENCE_STRAIGHT_TOP, 
    FENCE_STRAIGHT_LEFT, 
    FENCE_STRAIGHT_BOTTOM, 
    FENCE_STRAIGHT_RIGHT, 
    FENCE_CORNER_TOP_LEFT,
    FENCE_CORNER_TOP_RIGHT,
    FENCE_CORNER_BOTTOM_LEFT,
    FENCE_CORNER_BOTTOM_RIGHT,
    WATER_MIDDLE,
    WATER_STRAIGHT_TOP, 
    WATER_STRAIGHT_LEFT, 
    WATER_STRAIGHT_BOTTOM, 
    WATER_STRAIGHT_RIGHT, 
    WATER_CORNER_TOP_LEFT,
    WATER_CORNER_TOP_RIGHT,
    WATER_CORNER_BOTTOM_LEFT,
    WATER_CORNER_BOTTOM_RIGHT,
    NONE
    };

string groundToString (Ground ground);


enum class Plant { LANDSEED, LANDSMALL, LANDBIG, WATERSEED, WATERSMALL, WATERBIG, GENERATOR, NONE };

//pair<string, pair<int, int>> plantToString (Plant plant);
string plantToString(Plant plant);

enum class Obstacle { SMOG, FIRE, RADIATION, NONE };

string obstacleToString (Obstacle obstacle);

#endif
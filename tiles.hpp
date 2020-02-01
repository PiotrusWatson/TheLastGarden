#ifndef _tiles_hpp
#define _tiles_hpp

#include <string>
using namespace std;


enum class Ground { ALIVE, DEAD, FENCE };

string groundToString (Ground ground);


enum class Plant { LANDSEED, LANDSMALL, LANDBIG, WATERSEED, WATERSMALL, WATERBIG };

pair<string, pair<int, int>> plantToString (Plant plant);


enum class Obstacle { SMOG, FIRE, RADIATION };

string obstacleToString (Obstacle obstacle);

#endif
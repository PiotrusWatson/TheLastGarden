#include <string>
#include <vector>

using namespace std;



enum class Ground {
    ALIVE, 
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

string groundToString (Ground ground)
{
    switch (ground)
    {
        case Ground::ALIVE: return "Assets/Images/Ground_Neutral.png";
        case Ground::DEAD: return "Assets/Images/Dead-Ground.png";
        case Ground::FENCE_STRAIGHT_TOP: return "Assets/Images/Fence-Plus-Dead-Ground-1.png";
        case Ground::FENCE_STRAIGHT_LEFT: return "Assets/Images/Fence-Plus-Dead-Ground-2.png";
        case Ground::FENCE_STRAIGHT_BOTTOM: return "Assets/Images/Fence-Plus-Dead-Ground-3.png";
        case Ground::FENCE_STRAIGHT_RIGHT: return "Assets/Images/Fence-Plus-Dead-Ground-4.png";
        case Ground::FENCE_CORNER_TOP_LEFT: return "Assets/Images/Fence-Plus-Dead-Ground-7.png";
        case Ground::FENCE_CORNER_TOP_RIGHT: return "Assets/Images/Fence-Plus-Dead-Ground-8.png";
        case Ground::FENCE_CORNER_BOTTOM_LEFT: return "Assets/Images/Fence-Plus-Dead-Ground-6.png";
        case Ground::FENCE_CORNER_BOTTOM_RIGHT: return "Assets/Images/Fence-Plus-Dead-Ground-5.png";
        case Ground::WATER_MIDDLE: return "Assets/Images/Water-Pond-9.png"; 
        case Ground::WATER_STRAIGHT_TOP: return "Assets/Images/Water-Pond-5.png";
        case Ground::WATER_STRAIGHT_LEFT: return "Assets/Images/Water-Pond-8.png";
        case Ground::WATER_STRAIGHT_BOTTOM: return "Assets/Images/Water-Pond-7.png";
        case Ground::WATER_STRAIGHT_RIGHT: return "Assets/Images/Water-Pond-6.png";
        case Ground::WATER_CORNER_TOP_LEFT: return "Assets/Images/Water-Pond-1.png";
        case Ground::WATER_CORNER_TOP_RIGHT: return "Assets/Images/Water-Pond-2.png";
        case Ground::WATER_CORNER_BOTTOM_LEFT: return "Assets/Images/Water-Pond-4.png";
        case Ground::WATER_CORNER_BOTTOM_RIGHT: return "Assets/Images/Water-Pond-3.png";
        
    }
}

bool isWalkableGround (Ground ground)
{
    switch (ground) 
    {
        case Ground::ALIVE:
        case Ground::DEAD:
        case Ground::NONE: 
            return true;
        default:
            return false;
    }
}

//Interactible Objects: Plants and Generator
enum class Plant { LANDSEED, LANDSMALL, LANDBIG, WATERSEED, WATERSMALL, WATERBIG, GENERATOR, NONE };


string plantToString (Plant plant)
{
    switch (plant)
    {
        case Plant::LANDSEED: return "Assets/Images/Trees-1.png";
        case Plant::LANDSMALL: return "Assets/Images/Trees-2.png";
        case Plant::LANDBIG: return "Assets/Images/Trees-3.png";
        case Plant::WATERSEED: return "Assets/Images/Trees-4.png";
        case Plant::WATERSMALL: return "Assets/Images/Trees-5.png";
        case Plant::WATERBIG: return "Assets/Images/Trees-6.png";
        case Plant::GENERATOR: return "Assets/Images/Generator.png";
    }
}

bool isPlantNone (Plant plant)
{
    return plant == Plant::NONE;
}


enum class Obstacle { SMOG, FIRE, RADIATION, NONE };

string obstacleToString (Obstacle obstacle)
{
    switch (obstacle)
    {
        case Obstacle::SMOG : return "Assets/Images/smog.png";
        case Obstacle::FIRE : return "Assets/Images/fire_anim-1.png"; // TODO: needs to change to be animated
        case Obstacle::RADIATION : return "Assets/Images/radiation.png";
    }
}

// could also be used to see if there is an obstacle to work on
bool isObstacleNone (Obstacle obstacle)
{
    return obstacle == Obstacle::NONE;
}



bool isWalkable (int x, int y, vector<vector<Ground>> g, vector<vector<Plant>> p, vector<vector<Obstacle>> o)
{
    return isWalkableGround(g[x][y]) && isPlantNone(p[x][y]) && isObstacleNone(o[x][y]);
}



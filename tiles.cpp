#include <string>

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
    FENCE_CORNER_BOTTOM_RIGHT
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
    }
}


enum class Plant { LANDSEED, LANDSMALL, LANDBIG, WATERSEED, WATERSMALL, WATERBIG };

// struct Sprite
// {
//     Sprite(const std::string & name, int xpos, int ypos) : texture(name), x(xpos), y(ypos) {}
//     std::string texture;
//     int x, y;
// };

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
    }
}


enum class Obstacle { SMOG, FIRE, RADIATION };

string obstacleToString (Obstacle obstacle)
{
    switch (obstacle)
    {
        case Obstacle::SMOG : return "Assets/Images/smog.png";
        case Obstacle::FIRE : return "Assets/Images/fire-anim.png"; // TODO: needs to change to be animated
        case Obstacle::RADIATION : return "Assets/Images/radiation.png";
    }
}
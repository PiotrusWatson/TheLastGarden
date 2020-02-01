#include <string>

using namespace std;



enum class Ground { ALIVE, DEAD, FENCE };

string groundToString (Ground ground)
{
    switch (ground)
    {
        case Ground::ALIVE: return "Assets/Images/Ground_Neutral.png";
        case Ground::DEAD: return "Assets/Images/Dead-Ground.png";
        case Ground::FENCE: return "Assets/Images/Fence-Plus-Dead-Ground.png";
    }
}


enum class Plant { LANDSEED, LANDSMALL, LANDBIG, WATERSEED, WATERSMALL, WATERBIG };

pair<string, pair<int, int>> plantToString (Plant plant)
{
    switch (plant)
    {
        case Plant::LANDSEED: return pair<string, pair<int, int>>("Assets/Images/Trees.png", pair<int, int>(0, 0));
        case Plant::LANDSMALL: return pair<string, pair<int, int>>("Assets/Images/Trees.png", pair<int, int>(0, 1));
        case Plant::LANDBIG: return pair<string, pair<int, int>>("Assets/Images/Trees.png", pair<int, int>(0, 2));
        case Plant::WATERSEED: return pair<string, pair<int, int>>("Assets/Images/Trees.png", pair<int, int>(1, 0));
        case Plant::WATERSMALL: return pair<string, pair<int, int>>("Assets/Images/Trees.png", pair<int, int>(1, 1));
        case Plant::WATERBIG: return pair<string, pair<int, int>>("Assets/Images/Trees.png", pair<int, int>(1, 2));
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
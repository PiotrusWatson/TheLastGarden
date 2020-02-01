#include "engine.hpp"
#include "state.h"
#include <utility>
#include <vector>

using namespace std;

void render_scaled (Engine * engine, const std::string & file, int x, int y);

const int TILE_SIZE = 16;
const int GLOBAL_SCALE = 4;
const string PLAYER_SPRITE = "Assets/Images/Robot_Idle.png"; // TODO: needs to be animated
// PLACEHOLDER MAP SIZE
const int xNumOfTiles = 11, yNumOfTiles = 11;



////////////////////////////////////////////////////////////////////
// ENUMS
////////////////////////////////////////////////////////////////////
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


////////////////////////////////////////////////////////////////////
// LEVEL DESIGN
////////////////////////////////////////////////////////////////////

const vector<Ground> GROUND_LEVEL = {Ground::DEAD};


////////////////////////////////////////////////////////////////////
// TEST STATE
////////////////////////////////////////////////////////////////////



class Test_State : public State
{
public:
    bool init() override { return true; }
    void update() override {}
    void render() override
    {
        Ground g = Ground::ALIVE;


        // render_scaled(engine(), groundToString(g), 64, 64);
        // drawDeadGround(engine(), xNumOfTiles + 6, yNumOfTiles + 6);
    }
    void on_keydown(Si32 key) override
    {
        if (key == SDLK_ESCAPE) engine()->switch_state("test2");
    }
};





////////////////////////////////////////////////////////////////////
// HELPERS
////////////////////////////////////////////////////////////////////

void render_scaled (Engine * engine, const std::string & file, int x, int y)
{
    engine->render_texture(file, x, y, GLOBAL_SCALE, GLOBAL_SCALE);
}



////////////////////////////////////////////////////////////////////
// MAIN APPLICATION
////////////////////////////////////////////////////////////////////

int main(int argc, const char * argv[])
{
    int xScreenSize = xNumOfTiles * TILE_SIZE * GLOBAL_SCALE;
    int yScreenSize = yNumOfTiles * TILE_SIZE * GLOBAL_SCALE;

    Engine engine("The Last Garden", xScreenSize, yScreenSize, Engine::WINDOWED);
    Test_State state;

    engine.push_state("test", &state);
    return engine.execute("test");
}
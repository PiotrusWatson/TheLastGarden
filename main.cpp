#include "engine.hpp"
#include "state.h"
#include <utility>
#include <vector>
#include "tiles.hpp"

using namespace std;

void render_scaled (Engine * engine, const std::string & file, int x, int y);

const int TILE_SIZE = 16;
const int GLOBAL_SCALE = 4;
const string PLAYER_SPRITE = "Assets/Images/Robot_Idle.png"; // TODO: needs to be animated
// PLACEHOLDER MAP SIZE
const int xNumOfTiles = 11, yNumOfTiles = 11;


////////////////////////////////////////////////////////////////////
// LEVEL DESIGN
////////////////////////////////////////////////////////////////////

const vector<Ground> GROUND_LEVEL = {Ground::DEAD};


////////////////////////////////////////////////////////////////////
// TEST STATE
////////////////////////////////////////////////////////////////////

#include "debug.h"

class Test_State : public State
{

public:

    
    bool init() override
    { 
        MX_LOG("Init called!");
        return true; 
    }
    void update() override {}
    void render() override
    {
        
        Ground g = Ground::ALIVE;
        if(g != Ground::NONE) render_scaled(engine(), groundToString(g), 64, 64);
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
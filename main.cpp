#include "engine.hpp"
#include "state.h"
#include <utility>
#include <vector>
#include "tiles.hpp"
#include "robot.hpp"
#include "debug.h"

using namespace std;

void render_scaled (Engine * engine, const std::string & file, int x, int y);

const int TILE_SIZE = 16;
const int GLOBAL_SCALE = 4;
const string PLAYER_SPRITE = "Assets/Images/Robot_Idle-5.png"; // TODO: needs to be animated
// PLACEHOLDER MAP SIZE
const int xNumOfTiles = 11, yNumOfTiles = 11;


////////////////////////////////////////////////////////////////////
// LEVEL DESIGN
////////////////////////////////////////////////////////////////////

//initialzie ground layer here, currently set up to fill 11x11
const vector<vector<Ground>> GROUND_LEVEL = {{Ground::FENCE_CORNER_TOP_LEFT, Ground::FENCE_STRAIGHT_TOP, Ground::FENCE_STRAIGHT_TOP, Ground::FENCE_STRAIGHT_TOP,Ground::FENCE_STRAIGHT_TOP, Ground::FENCE_STRAIGHT_TOP, Ground::FENCE_STRAIGHT_TOP, Ground::FENCE_STRAIGHT_TOP,Ground::FENCE_STRAIGHT_TOP, Ground::FENCE_STRAIGHT_TOP, Ground::FENCE_CORNER_TOP_RIGHT},
                                            {Ground::FENCE_STRAIGHT_LEFT, Ground::ALIVE, Ground::ALIVE, Ground::ALIVE,Ground::ALIVE, Ground::ALIVE, Ground::ALIVE, Ground::ALIVE,Ground::ALIVE, Ground::ALIVE, Ground::FENCE_STRAIGHT_RIGHT},
                                            {Ground::FENCE_STRAIGHT_LEFT, Ground::ALIVE, Ground::ALIVE, Ground::ALIVE,Ground::ALIVE, Ground::ALIVE, Ground::ALIVE, Ground::ALIVE,Ground::ALIVE, Ground::ALIVE, Ground::FENCE_STRAIGHT_RIGHT},
                                            {Ground::FENCE_STRAIGHT_LEFT, Ground::ALIVE, Ground::ALIVE, Ground::ALIVE,Ground::ALIVE, Ground::ALIVE, Ground::ALIVE, Ground::ALIVE,Ground::ALIVE, Ground::ALIVE, Ground::FENCE_STRAIGHT_RIGHT},
                                            {Ground::FENCE_STRAIGHT_LEFT, Ground::ALIVE, Ground::ALIVE, Ground::ALIVE,Ground::ALIVE, Ground::ALIVE, Ground::ALIVE, Ground::ALIVE,Ground::ALIVE, Ground::ALIVE, Ground::FENCE_STRAIGHT_RIGHT},
                                            {Ground::FENCE_STRAIGHT_LEFT, Ground::ALIVE, Ground::ALIVE, Ground::ALIVE,Ground::ALIVE, Ground::ALIVE, Ground::ALIVE, Ground::ALIVE,Ground::ALIVE, Ground::ALIVE, Ground::FENCE_STRAIGHT_RIGHT},
                                            {Ground::FENCE_STRAIGHT_LEFT, Ground::ALIVE, Ground::ALIVE, Ground::ALIVE,Ground::ALIVE, Ground::ALIVE, Ground::ALIVE, Ground::ALIVE,Ground::ALIVE, Ground::ALIVE, Ground::FENCE_STRAIGHT_RIGHT},
                                            {Ground::FENCE_STRAIGHT_LEFT, Ground::ALIVE, Ground::ALIVE, Ground::ALIVE,Ground::ALIVE, Ground::ALIVE, Ground::ALIVE, Ground::ALIVE,Ground::ALIVE, Ground::ALIVE, Ground::FENCE_STRAIGHT_RIGHT},
                                            {Ground::FENCE_STRAIGHT_LEFT, Ground::ALIVE, Ground::ALIVE, Ground::ALIVE,Ground::ALIVE, Ground::ALIVE, Ground::ALIVE, Ground::ALIVE,Ground::ALIVE, Ground::ALIVE, Ground::FENCE_STRAIGHT_RIGHT},
                                            {Ground::FENCE_STRAIGHT_LEFT, Ground::ALIVE, Ground::ALIVE, Ground::ALIVE,Ground::ALIVE, Ground::ALIVE, Ground::ALIVE, Ground::ALIVE,Ground::ALIVE, Ground::ALIVE, Ground::FENCE_STRAIGHT_RIGHT},
                                            {Ground::FENCE_CORNER_BOTTOM_LEFT, Ground::FENCE_STRAIGHT_BOTTOM, Ground::FENCE_STRAIGHT_BOTTOM, Ground::FENCE_STRAIGHT_BOTTOM,Ground::FENCE_STRAIGHT_BOTTOM, Ground::FENCE_STRAIGHT_BOTTOM, Ground::FENCE_STRAIGHT_BOTTOM, Ground::FENCE_STRAIGHT_BOTTOM,Ground::FENCE_STRAIGHT_BOTTOM, Ground::FENCE_STRAIGHT_BOTTOM, Ground::FENCE_CORNER_BOTTOM_LEFT},};

//initialize xNumOfTile*yNumOfTiles sized vectors with NONE
//Note: removed const because those layers are modified later on
vector<vector<Plant>> plantLevel(xNumOfTiles, vector<Plant>(yNumOfTiles, Plant::NONE));
vector<vector<Obstacle>> obstacleLevel(xNumOfTiles, vector<Obstacle>(yNumOfTiles, Obstacle::NONE));
                                    

////////////////////////////////////////////////////////////////////
// TEST STATE
////////////////////////////////////////////////////////////////////



class Test_State : public State
{


public:

    Robot rob;

    bool init() override
    { 
        //initialize map
        plantLevel[9][1] = Plant::GENERATOR;
        rob = Robot();

        return true; 
    }

    void on_enter() override
    {
        engine()->play_music("Assets/Music/Theme.mp3");    
    }

    void on_leave() override
    {
        engine()->stop_music();
    }


    void update() override {}
    void render() override
    {

        //iterate through every tile of the State
        for(int i=0; i<yNumOfTiles; i++)
        {
            for(int j=0; j<xNumOfTiles; j++)
            {

                Ground ground = GROUND_LEVEL[i][j];
                Plant plant =  plantLevel[i][j];
                Obstacle obstacle = obstacleLevel[i][j];
                
                if(ground != Ground::NONE) render_scaled(engine(), groundToString(ground), j*64, i*64 ); 
                if(plant != Plant::NONE) render_scaled(engine(), plantToString(plant), j*64, i*64 );
                if(obstacle != Obstacle::NONE) render_scaled(engine(), obstacleToString(obstacle), j*64, i*64 ); 
            }    

        }

        render_scaled(engine(), PLAYER_SPRITE, rob.y * 64, rob.x *64);
        render_scaled(engine(), obstacleToString(Obstacle::FIRE), rob.diry * 64, rob.dirx *64);
        // drawDeadGround(engine(), xNumOfTiles + 6, yNumOfTiles + 6);
    }
    void on_keydown(Si32 key) override
    {
        //Switch Statement to check for keys
        //Gives the direction of the robot and calculate coordinate of the next tile
        if (key == SDLK_ESCAPE) engine()->switch_state("test2");
        switch(key)
        {
            case SDLK_ESCAPE: 
                engine()->switch_state("test2");
                break;
            case SDLK_UP: 
                rob.dir = Robot::UP; 
                rob.dirx = rob.x - 1; rob.diry = rob.y; 
                break;
            case SDLK_DOWN: 
                rob.dir = Robot::DOWN;
                rob.dirx = rob.x + 1; rob.diry = rob.y; 
                break;
            case SDLK_LEFT: 
                rob.dir = Robot::LEFT; 
                rob.dirx = rob.x; rob.diry = rob.y-1;
                break;
            case SDLK_RIGHT: 
                rob.dir = Robot::RIGHT; 
                rob.dirx = rob.x; rob.diry = rob.y+1;
                break;
            default: break;
        }
        
        rob.move();
        
    }
private:
    Text_ID text;
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
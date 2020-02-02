#include "engine.hpp"
#include "state.h"
#include <utility>
#include <vector>
#include <string>
#include "tiles.hpp"
#include "robot.hpp"
#include "debug.h"
#include "animation.hpp"
#include "tilemap.h"
#include "debug.h"
#include "numerics.h"
#include "title_state.h"
#include "text_state.h"

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
const vector<vector<Ground>> groundLevel = {{Ground::FENCE_CORNER_TOP_LEFT, Ground::FENCE_STRAIGHT_TOP, Ground::FENCE_STRAIGHT_TOP, Ground::FENCE_STRAIGHT_TOP,Ground::FENCE_STRAIGHT_TOP, Ground::FENCE_STRAIGHT_TOP, Ground::FENCE_STRAIGHT_TOP, Ground::FENCE_STRAIGHT_TOP,Ground::FENCE_STRAIGHT_TOP, Ground::FENCE_STRAIGHT_TOP, Ground::FENCE_CORNER_TOP_RIGHT},
                                            {Ground::FENCE_STRAIGHT_LEFT, Ground::WATER_MIDDLE, Ground::WATER_MIDDLE, Ground::WATER_STRAIGHT_RIGHT,Ground::ALIVE, Ground::ALIVE, Ground::ALIVE, Ground::ALIVE,Ground::ALIVE, Ground::ALIVE, Ground::FENCE_STRAIGHT_RIGHT},
                                            {Ground::FENCE_STRAIGHT_LEFT, Ground::WATER_STRAIGHT_BOTTOM, Ground::WATER_STRAIGHT_BOTTOM, Ground::WATER_CORNER_BOTTOM_RIGHT,Ground::ALIVE, Ground::ALIVE, Ground::ALIVE, Ground::ALIVE,Ground::ALIVE, Ground::ALIVE, Ground::FENCE_STRAIGHT_RIGHT},
                                            {Ground::FENCE_STRAIGHT_LEFT, Ground::ALIVE, Ground::ALIVE, Ground::ALIVE,Ground::ALIVE, Ground::ALIVE, Ground::ALIVE, Ground::ALIVE,Ground::ALIVE, Ground::ALIVE, Ground::FENCE_STRAIGHT_RIGHT},
                                            {Ground::FENCE_STRAIGHT_LEFT, Ground::ALIVE, Ground::ALIVE, Ground::ALIVE,Ground::ALIVE, Ground::ALIVE, Ground::WATER_CORNER_TOP_LEFT, Ground::WATER_CORNER_TOP_RIGHT,Ground::ALIVE, Ground::ALIVE, Ground::FENCE_STRAIGHT_RIGHT},
                                            {Ground::FENCE_STRAIGHT_LEFT, Ground::ALIVE, Ground::ALIVE, Ground::ALIVE,Ground::ALIVE, Ground::ALIVE, Ground::WATER_CORNER_BOTTOM_LEFT, Ground::WATER_CORNER_BOTTOM_RIGHT,Ground::ALIVE, Ground::ALIVE, Ground::FENCE_STRAIGHT_RIGHT},
                                            {Ground::FENCE_STRAIGHT_LEFT, Ground::ALIVE, Ground::ALIVE, Ground::ALIVE,Ground::ALIVE, Ground::ALIVE, Ground::ALIVE, Ground::ALIVE,Ground::ALIVE, Ground::ALIVE, Ground::FENCE_STRAIGHT_RIGHT},
                                            {Ground::FENCE_STRAIGHT_LEFT, Ground::ALIVE, Ground::ALIVE, Ground::ALIVE,Ground::ALIVE, Ground::ALIVE, Ground::ALIVE, Ground::ALIVE,Ground::ALIVE, Ground::ALIVE, Ground::FENCE_STRAIGHT_RIGHT},
                                            {Ground::FENCE_STRAIGHT_LEFT, Ground::ALIVE, Ground::ALIVE, Ground::ALIVE,Ground::ALIVE, Ground::WATER_CORNER_TOP_LEFT, Ground::WATER_CORNER_TOP_RIGHT, Ground::ALIVE,Ground::ALIVE, Ground::ALIVE, Ground::FENCE_STRAIGHT_RIGHT},
                                            {Ground::FENCE_STRAIGHT_LEFT, Ground::ALIVE, Ground::ALIVE, Ground::ALIVE,Ground::ALIVE, Ground::WATER_STRAIGHT_LEFT, Ground::WATER_STRAIGHT_RIGHT, Ground::ALIVE,Ground::ALIVE, Ground::ALIVE, Ground::FENCE_STRAIGHT_RIGHT},
                                            {Ground::FENCE_CORNER_BOTTOM_LEFT, Ground::FENCE_STRAIGHT_BOTTOM, Ground::FENCE_STRAIGHT_BOTTOM, Ground::FENCE_STRAIGHT_BOTTOM,Ground::FENCE_STRAIGHT_BOTTOM, Ground::FENCE_STRAIGHT_BOTTOM, Ground::FENCE_STRAIGHT_BOTTOM, Ground::FENCE_STRAIGHT_BOTTOM,Ground::FENCE_STRAIGHT_BOTTOM, Ground::FENCE_STRAIGHT_BOTTOM, Ground::FENCE_CORNER_BOTTOM_LEFT},};

//initialize xNumOfTile*yNumOfTiles sized vectors with NONE
//Note: removed const because those layers are modified later on
vector<vector<Plant>> plantLevel(xNumOfTiles, vector<Plant>(yNumOfTiles, Plant::NONE));
vector<vector<Obstacle>> obstacleLevel(xNumOfTiles, vector<Obstacle>(yNumOfTiles, Obstacle::SMOG));



Tilemap<Ground> groundMap = Tilemap<Ground>(xNumOfTiles, yNumOfTiles, Ground::NONE);
Tilemap<Plant> plantMap = Tilemap<Plant>(xNumOfTiles, yNumOfTiles, Plant::NONE);
Tilemap<Obstacle> obstacleMap = Tilemap<Obstacle>(xNumOfTiles, yNumOfTiles, Obstacle::NONE);


// for (int i=0; i < yNumOfTiles; i++)
// {
//     for (int j=0; j < xNumOfTiles; j++)
//     {
//         groundMap.set()
//     }
// }


                                    

////////////////////////////////////////////////////////////////////
// TEST STATE
////////////////////////////////////////////////////////////////////
std::string title_img = "Assets/Images/Title_Screen.png";


class Test_State : public State
{


public:

    

    bool init() override
    { 
        //initialize map
        plantLevel[9][1] = Plant::GENERATOR;
        rob = Robot();


        for (int i=0; i < yNumOfTiles; i++)
        {
            for (int j=0; j < xNumOfTiles; j++)
            {
                groundMap.set(j, i, groundLevel[i][j]);
                plantMap.set(j, i, plantLevel[i][j]);
                obstacleMap.set(j, i, obstacleLevel[i][j]);
                // MX_LOG("hello");
            }
        }

        plantMap.set(1,9,Plant::GENERATOR);
        //UI Text Initialization
        std::string font = "Assets/Fonts/Laconic.otf";
        std::string energyContent = "20";
        std::string seedContent = "2";
        int size =40;
        energyText = engine()->create_text(font, size, energyContent );
        seedText = engine()->create_text(font, size, seedContent);

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


    void update() override 
    {
        for(int i=1; i<xNumOfTiles-1; i++)
        {
            for(int j=1; j<yNumOfTiles-1; j++)
            {
                if (!isPlantNone(*(plantMap.get(i, j))))
                {
                    for (int x=-1; x < 2; x++)
                    {
                        for (int y=-1; y < 2; y++)
                        {
                            obstacleMap.set(i-x, j-y, Obstacle::NONE);
                        }
                    }
                }
            }
        }
    }
    void render() override
    {

        //iterate through every tile of the State
        for(int i=0; i<yNumOfTiles; i++)
        {
            for(int j=0; j<xNumOfTiles; j++)
            {
                Ground ground = *(groundMap.get(j, i));
                Plant plant =  *(plantMap.get(j, i));
                Obstacle obstacle = *(obstacleMap.get(j, i));
                
                if(ground != Ground::NONE) render_scaled(engine(), groundToString(ground), j*64, i*64 );
                if(plant != Plant::NONE) render_scaled(engine(), plantToString(plant), j*64, i*64 );
                if(obstacle != Obstacle::NONE) render_scaled(engine(), obstacleToString(obstacle), j*64, i*64 );
            }    

        }

        render_scaled(engine(), PLAYER_SPRITE, rob.y * 64, rob.x *64);
        render_scaled(engine(), obstacleToString(Obstacle::FIRE), rob.diry * 64, rob.dirx *64);
        // drawDeadGround(engine(), xNumOfTiles + 6, yNumOfTiles + 6);
        // engine()->render_texture("Assets/Images/Title_Screen.png",0,0);
        // int img_w = 0, img_h = 0, win_w = 0, win_h = 0;
        // engine()->get_texture_size(title_img, &img_w, &img_h);

        // engine()->get_window_size(&win_w, &win_h);
        // if (img_w > 0)
        // {
        //     float scale = float(win_w)/float(img_w);
        //     engine()->render_texture(title_img,0,0, scale, scale);
        // }
        // else MX_LOG(img_w << "x" << img_h);

        //UI Rendering
        render_scaled(engine(), "Assets/Images/energy-icon.png", 10*64, 16);
        render_scaled(engine(), "Assets/Images/energy-icon.png", 8*64, 16);
        engine()->render_text(energyText, 9*64+20, 32);
        engine()->render_text(seedText, 7*64+20, 32);
    }

    void on_keydown(Si32 key) override
    {
        //Switch Statement to check for keys
        //Gives the direction of the robot and calculate coordinate of the next tile
        switch(key)
        {
            case SDLK_ESCAPE: 
                engine()->switch_state("entry_point");
                break;
            case SDLK_UP: 
                rob.move(Robot::UP, groundMap, plantMap, obstacleMap); 
                break;
            case SDLK_DOWN: 
                rob.move(Robot::DOWN, groundMap, plantMap, obstacleMap);
                break;
            case SDLK_LEFT: 
                rob.move(Robot::LEFT, groundMap, plantMap, obstacleMap);
                break;
            case SDLK_RIGHT:
                rob.move(Robot::RIGHT, groundMap, plantMap, obstacleMap);
                break;
            case SDLK_SPACE:
                rob.plantTree(groundMap, plantMap);
                break;
            default: break;
        }
        
        
    }

private:
    Text_ID text;
    Robot rob;
    Text_ID energyText;
    Text_ID seedText;
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
    Test_State game_state;

    Title_State state;
    Text_State text_00("text_01", "The earth is dying.\nThere is but one garden.");
    Text_State text_01("text_02", "You are its caretaker.");
    Text_State text_02("title", "MISTAKes WeRE maDE...");

    engine.push_state("title", &state);
    engine.push_state("entry_point", &text_00);
    engine.push_state("text_01", &text_01);
    engine.push_state("text_02", &text_02);
    engine.push_state("Test_State", &game_state);
    
    // This code is a shit-fire, but it shouldn't break your computer.

    return engine.execute("entry_point");
}
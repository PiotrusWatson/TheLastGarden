#include "engine.hpp"
#include "state.h"
#include "animation.hpp"
#include "tilemap.h"

std::string my_img = "/home/nano/Pictures/Avatars/yuriheart.jpg";



class Test_State : public State
{
public:
    bool init() override
    {
        return true;
    }
    void update() override {}
    void render() override
    {
        engine()->render_texture("Assets/Images/Title_Screen.png",0,0);
    }
    void on_keydown(Si32 key) override
    {

    }
private:
    Text_ID text;
};

int main(int argc, const char * argv[])
{
    Engine engine("The Last Garden", 800, 450, Engine::WINDOWED);
    Test_State state;

    engine.push_state("test", &state);
    return engine.execute("test");
}
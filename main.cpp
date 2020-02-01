#include "engine.hpp"
#include "state.h"

class Test_State : public State
{
public:
    void update() override {}
    void render() override
    {
        engine()->render_texture("/home/nano/Pictures/Avatars/yuriheart.jpg", 10, 10);
    }
    void on_keydown(Si32 key) override
    {
        if (key == SDLK_ESCAPE) engine()->switch_state("test2");
    }
};

int main(int argc, const char * argv[])
{
    Engine engine("The Last Garden", 800, 450, Engine::FULLSCREEN);
    Test_State state;
    Test_State state2;

    engine.push_state("test", &state);
    engine.push_state("test2", &state2);
    return engine.execute("test");
}
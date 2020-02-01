#include "engine.hpp"
#include "state.h"

std::string my_img = "/home/nano/Pictures/Avatars/yuriheart.jpg";

class Test_State : public State
{
public:
    bool init() override
    {
        text = engine()->create_text("Assets/Fonts/Laconic.otf", 64, "Hello, My Text!");
        return true;
    }
    void update() override {}
    void render() override
    {
        engine()->render_texture(my_img, 10, 10);
        engine()->render_text(text, 300, 30);
    }
    void on_keydown(Si32 key) override
    {
        if (key == SDLK_ESCAPE) engine()->switch_state("test2");
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
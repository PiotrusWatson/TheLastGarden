#include "engine.hpp"
#include "state.h"
#include "animation.hpp"
#include "tilemap.h"
#include "debug.h"

std::string title_img = "Assets/Images/Title_Screen.png";


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
        int img_w = 0, img_h = 0, win_w = 0, win_h = 0;
        engine()->get_texture_size(title_img, &img_w, &img_h);

        engine()->get_window_size(&win_w, &win_h);
        if (img_w > 0)
        {
            float scale = float(win_w)/float(img_w);
            engine()->render_texture(title_img,0,0, scale, scale);
        }
        else MX_LOG(img_w << "x" << img_h);
    }
    void on_keydown(Si32 key) override
    {

    }
private:
    Text_ID text;
};

int main(int argc, const char * argv[])
{
    Engine engine("The Last Garden", 800, 450, Engine::FULLSCREEN);
    Test_State state;

    engine.push_state("test", &state);
    return engine.execute("test");
}
#ifndef _engine_hpp
#define _engine_hpp

#include "numerics.h"

#include <string>
#include <unordered_map>

class State;
struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;
struct _TTF_Font;

typedef Ui32 Text_ID;
constexpr Ui32 INVALID_TEXT_ID = UI32_MAX;

class Engine
{
public:
    enum MODE
    {
        FULLSCREEN, WINDOWED
    };

    Engine(const char * title, int w, int h, MODE screen_mode)
    : win_w(w), win_h(h), win_title(title),
    window(nullptr), renderer(nullptr),
    current_state(nullptr), active(false), _screen_mode(screen_mode),
    next_text_id(0)
    {}

    /// execute() starts the engine, loops and cleans up itself
    int execute(const std::string & initial_state);
    void halt();
    
    void push_state(const std::string & id, State * state);
    bool switch_state(const std::string & id);

    void window_size(int * w, int * h);

    Text_ID create_text(const std::string & font, int size, const std::string text, Ui32 wrap);

    void render_texture(const std::string & file);
    void render_texture(const std::string & file, int x, int y, float xscale = 1, float yscale = 1);
    void render_text(Text_ID, int x, int y);
private:
    void loop();
    bool init();
    void cleanup();

    SDL_Texture* fetch_texture(const std::string & file);

    std::unordered_map<std::string, SDL_Texture*> texture_vault;
    std::unordered_map<std::string, State*> state_vault;
    std::unordered_map<Text_ID, SDL_Texture*> text_vault;
    std::unordered_map<std::string, _TTF_Font*> font_vault;

    Text_ID next_text_id;

    const char * win_title;
    int win_w, win_h;
    State * current_state;
    SDL_Window * window;
    SDL_Renderer * renderer;
    bool active;
    MODE _screen_mode;
};

#endif /* _engine_hpp */
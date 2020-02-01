#include "engine.hpp"

#include "debug.h"
#include "state.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#define MX_OKAY 0
#define MX_ERR  1

bool Engine::init()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        MX_LOG("Could not initialise SDL");
        MX_LOG("---> " << SDL_GetError);
        return false;
    }

    Ui32 win_flags = (_screen_mode == MODE::FULLSCREEN)
    ? SDL_WINDOW_FULLSCREEN
    : SDL_WINDOW_SHOWN;

    window = SDL_CreateWindow(win_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, win_w, win_h, win_flags);
    if (window == nullptr)
    {
        MX_LOG("[ ERROR ] Could not create window");
        MX_LOG("---> " << SDL_GetError);
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr)
    {
        MX_LOG("[ ERR ] Could not create renderer");
        MX_LOG(SDL_GetError);
        return false;
    }


    int img_flags = IMG_INIT_PNG | IMG_INIT_JPG;
    if (IMG_Init(img_flags) != img_flags)
    {
        MX_LOG("[ ERR ] could not initialize image support");
        MX_LOG(IMG_GetError);
        return false;
    }

    if (TTF_Init() != 0)
    {
        MX_LOG("[ ERR ] could not initialize TTF support!");
        MX_LOG(TTF_GetError);
        return false;
    }

    active = true;
    return true;
}

void Engine::cleanup()
{
    // -----[ STATE VAULT CLEANUP ]-----
    state_vault.clear();

    // -----[ TEXT VAULT CLEANUP ]-----
    for (auto & it: text_vault)
    {
        if (it.second != nullptr)
        {
            SDL_DestroyTexture(it.second);
            it.second = nullptr;
        }
    }
    text_vault.clear();

    // -----[ FONT VAULT CLEANUP ]-----
    for (auto & it: font_vault)
    {
        if (it.second != nullptr)
        {
            TTF_CloseFont(it.second);
            it.second = nullptr;
        }
    }
    font_vault.clear();

    // -----[ TEXTURE VAULT CLEANUP ]-----
    for (auto & it: texture_vault)
    {
        if (it.second != nullptr)
        {
            SDL_DestroyTexture(it.second);
            it.second = nullptr;
        }
    }
    texture_vault.clear();

    TTF_Quit();
    IMG_Quit();

    if (renderer != nullptr)
    {
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
    }
    if (window != nullptr)
    { 
        SDL_DestroyWindow(window);
        window = nullptr;
    }
    SDL_Quit();
}

void Engine::halt()
{
    active = false;
}

void Engine::push_state(const std::string & id, State * state)
{
    if (state == nullptr)
    {
        MX_LOG("Could not add state as it was a nullptr!");
        return;
    }
    auto search = state_vault.find(id);
    if (search != state_vault.end())
    {
        MX_LOG("Could not add state as one with this ID already exists!!!");
        return; // State already exists!
    }

    state_vault[id] = state;
    state->set_engine(this);
}

int Engine::execute(const std::string & initial_state)
{
    if (active)
    {
        MX_LOG("Attempt to call execute whilst engine was already running!");
        return false;
    }

    if (!init())
    {
        cleanup();
        return MX_ERR;
    }

    for (auto & it: state_vault)
    {
        if (it.second != nullptr)
        {
            if (it.second->init() == false) halt();
        }
    }

    if (!switch_state(initial_state))
    {
        cleanup();
        return MX_ERR;
    }

    while (active) loop();

    cleanup();
    return MX_OKAY;
}

void Engine::loop()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        // -----[ EVENTS ]-----
        switch (event.type)
        {
        case SDL_QUIT:
            halt();
            break;
        case SDL_KEYDOWN:
            if (event.key.repeat == 0) 
                current_state->on_keydown(event.key.keysym.sym);
            break;
        case SDL_KEYUP:
            current_state->on_keyup(event.key.keysym.sym);
            break;
        default:
            break;
        }
    }
    // -----[ LOGIC ]-----

    current_state->update();

    // -----[ RENDER ]-----
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    current_state->render();

    SDL_RenderPresent(renderer);
}

bool Engine::switch_state(const std::string & id)
{
    auto search = state_vault.find(id);
    if (search == state_vault.end())
    {
        MX_LOG("[ ERR ] Could not switch state");
        MX_LOG("state '" << id << "' could not be found");
        return false;
    }
    if (search->second == nullptr)
    {
        MX_LOG("[ ERR ] Could not switch state");
        MX_LOG("state '" << id << "' was a nullptr");
        return false;
    }

    // Success!
    if (current_state != nullptr) current_state->on_leave();
    current_state = search->second;
    current_state->on_enter();

    return true;
}

void Engine::window_size(int * w, int * h)
{
    SDL_GetRendererOutputSize(renderer, w, h);
}

Text_ID Engine::create_text(const std::string & font_name, int size, const std::string text, Ui32 wrap)
{
    Text_ID output = next_text_id;
    std::string font_key = font_name + std::to_string(size);

    auto search = font_vault.find(font_key);
    if (search == font_vault.end())
    {
        // Attempt to load it!
        TTF_Font * font = nullptr;
        font = TTF_OpenFont(font_name.c_str(), size);
        if (font == nullptr)
        {
            MX_LOG("could not load font:");
            MX_LOG("File: " << font_name);
            MX_LOG("Size: " << size);
            return INVALID_TEXT_ID;
        }
        font_vault[font_key] = font;
        search = font_vault.find(font_key);
        if (search == font_vault.end())
        {
            MX_LOG("Strange Error occured whilst accessing font vault!");
            return INVALID_TEXT_ID;
        }
    }
    if (search->second == nullptr)
    {
        MX_LOG("nullptr existed in font_vault, for some reason");
        return INVALID_TEXT_ID;
    }
    SDL_Surface * surf = nullptr;
    if (wrap > 0)
    { surf = TTF_RenderUTF8_Blended_Wrapped(search->second,text.c_str(),{255,255,255,255}, wrap); }
    else surf = TTF_RenderUTF8_Blended(search->second,text.c_str(),{255,255,255,255});
    if (surf == nullptr)
    {
        MX_LOG("Could not create text for rendering!");
        return INVALID_TEXT_ID;
    }
    SDL_Texture * tx = SDL_CreateTextureFromSurface(renderer,surf);
    SDL_FreeSurface(surf);
    if (tx == nullptr)
    {
        MX_LOG("Could not create text texture from surface!");
        return INVALID_TEXT_ID;
    }
    
    text_vault[output] = tx;
    ++next_text_id;

    return output;
}

void Engine::render_texture(const std::string & file)
{
    SDL_Texture * tx = fetch_texture(file);
    if (tx == nullptr) return;
    SDL_RenderCopy(renderer, tx, nullptr, nullptr);
}

void Engine::render_texture(const std::string & file, int x, int y, float xScale, float yScale)
{
    SDL_Texture * tx = fetch_texture(file);
    if (tx == nullptr) return;
    SDL_Rect dst = { x, y, 0, 0};
    SDL_QueryTexture(tx, nullptr, nullptr, &dst.w, &dst.h);
    dst.w *= xScale;
    dst.h *= yScale;
    SDL_RenderCopy(renderer, tx, nullptr, &dst);
}

void Engine::render_text(Text_ID id, int x, int y)
{
    if (id == INVALID_TEXT_ID) return;
    auto search = text_vault.find(id);
    if (search == text_vault.end()) return; // could not find text;
    if (search->second == nullptr) return; // should not have null textures, but all the same
    SDL_Rect dst = {x,y,0,0};
    SDL_QueryTexture(search->second, nullptr, nullptr, &dst.w, &dst.h);
    SDL_RenderCopy(renderer, search->second, nullptr, &dst);


    // TODO: Fill this function in!
}

SDL_Texture* Engine::fetch_texture(const std::string & file)
{
    auto search = texture_vault.find(file);
    if (search != texture_vault.end()) // found image in vault
    { return search->second; }

    // Ok, so attempt to load it.
    // Yes, this section of the code is awful, have pity on me plz
    SDL_Texture * texture = nullptr;
    texture = IMG_LoadTexture(renderer, file.c_str());
    if (texture != nullptr) texture_vault[file] = texture;
    else MX_LOG("Could not load image: " << file);
    return texture;
}
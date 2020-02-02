#ifndef _text_state_h
#define _text_state_h

#include <string>
#include "state.h"
#include "engine.hpp"
#include "debug.h"

class Text_State : public State
{
public:
    Text_State(const std::string & next_state, const std::string & text)
    : text_string(text), goto_state(next_state), status(STATUS::BEGIN),
    text_id(INVALID_TEXT_ID), alpha(0.0f), speed(0.01f), border(20),
    font("Assets/Fonts/Laconic.otf") {}
    bool init() override
    {
        int win_w = 0, win_h = 0;
        engine()->get_window_size(&win_w, &win_h);
        text_id = engine()->create_text(font, 40, text_string, win_w-(border*2));
        if (text_id == INVALID_TEXT_ID)
        {
            MX_LOG("Could not create text for text_state:");
            MX_LOG("--> " << text_string);
            return false;
        }
        return true;
    }
    void update() override
    {
        switch (status)
        {
        case STATUS::BEGIN:
            alpha += speed;
            if (alpha >= 1)
            {
                alpha = 1;
                status = STATUS::HOLD;
            }
            break;
        case STATUS::END:
            alpha -= speed;
            if (alpha <= 0)
            {
                alpha = 0;
                status = STATUS::BEGIN;
                engine()->switch_state(goto_state);
            }
            break;
        default:
            break;
        }
        
    }
    void render() override
    {
        int text_w = 0, text_h = 0, win_w=0, win_h = 0;
        engine()->get_text_size(text_id, &text_w, &text_h);
        engine()->get_window_size(&win_w, &win_h);
        int xpos = win_w/2 - text_w/2;
        int ypos = win_h/2 - text_h/2;;
        engine()->render_text(text_id, xpos , ypos);
        if (status == STATUS::BEGIN || status == STATUS::END)
        {
            engine()->render_fill(0,0,0, (1.0f - alpha) * 255);
        }
    }

    void on_keydown(Si32 key) override
    {
        if (status == STATUS::HOLD) status = STATUS::END;
    }

    void on_enter() override
    {
        alpha = 0.0f;
        status = STATUS::BEGIN;
    }

    void on_leave() override
    { }

private:
    enum STATUS
    {
        BEGIN, HOLD, END
    };
    std::string font;
    STATUS status;
    std::string text_string;
    std::string goto_state;
    int border;
    float alpha;
    float speed;
    Text_ID text_id;
};

#endif /* _text_state_h */
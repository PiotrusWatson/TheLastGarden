#ifndef _run_dat_game_h
#define _run_dat_game_h

#include "engine.hpp"
#include "title_state.h"
#include "text_state.h"


int run_game()
{
    Engine engine("The Last Garden", 800, 450, Engine::WINDOWED);
    Title_State state;
    Text_State text_00("text_01", "The earth is dying.\nThere is but one garden.");
    Text_State text_01("text_02", "You are its caretaker.");
    Text_State text_02("title", "MISTAKes WeRE maDE...");

    engine.push_state("title", &state);
    engine.push_state("text_00", &text_00);
    engine.push_state("text_01", &text_01);
    engine.push_state("text_02", &text_02);
    return engine.execute("text_00");
}

#endif /* run_dat_game_h */
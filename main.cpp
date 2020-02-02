#include "engine.hpp"
#include "title_state.h"


int main(int argc, const char * argv[])
{
    Engine engine("The Last Garden", 800, 450, Engine::WINDOWED);
    Title_State state;

    engine.push_state("title", &state);
    return engine.execute("title");
}
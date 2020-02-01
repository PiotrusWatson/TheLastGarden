#ifndef _state_h
#define _state_h

#include "numerics.h"
#include <SDL2/SDL_keycode.h>

class Engine;

class State
{
public:
    State() : _engine(nullptr) {}
    virtual ~State() {}

    virtual void on_enter() {}
    virtual void on_leave() {}

    virtual void update() = 0;
    virtual void render() = 0;

    virtual void on_keydown(Si32 key) {}
    virtual void on_keyup(Si32 key) {}
    
    /// Use this function to access the engine code
    Engine* engine() { return _engine; }

    /// DO NOT CALL THIS FUNCTION!!
    void set_engine(Engine * e) { _engine = e; }

private:
    Engine* _engine;
};

#endif /*_state_h */
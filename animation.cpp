#include "animation.hpp"
#include "debug.h"

void Animation_Engine::update()
{
    for (auto & it: animations)
    { ++it.second.acc; }
}

void Animation_Engine::create(const std::string & id, Ui frame_len)
{
    if (frame_len < 1)
    {
        MX_LOG("Unable to create animation with an update time of less than 1!");
        return;
    }
    if (id == "")
    {
        MX_LOG("Blank \"\" animation name is reserved for invalid animation identifier");
        return;
    }
    auto search = animations.find(id);
    if (search != animations.end())
    {
        MX_LOG("Attempt to create duplicate animation: " << id);
        return;
    }
    Sequence seq(frame_len);

    animations[id] = seq;   
}

std::string Animation_Engine::current_frame(const std::string & id)
{
    auto search = animations.find(id);
    if (search == animations.end())
    {
        MX_LOG("Unable to find animation: " << id);
        return "";
    }
    Sequence * seq = &(search->second);
    if (seq->frames.empty()) return "";
    else if (seq->frames.size() == 1) return seq->frames.back();
    
    Ui frame_num = (seq->acc / seq->interval) %  seq->frames.size();
    return seq->frames[frame_num];
}
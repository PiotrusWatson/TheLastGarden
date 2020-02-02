#ifndef _animation_hpp
#define _animation_hpp

#include "numerics.h"
#include <unordered_map>
#include <vector>

class Animation_Engine
{
public:
    void create(const std::string & id, Ui frame_len);
    void append(const std::string & id, const std::string & image);
    std::string current_frame(const std::string & id);
    void update();
private:
    struct Sequence
    {
        Sequence(Ui frame_len) : interval(frame_len), acc(0) {}
        Sequence(const Sequence & other)
        : frames(other.frames), interval(other.interval), acc(other.acc)
        {}
        Sequence & operator=(const Sequence& other)
        {
            frames = other.frames;
            interval = other.interval;
            acc = other.interval;
            return *this;
        }

        std::vector<std::string> frames;
        Ui interval;
        Ui acc;
    };
    std::unordered_map<std::string, Sequence> animations;
};

#endif /* _animation_hpp */
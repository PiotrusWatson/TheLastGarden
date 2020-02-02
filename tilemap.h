#ifndef _tilemap_h
#define _tilemap_h

#include "numerics.h"

template <class T>
struct Tilemap
{
public:
    Tilemap(Ui width, Ui height) : w(width), h(height) { _data.reserve(w*h); }

    Tilemap(Ui width, Ui height, const T & fill_type) : w(width), h(height)
    {
        _data.reserve(w*h);
        fill(fill_type);
    }

    void fill(const T & t)
    {
        for (auto & it: _data) it = t;
    }

    T* get(Ui x, Ui y)
    {
        if ((x >= w) || (y >= h)) return nullptr;
        else return &(_data[y*w +x]);
    }

    void set(Ui x, Ui y, const T & t)
    {
        if ((x >= w) || (y >= h)) return;
        else _data[y*w + x] = t;
    }

    Ui width(){ return w; }
    Ui height(){ return h; }

    const T& data(){ return *_data.data(); }
private:
    std::vector<T> _data;
    Ui w;
    Ui h;
};

#endif /* _tilemap_h */
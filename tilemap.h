#ifndef _tilemap_h
#define _tilemap_h

#include <vector>
#include "pos2d.h"

template <class T>
class Tilemap
{
public:
    Tilemap(Ui w, Ui h, const std::vector<T> & data) : width(w), height(h), storage(data) {}

    T* get_tile(Ui x, Ui y)
    {
        if (x >= width || y >= height) return nullptr;
        Ui pos = get_index(x, y);
    }

    bool locate(T* t, Ui * xOut, Ui * yOut)
    {
        if (xOut == nullptr || yOut == nullptr) return false;
        for (int y = 0; y < height; ++y) 
        {
            for (int x = 0; x < width; ++x)
            {
                if (t == &storage[get_index(x,y)])
                {
                    *xOut = x;
                    *yOut = y;
                    return true;
                }
            }
        }
    }
private:
    Ui get_index(Ui x, Ui y)
    {
        return y*width + x;
    }
    std::vector<T> storage;
    const int width, height;
};

#endif /* _tilemap_h */
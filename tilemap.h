#ifndef _tilemap_h
#define _tilemap_h

template <class T, Ui w, Ui h>
struct Tilemap
{
    T* tile(Ui x, Ui y)
    {
        if ((x >= w) || (y >= h)) return nullptr;
        else return data[y*w+x];
    }
    T data[w*h];
    const Ui WIDTH = w;
    const Ui HEIGHT = h;
};

#endif /* _tilemap_h */
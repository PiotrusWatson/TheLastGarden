#ifndef _tilemap_h
#define _tilemap_h

template <class T>
struct Tilemap
{
public:
    Tilemap(Ui width, Ui height) : w(width), h(height) { _data.reserve(w*h); }

    Tilemap(Ui width, Ui height, const T & t) : Tilemap(w,h){ fill(t); }

    void fill(const T & t)
    {
        for (auto & it: data) it = t;
    }

    T* get(Ui x, Ui y)
    {
        if ((x >= WIDTH) || (y >= HEIGHT)) return nullptr;
        else return _data[y*WIDTH +x];
    }

    void set(Ui x, Ui y, const T & t)
    {
        if ((x >= WIDTH) || (y >= HEIGHT)) return nullptr;
        else _data[y*WIDTH + x] = t;
    }

    Ui width(){ return w; }
    Ui height(){ return h; }
private:
    std::vector<T> _data;
    Ui w;
    Ui h;
};

#endif /* _tilemap_h */
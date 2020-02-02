#include <string>
#include <vector>

using namespace std;

class Robot{
    
    private:
        int _x, _y;


    public:

        int energy;

        Robot() : _x(9), _y(3), energy(20) {}
        Robot(int xpos, int ypos) : _x(xpos), _y(ypos) {}
        
        

        void setPos(int xpos, int ypos)
        {
            _x = xpos;
            _y = ypos;
        };
        
        int x(){ return _x; };
        int y(){ return _y; };

        
    
    

};
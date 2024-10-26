#include <iostream>
using namespace std;

enum eDir { STOP = 0, LEFT = 1, UPLEFT = 2, DOWNLEFT = 3, RIGHT = 4, UPRIGHT = 5, DOWNRIGHT = 6 };

class cBall {
private:
    int x, y;
    int originalX, originalY;
    eDir direction;

public:
    cBall(int posX, int posY) {
        originalX = posX;
        originalY = posY;
        x = posX;
        y = posY;
        direction = STOP;
    }

    void Reset() {
        x = originalX;
        y = originalY;
        direction = STOP;
    }

    void changeDirection(eDir d) {
        direction = d;
    }

    void randomDirection() {
        direction = (eDir)((rand() % 6) + 1);
    }

    inline int getX() { return x; }
    inline int getY() { return y; }
    inline eDir getDirection() { return direction; }

    void Move() {
        switch (direction) {
            case STOP:
                break;
            case LEFT:
                x--;
                break;
            case RIGHT:
                x++;
                break;
            case UPLEFT:
                x--; y--;
                break;
            case DOWNLEFT:
                x--; y++;
                break;
            case UPRIGHT:
                x++; y--;
                break;
            case DOWNRIGHT:
                x++; y++;
                break;
            default:
                break;
        }
    }

    friend ostream& operator<<(ostream& o, const cBall& c) {
        o << "[" << c.x << "," << c.y << "][" << c.direction << "]" << endl;
        return o;
    }
};
 class cPaddle
 {
    private:
    int x,y;
    int originalX , originalY;
    public:
    cPaddle()
    {
        x = y = 0;
    }
    
      cPaddle(int posX, int posY):cPaddle()
      {
          originalX =posX;
          originalY =posY;
          x =posX;
          y = posY;
      }
     inline void Reset() {x =originalX;y = originalY;}
     inline int getX() {return x;}
     inline int getY() {return y;}
     inline void MoveUp(){y--;}
     inline void MoveDown() {y++;}
     friend ostream & operator << (ostream & o, cPaddle c)
     {
        
     }
 };
int main() {
    cBall c(0, 0);
    cout << c << endl;
    c.randomDirection();

    cout << c << endl;
    c.Move();
    cout << c << endl;
    c.randomDirection();
    c.Move();
    cout << c << endl;

    return 0;
}

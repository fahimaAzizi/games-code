#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
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

class cPaddle {
private:
    int x, y;
    int originalX, originalY;
public:
    cPaddle() : x(0), y(0) {}

    cPaddle(int posX, int posY) {
        originalX = posX;
        originalY = posY;
        x = posX;
        y = posY;
    }

    inline void Reset() { x = originalX; y = originalY; }
    inline int getX() { return x; }
    inline int getY() { return y; }
    inline void MoveUp() { y--; }
    inline void MoveDown() { y++; }

    friend ostream& operator<<(ostream& o, const cPaddle& c) {
        o << "paddle [" << c.x << "," << c.y << "]";
        return o;
    }
};

class cGameManger {
private:
    int width, height;
    int score1, score2;
    char up1, down1, up2, down2;
    bool quit;
    cBall* ball;
    cPaddle* player1;
    cPaddle* player2;
    string ballColor;  // Store current color of the ball
    const string colors[6] = {"\033[31m", "\033[32m", "\033[33m", "\033[34m", "\033[35m", "\033[36m"}; // Red, Green, Yellow, Blue, Magenta, Cyan

public:
    cGameManger(int w, int h) {
        srand(time(NULL));
        quit = false;
        up1 = 'w'; up2 = 'i';
        down1 = 's'; down2 = 'k';
        score1 = score2 = 0;
        width = w; height = h;
        ball = new cBall(w / 2, h / 2);
        player1 = new cPaddle(1, h / 2 - 3);
        player2 = new cPaddle(w - 2, h / 2 - 3);
        ballColor = colors[0]; // Initialize with the first color
    }


    void scoreUp(cPaddle* player) {
        if (player == player1)
            score1++;
        else if (player == player2)
            score2++;

        ball->Reset();
        player1->Reset();
        player2->Reset();
    }

    void Draw() {
    system("clear");
    cout << "\033[42m"; // Set green background for the entire screen

    for (int i = 0; i < width + 2; i++)
        cout << "\xB2";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width + 2; j++) {
            int ballx = ball->getX();
            int bally = ball->getY();
            int player1x = player1->getX();
            int player2x = player2->getX();
            int player1y = player1->getY();
            int player2y = player2->getY();

            if (j == 0 || j == width + 1) {
                cout << "\xB2";
            } else if (ballx == j && bally == i) {
                cout << ballColor << "o\033[42m"; // Use the current ball color
            } else if (player1x == j && (player1y <= i && i < player1y + 4)) {
                cout << "\033[31m\xDB\033[42m"; // Red color for player1 paddle
            } else if (player2x == j && (player2y <= i && i < player2y + 4)) {
                cout << "\033[30m\xDB\033[42m"; // Black color for player2 paddle
            } else {
                cout << " ";
            }
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
        cout << "\xB2";
    cout << "\033[0m" << endl; // Reset colors to default
    cout << "Score 1: " << score1 << "   Score 2: " << score2 << endl;
}


    void Input() {
        if (_kbhit()) {
            char current = _getch();
            if (current == up1 && player1->getY() > 0)
                player1->MoveUp();
            if (current == down1 && player1->getY() + 4 < height)
                player1->MoveDown();
            if (current == up2 && player2->getY() > 0)
                player2->MoveUp();
            if (current == down2 && player2->getY() + 4 < height)
                player2->MoveDown();

            if (ball->getDirection() == STOP)
                ball->randomDirection();

            if (current == 'q')
                quit = true;
        }
    }

    void Logic() {
    int ballx = ball->getX();
    int bally = ball->getY();
    int player1x = player1->getX();
    int player2x = player2->getX();
    int player1y = player1->getY();
    int player2y = player2->getY();

    // Ball collision with paddles
    for (int i = 0; i < 4; i++) {
        if (ballx == player1x + 1 && bally == player1y + i) {
            ball->changeDirection((eDir)((rand() % 3) + 4));
            ballColor = colors[rand() % 6]; // Change to a random color
        }
        if (ballx == player2x - 1 && bally == player2y + i) {
            ball->changeDirection((eDir)((rand() % 3) + 1));
            ballColor = colors[rand() % 6]; // Change to a random color
        }
    }

    // Ball collision with top and bottom walls
    if (bally == 0 || bally == height - 1) {
        ball->changeDirection(ball->getDirection() == DOWNRIGHT ? UPRIGHT : UPLEFT);
        ballColor = colors[rand() % 6]; // Change to a random color
    }

    // Ball passes paddles (score)
    if (ballx == width - 1) scoreUp(player1);
    if (ballx == 0) scoreUp(player2);

    ball->Move();
}

     

    void Run() {
        while (!quit) {
            Draw();
            Input();
            Logic();
        }
    }
};

int main() {
    cGameManger c(40, 20);
    c.Run();
    return 0;
}

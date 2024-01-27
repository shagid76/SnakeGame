#include <iostream>
#include <conio.h>
#include <windows.h>
bool GameOver;
const int width = 118;
const int height = 26;
int x, y, fruitx, fruity, score;
int tailx[100], taily[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag;
    SetConsoleCursorInfo(out, &cursorInfo);
}
void Setup() {
    GameOver = false;
    dir = STOP;
    x = width / 2;
    y = height / 2;
    fruitx = rand() % width;
    fruity = rand() % height;
    score = 0;
}
void Draw() {
    system("cls");
    for (int i = 0; i < width + 1; i++)
    {
        std::cout << "#";
    }
    std::cout << std::endl;

    for (int j = 0; j < height; j++)
    {
        for (int i = 0; i < width; i++)
        {
            if (i == 0 || i == width - 1) {
                std::cout << "#";
            }
            if (j == y && i == x) {
                std::cout << "0";
            }
            else if (i == fruitx && j == fruity) {
                std::cout << "f";
            }
            else {
                bool print = false;
                
                for (int k = 0; k < nTail; k++)
                {
                    if (tailx[k] == i && taily[k] == j) {
                        print = true;
                        std::cout << "o";
                    }
                }
                if (!print) {

                    std::cout << " ";
                }
            }
        }
        std::cout << std::endl;
    }
    for (int i = 0; i < width + 1; i++)
    {
        std::cout << "#";
    }
    std::cout << std::endl;
    std::cout << "Score: " << score << std::endl;
}


void Input() {
    if (_kbhit()) {
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'A':
            dir = LEFT;
            break;
        case 'D':
            dir = RIGHT;
            break;
        case 'W':
            dir = UP;
            break;
        case 'S':
            dir = DOWN;
            break;
        case'x':
            GameOver = true;
            break;
        }
    }
}
void Logic() {
    int prevX = tailx[0];
    int prevY = taily[0];
    int prev2X, prev2Y;
    tailx[0] = x;
    taily[0] = y;

    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailx[i];
        prev2Y = taily[i];
        tailx[i] = prevX;
        taily[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    }
    
    if (x >= width - 1) {
        x = 0;
    }
    else if (x < 0) {
        x = width - 2;
    }
    if (y >= height) {
        y = 0;
    }
    else if (y < 0) {
        y = height - 1;
    }
    for (int i = 0; i < nTail; i++) {
        if (tailx[i] == x && taily[i] == y) {
            GameOver = true;
        }
    }


    if (x == fruitx && y == fruity) {
        score += 10;
        fruitx = rand() % width;
        fruity = rand() % height;
        nTail++;
    }
}
int main()
{
    Setup();
    ShowConsoleCursor(false);
    system("pause");

    while (!GameOver) {
        Draw();
        Input();
        Logic();
        Sleep(1);
    }

    return 0;
}


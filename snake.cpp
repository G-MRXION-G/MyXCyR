#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>

using namespace std;

// 游戏参数
const int WIDTH = 80;
const int HEIGHT = 20;
int x, y;           // 蛇头位置
int fruitX, fruitY; // 水果位置
int score;          // 分数
int tailX[100], tailY[100]; // 蛇尾位置
int nTail;          // 蛇尾长度

// 方向枚举
enum Direction {
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};
Direction dir;

// 初始化游戏
void Setup() {
    dir = STOP;
    x = WIDTH / 2;
    y = HEIGHT / 2;
    fruitX = rand() % WIDTH;
    fruitY = rand() % HEIGHT;
    score = 0;
    nTail = 0;
    srand(time(NULL));
}

// 绘制游戏界面
void Draw() {
    system("cls"); // 清屏
    
    // 打印顶部边框
    for (int i = 0; i < WIDTH + 2; i++)
        cout << "#";
    cout << endl;
    
    // 打印游戏区域
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (j == 0) // 左边界
                cout << "#";
            
            if (i == y && j == x) // 蛇头
                cout << "O";
            else if (i == fruitY && j == fruitX) // 水果
                cout << "F";
            else { // 蛇尾和空白区域
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }
            
            if (j == WIDTH - 1) // 右边界
                cout << "#";
        }
        cout << endl;
    }
    
    // 打印底部边框
    for (int i = 0; i < WIDTH + 2; i++)
        cout << "#";
    cout << endl;
    
    // 打印分数
    cout << "分数: " << score << endl;
    cout << "按WASD移动，按X退出" << endl;
}

// 处理输入
void Input() {
    if (_kbhit()) { // 检测键盘输入
        switch (_getch()) {
        case 'a':
            if (dir != RIGHT) // 防止直接反向移动
                dir = LEFT;
            break;
        case 'd':
            if (dir != LEFT)
                dir = RIGHT;
            break;
        case 'w':
            if (dir != DOWN)
                dir = UP;
            break;
        case 's':
            if (dir != UP)
                dir = DOWN;
            break;
        case 'x':
            dir = STOP;
            break;
        }
    }
}

// 游戏逻辑
void Logic() {
    // 更新蛇尾位置
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    
    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    
    // 更新蛇头位置
    switch (dir) {
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
    case STOP:
        return;
    }
    
    // 边界检测（穿墙）
    if (x >= WIDTH)
        x = 0;
    else if (x < 0)
        x = WIDTH - 1;
    
    if (y >= HEIGHT)
        y = 0;
    else if (y < 0)
        y = HEIGHT - 1;
    
    // 检测撞到自己
    for (int i = 0; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y) {
            dir = STOP;
            cout << "游戏结束！最终分数: " << score << endl;
            system("pause");
        }
    }
    
    // 检测吃到水果
    if (x == fruitX && y == fruitY) {
        score += 10;
        fruitX = rand() % WIDTH;
        fruitY = rand() % HEIGHT;
        nTail++;
    }
}

int main() {
    Setup();
    while (dir != STOP) {
        Draw();
        Input();
        Logic();
        Sleep(100); // 控制游戏速度
    }
    return 0;
}

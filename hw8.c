#include <stdio.h>

#define MAX_N 10  //迷宮大小

int ExitX = 8;
int ExitY = 10;

int MAZE[MAX_N][MAX_N] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},  // 0 表示路徑，1 表示牆壁
    {1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
    {1, 1, 1, 0, 1, 0, 0, 1, 1, 1},
    {1, 1, 1, 0, 1, 0, 1, 1, 0, 1},
    {1, 1, 0, 0, 0, 0, 1, 1, 1, 1},
    {1, 1, 0, 1, 1, 1, 1, 0, 0, 0},
    {1, 1, 0, 1, 1, 1, 1, 0, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

typedef struct {   //座標結構
    int x, y;
} XyNode;

typedef struct {                  //堆疊結構
    XyNode stack[MAX_N * MAX_N];
    int top;
} TraceRoad;

void push(TraceRoad *t, int x, int y) {
    t->stack[++t->top] = (XyNode){x, y};
}

XyNode pop(TraceRoad *t) {
    return t->stack[t->top--];  // pop
}

int getExit(int x, int y) {
    return x == ExitX && y == ExitY;  // 檢查是否到達出口
}

void printMaze() {
    for (int i = 0; i < MAX_N; i++) {
        for (int j = 0; j < MAX_N; j++) {
            printf("%d ", MAZE[i][j]);  // 輸出迷宮地圖
        }
        printf("\n");
    }
}

int main() {
    int nowX = 1, nowY = 1;
    TraceRoad t = {{0}};

    printMaze();

    while (nowX <= ExitX && nowY <= ExitY) {
        MAZE[nowX][nowY] = 2;  // 標記走過的路徑

        if (MAZE[nowX - 1][nowY] == 0 || MAZE[nowX][nowY + 1] == 0 || MAZE[nowX + 1][nowY] == 0 || MAZE[nowX][nowY - 1] == 0) {
            push(&t, nowX, nowY);  // 有路可走，將目前座標push堆疊
            if (getExit(nowX, nowY)) {
                printf("Reach Exit\n");  // 到達出口
                break;
            }

            if (MAZE[nowX - 1][nowY] == 0) nowX -= 1;  // 上方有路，向上移動
            else if (MAZE[nowX][nowY + 1] == 0) nowY += 1;  // 右方有路，向右移動
            else if (MAZE[nowX + 1][nowY] == 0) nowX += 1;  // 下方有路，向下移動
            else if (MAZE[nowX][nowY - 1] == 0) nowY -= 1;  // 左方有路，向左移動
        } else if (t.top >= 0) {
            XyNode last = pop(&t);  // 無路可走，從堆疊中pop上一個座標
            nowX = last.x;
            nowY = last.y;
        }
    }

    printMaze();

    return 0;
}

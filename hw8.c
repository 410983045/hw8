#include <stdio.h>

#define MAX_N 10  //�g�c�j�p

int ExitX = 8;
int ExitY = 10;

int MAZE[MAX_N][MAX_N] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},  // 0 ��ܸ��|�A1 ������
    {1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
    {1, 1, 1, 0, 1, 0, 0, 1, 1, 1},
    {1, 1, 1, 0, 1, 0, 1, 1, 0, 1},
    {1, 1, 0, 0, 0, 0, 1, 1, 1, 1},
    {1, 1, 0, 1, 1, 1, 1, 0, 0, 0},
    {1, 1, 0, 1, 1, 1, 1, 0, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

typedef struct {   //�y�е��c
    int x, y;
} XyNode;

typedef struct {                  //���|���c
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
    return x == ExitX && y == ExitY;  // �ˬd�O�_��F�X�f
}

void printMaze() {
    for (int i = 0; i < MAX_N; i++) {
        for (int j = 0; j < MAX_N; j++) {
            printf("%d ", MAZE[i][j]);  // ��X�g�c�a��
        }
        printf("\n");
    }
}

int main() {
    int nowX = 1, nowY = 1;
    TraceRoad t = {{0}};

    printMaze();

    while (nowX <= ExitX && nowY <= ExitY) {
        MAZE[nowX][nowY] = 2;  // �аO���L�����|

        if (MAZE[nowX - 1][nowY] == 0 || MAZE[nowX][nowY + 1] == 0 || MAZE[nowX + 1][nowY] == 0 || MAZE[nowX][nowY - 1] == 0) {
            push(&t, nowX, nowY);  // �����i���A�N�ثe�y��push���|
            if (getExit(nowX, nowY)) {
                printf("Reach Exit\n");  // ��F�X�f
                break;
            }

            if (MAZE[nowX - 1][nowY] == 0) nowX -= 1;  // �W�観���A�V�W����
            else if (MAZE[nowX][nowY + 1] == 0) nowY += 1;  // �k�観���A�V�k����
            else if (MAZE[nowX + 1][nowY] == 0) nowX += 1;  // �U�観���A�V�U����
            else if (MAZE[nowX][nowY - 1] == 0) nowY -= 1;  // ���観���A�V������
        } else if (t.top >= 0) {
            XyNode last = pop(&t);  // �L���i���A�q���|��pop�W�@�Ӯy��
            nowX = last.x;
            nowY = last.y;
        }
    }

    printMaze();

    return 0;
}

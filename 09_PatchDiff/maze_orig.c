#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 6
#define MAZE_SIZE (2 * N + 1)

enum { UP, RIGHT, DOWN, LEFT };
const int DX[4] = { 0, 1, 0, -1 };
const int DY[4] = { -1, 0, 1, 0 };

typedef struct {
    int visited;
    int walls[4];
} Cell;

Cell maze[N][N];

void initMaze();
void generateMaze(int x, int y);
void renderMaze(char output[MAZE_SIZE][MAZE_SIZE]);
void printMaze(char output[MAZE_SIZE][MAZE_SIZE]);

int main() {
    srand(time(NULL));

    initMaze();
    generateMaze(0, 0);

    char output[MAZE_SIZE][MAZE_SIZE];
    renderMaze(output);
    printMaze(output);

    return 0;
}

void initMaze() {
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            maze[y][x].visited = 0;
            maze[y][x].walls[UP] = 1;
            maze[y][x].walls[RIGHT] = 1;
            maze[y][x].walls[DOWN] = 1;
            maze[y][x].walls[LEFT] = 1;
        }
    }
}

void shuffle(int *array, int n) {
    for (int i = 0; i < n - 1; i++) {
        int j = i + rand() / (RAND_MAX / (n - i) + 1);
        int t = array[j];
        array[j] = array[i];
        array[i] = t;
    }
}

void generateMaze(int x, int y) {
    maze[y][x].visited = 1;

    int directions[4] = { UP, RIGHT, DOWN, LEFT };
    shuffle(directions, 4);

    for (int i = 0; i < 4; i++) {
        int dir = directions[i];
        int nx = x + DX[dir];
        int ny = y + DY[dir];

        if (nx >= 0 && nx < N && ny >= 0 && ny < N && !maze[ny][nx].visited) {
            maze[y][x].walls[dir] = 0;
            maze[ny][nx].walls[(dir + 2) % 4] = 0;
            generateMaze(nx, ny);
        }
    }
}

void renderMaze(char output[MAZE_SIZE][MAZE_SIZE]) {
    for (int x = 0; x < MAZE_SIZE; x++) {
        for (int y = 0; y < MAZE_SIZE; y++) {
            output[x][y] = '#';
        }
    }

    for (int x = 0; x < N; x++) {
        for (int y = 0; y < N; y++) {
            int mazeX = x * 2 + 1;
            int mazeY = y * 2 + 1;
            output[mazeX][mazeY] = '.';

            if (maze[x][y].walls[RIGHT] == 0 && mazeY + 1 < MAZE_SIZE - 1) {
                output[mazeX][mazeY + 1] = '.';
            }

            if (maze[x][y].walls[DOWN] == 0 && mazeX + 1 < MAZE_SIZE - 1) {
                output[mazeX + 1][mazeY] = '.';
            }
        }
    }
}

void printMaze(char output[MAZE_SIZE][MAZE_SIZE]) {
    for (int x = 0; x < MAZE_SIZE; x++) {
        for (int y = 0; y < MAZE_SIZE; y++) {
            putchar(output[x][y]);
        }
        putchar('\n');
    }
}

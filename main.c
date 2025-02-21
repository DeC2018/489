#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Максимальные размеры комнаты
#define MAX_ROWS 100
#define MAX_COLS 100

// Направления робота
#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

// Структура для представления робота
typedef struct {
    int room[MAX_ROWS][MAX_COLS]; // Симуляция комнаты
    int rows, cols; // Размеры комнаты
    int row, col; // Текущая позиция робота
    int dir; // Текущее направление робота
} Robot;

// Инициализация робота
void initRobot(Robot* robot, int room[MAX_ROWS][MAX_COLS], int rows, int cols, int startRow, int startCol) {
    robot->rows = rows;
    robot->cols = cols;
    robot->row = startRow;
    robot->col = startCol;
    robot->dir = UP; // Начинаем с направления "вверх"

    // Копируем комнату
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            robot->room[i][j] = room[i][j];
        }
    }
}

// Движение робота вперед
bool move(Robot* robot) {
    int newRow = robot->row;
    int newCol = robot->col;

    // Вычисляем новую позицию в зависимости от направления
    switch (robot->dir) {
        case UP: newRow--; break;
        case RIGHT: newCol++; break;
        case DOWN: newRow++; break;
        case LEFT: newCol--; break;
    }

    // Проверяем, можно ли двигаться в новую клетку
    if (newRow >= 0 && newRow < robot->rows && newCol >= 0 && newCol < robot->cols && robot->room[newRow][newCol] == 1) {
        robot->row = newRow;
        robot->col = newCol;
        printf("Robot moved to (%d, %d).\n", robot->row, robot->col);
        return true;
    }

    printf("Robot hit a wall.\n");
    return false;
}

// Поворот робота влево
void turnLeft(Robot* robot) {
    robot->dir = (robot->dir - 1 + 4) % 4;
    printf("Robot turned left. Now facing: %d\n", robot->dir);
}

// Поворот робота вправо
void turnRight(Robot* robot) {
    robot->dir = (robot->dir + 1) % 4;
    printf("Robot turned right. Now facing: %d\n", robot->dir);
}

// Очистка текущей клетки
void clean(Robot* robot) {
    robot->room[robot->row][robot->col] = 2; // Помечаем клетку как очищенную
    printf("Robot cleaned cell (%d, %d).\n", robot->row, robot->col);
}

// Структура для хранения посещенных клеток
typedef struct {
    int row;
    int col;
} Cell;

// Функция для возврата робота в предыдущую клетку
void goBack(Robot* robot) {
    turnRight(robot);
    turnRight(robot);
    move(robot);
    turnRight(robot);
    turnRight(robot);
}

// Рекурсивная функция для очистки комнаты
void backtrack(Robot* robot, Cell visited[], int* visitedCount, int row, int col, int dir) {
    // Добавляем текущую клетку в посещенные
    visited[*visitedCount].row = row;
    visited[*visitedCount].col = col;
    (*visitedCount)++;

    clean(robot); // Очищаем текущую клетку

    // Направления: вверх, вправо, вниз, влево
    int directions[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

    // Исследуем все четыре направления
    for (int i = 0; i < 4; i++) {
        int newDir = (dir + i) % 4;
        int newRow = row + directions[newDir][0];
        int newCol = col + directions[newDir][1];

        // Проверяем, была ли уже посещена новая клетка
        bool isVisited = false;
        for (int j = 0; j < *visitedCount; j++) {
            if (visited[j].row == newRow && visited[j].col == newCol) {
                isVisited = true;
                break;
            }
        }

        // Если клетка не посещена и робот может двигаться в нее
        if (!isVisited && move(robot)) {
            backtrack(robot, visited, visitedCount, newRow, newCol, newDir);
            goBack(robot); // Возвращаемся в предыдущую клетку
        }
        turnRight(robot); // Поворачиваем робота для следующего направления
    }
}

// Основная функция для очистки комнаты
void cleanRoom(Robot* robot) {
    Cell visited[MAX_ROWS * MAX_COLS]; // Массив для хранения посещенных клеток
    int visitedCount = 0; // Количество посещенных клеток

    backtrack(robot, visited, &visitedCount, robot->row, robot->col, robot->dir);
}

int main() {
    // Определяем комнату (1: пустая клетка, 0: стена)
    int room[MAX_ROWS][MAX_COLS] = {
        {1, 1, 1, 1, 1, 0, 1, 1},
        {1, 1, 1, 1, 1, 0, 1, 1},
        {1, 0, 1, 1, 1, 1, 1, 1},
        {0, 0, 0, 1, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1}
    };

    int rows = 5; // Количество строк в комнате
    int cols = 8; // Количество столбцов в комнате
    int startRow = 1; // Начальная строка робота
    int startCol = 3; // Начальный столбец робота

    Robot robot;
    initRobot(&robot, room, rows, cols, startRow, startCol); // Инициализация робота

    cleanRoom(&robot); // Очистка комнаты

    printf("Robot cleaned all rooms.\n");
    return 0;
}

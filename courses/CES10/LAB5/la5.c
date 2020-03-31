/***********************************/
/* Aluno: JOÃO LUÍS ROCHA SARMENTO */
/* CES-10: Introdução à Computação */
/* Prof. VITOR CURTIS              */
/***********************************/
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
typedef int **matrix;

int **getMatrix(int matrix_size);
int **getVisited(int matrix_size);
bool theMaze(int **Maze, int current_X, int current_Y, int maze_size, int path_size, int *path[2], int **visited);

int main()
{
    int maze_size;
    scanf("%d", &maze_size);
    matrix Maze = getMatrix(maze_size);    // allocs dynamically the matrix and also reads its values
    int **visited = getVisited(maze_size); // allocs dynamically the matrix that says if the current position was visited before, avoiding infinite loops
    int *path[2];
    path[0] = NULL;
    path[1] = NULL;
    theMaze(Maze, 0, 0, maze_size, 0, path, visited);
    for (int i = 0; i < maze_size; i++)
    {
        free(visited[i]);
        free(Maze[i]);
    }
    free(Maze);
    free(path[0]);
    free(path[1]);
    free(visited);
    return 0;
}

int **getMatrix(int matrix_size)
{
    matrix Matrix;
    Matrix = (matrix)malloc(matrix_size * sizeof(int *));
    for (int i = 0; i < (int)matrix_size; i++)
    {
        Matrix[i] = (int *)malloc(matrix_size * sizeof(int));
    }
    for (int i = 0; i < (int)matrix_size; i++)
    {
        for (int j = 0; j < (int)matrix_size; j++)
        {
            scanf("%d", &Matrix[i][j]);
        }
    }
    return Matrix;
}

bool theMaze(int **Maze, int current_X, int current_Y, int maze_size, int path_size, int *path[2], int **visited)
{
    if (current_X == maze_size - 1 && current_Y == maze_size - 1)
    {
        for (int i = 0; i < path_size; i++)
        {
            printf("%d %d\n", path[0][i], path[1][i]);
        }
        printf("%d %d\n", maze_size - 1, maze_size - 1);
        return true;
    }
    visited[current_X][current_Y] = true;
    if (current_X + 1 < maze_size && !visited[current_X + 1][current_Y] && !Maze[current_X + 1][current_Y])
    {
        path_size++;
        path[0] = (int *)realloc(path[0], (path_size) * sizeof(int));
        path[0][path_size - 1] = current_X;
        path[1] = (int *)realloc(path[1], (path_size) * sizeof(int));
        path[1][path_size - 1] = current_Y;
        bool success = theMaze(Maze, current_X + 1, current_Y, maze_size, path_size, path, visited);
        if (!success)
        {
            path_size--;
            path[0] = (int *)realloc(path[0], (path_size) * sizeof(int));
            path[1] = (int *)realloc(path[1], (path_size) * sizeof(int));
        }
        else return true;
    }
    if (current_X - 1 >= 0 && !visited[current_X - 1][current_Y] && !Maze[current_X - 1][current_Y])
    {
        path_size++;
        path[0] = (int *)realloc(path[0], (path_size) * sizeof(int));
        path[0][path_size - 1] = current_X;
        path[1] = (int *)realloc(path[1], (path_size) * sizeof(int));
        path[1][path_size - 1] = current_Y;
        bool success = theMaze(Maze, current_X - 1, current_Y, maze_size, path_size, path, visited);
        if (!success)
        {
            path_size--;
            path[0] = (int *)realloc(path[0], (path_size) * sizeof(int));
            path[1] = (int *)realloc(path[1], (path_size) * sizeof(int));
        }
        else return true;
    }
    if (current_Y + 1 < maze_size && !visited[current_X][current_Y + 1] && !Maze[current_X][current_Y + 1])
    {
        path_size++;
        path[0] = (int *)realloc(path[0], (path_size) * sizeof(int));
        path[0][path_size - 1] = current_X;
        path[1] = (int *)realloc(path[1], (path_size) * sizeof(int));
        path[1][path_size - 1] = current_Y;
        bool success = theMaze(Maze, current_X, current_Y + 1, maze_size, path_size, path, visited);
        if (!success)
        {
            path_size--;
            path[0] = (int *)realloc(path[0], (path_size) * sizeof(int));
            path[1] = (int *)realloc(path[1], (path_size) * sizeof(int));
        }
        else return true;
    }
    if (current_Y - 1 >= 0 && !visited[current_X][current_Y - 1] && !Maze[current_X][current_Y - 1])
    {
        path_size++;
        path[0] = (int *)realloc(path[0], (path_size) * sizeof(int));
        path[0][path_size - 1] = current_X;
        path[1] = (int *)realloc(path[1], (path_size) * sizeof(int));
        path[1][path_size - 1] = current_Y;
        bool success = theMaze(Maze, current_X, current_Y - 1, maze_size, path_size, path, visited);
        if (!success)
        {
            path_size--;
            path[0] = (int *)realloc(path[0], (path_size) * sizeof(int));
            path[1] = (int *)realloc(path[1], (path_size) * sizeof(int));
        }
        else return true;
    }
    return false;
}

int **getVisited(int matrix_size)
{
    matrix Matrix;
    Matrix = (matrix)malloc(matrix_size * sizeof(int *));
    for (int i = 0; i < (int)matrix_size; i++)
    {
        Matrix[i] = (int *)calloc(matrix_size, sizeof(int));
    }
    return Matrix;
}
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

bool Maze(int **maze, int x, int y, int maze_size, int **visited){
    visited[x][y] = 1;
    if(x == maze_size - 1 && y == maze_size - 1) return true;
    if(x + 1 < maze_size && !maze[x+1][y] && !visited[x+1][y]){
        bool success = Maze(maze, x + 1, y, maze_size, visited); 
        if(!success) maze[x+1][y] = 1;
        else {maze[x+1][y]=2;return true;}
    }if(x - 1 >= 0 && !maze[x-1][y]&& !visited[x-1][y]){
        bool success = Maze(maze, x - 1, y, maze_size, visited);
        if(!success) maze[x-1][y] = 1;
        else {maze[x-1][y]=2;return true;}
    }if(y + 1 < maze_size && !maze[x][y+1]&& !visited[x][y+1]){
        bool success = Maze(maze, x, y+1, maze_size, visited);
        if(!success) maze[x][y+1] = 1;
        else {maze[x][y+1]=2;return true;}
    }if(y - 1 >= 0 && !maze[x][y-1] && !visited[x][y-1]){
        bool success = Maze(maze, x, y-1, maze_size, visited);
        if(!success) maze[x][y-1] = 1;
        else {maze[x][y-1]=2;return true;}
    }
    return !(maze[x][y]=1);
}

int main(){
    int maze_size, x = 0, y = 0;
    scanf("%d", &maze_size);
    int **maze = (int **)malloc(maze_size*sizeof(int *)), **visited = (int **)malloc(maze_size*sizeof(int *));
    for(int i = 0; i < maze_size; i++) {
        maze[i] = (int *)malloc(maze_size*sizeof(int)); visited[i] = (int *)malloc(maze_size*sizeof(int));
        for(int j = 0; j < maze_size; j++){scanf("%d", &maze[i][j]); visited[i][j] = 0;}
    }
    Maze(maze, 0, 0, maze_size, visited);
    for(int i = 0; i < maze_size; i++) for(int j = 0; j < maze_size; j++) visited[i][j] = 0;
    if(maze!=NULL)maze[0][0]=2;
    while(true){
        if(x == maze_size-1 && y == maze_size-1) {printf("%d %d\n", x, y); break;}
        if(maze[x][y]==2 && !visited[x][y]){
            printf("%d %d\n", x, y);
            visited[x][y] = 1;
            if(x + 1 < maze_size && maze[x+1][y]==2 && !visited[x+1][y]) x++;
            else if(x - 1 >= 0 && maze[x-1][y]==2 && !visited[x-1][y]) x--;
            else if(y + 1 < maze_size && maze[x][y+1]==2 && !visited[x][y+1]) y++;
            else if(y - 1 >= 0 && maze[x][y-1]==2 && !visited[x][y-1]) y--;
        }
    }
    for(int i = 0; i < maze_size; i++) free(maze[i]);
    free(maze);
    return 0;
}


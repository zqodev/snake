#ifndef GRID_H
#define GRID_H

#define GRID_HEIGHT       (12)
#define GRID_WIDTH        (32)
#define DEFAULT_DIRECTION 'r'

typedef struct {
    int x;
    int y;
} Coord;

int get_level(int *snake_length);
void show_score(int *snake_length);
void snake_move(char grid[GRID_HEIGHT][GRID_WIDTH], char direction, Coord snake_body[], int *snake_length);
void init_grid(char grid[GRID_HEIGHT][GRID_WIDTH], Coord snake_body[], int *snake_length);
void show_grid(char grid[GRID_HEIGHT][GRID_WIDTH]);

#endif
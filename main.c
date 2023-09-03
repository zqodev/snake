#include <conio.h>
#include <process.h>
#include <windows.h>

#include "game.h"

char direction = DEFAULT_DIRECTION;

int main(void)
{
    char grid[GRID_HEIGHT][GRID_WIDTH];
    Coord snake_body[GRID_HEIGHT * GRID_WIDTH];
    int snake_length = 0;
    char key;

    init_grid(grid, snake_body, &snake_length);
    show_grid(grid);

    while (1) {
        if (kbhit()) {
            key = (char)getch();

            switch (key) {
                case 'z':
                    direction = 't';
                    break;
                case 's':
                    direction = 'b';
                    break;
                case 'q':
                    direction = 'l';
                    break;
                case 'd':
                    direction = 'r';
                    break;
            }

            system("cls");
            show_grid(grid);
        }

        system("cls");
        snake_move(grid, direction, snake_body, &snake_length);
        show_grid(grid);
        show_score(&snake_length);

        switch (get_level(&snake_length)) {
            case 1: {
                Sleep(1000);
                break;
            }
            case 2: {
                Sleep(750);
                break;
            }
            case 3: {
                Sleep(500);
                break;
            }
            case 4: {
                Sleep(250);
                break;
            }
            case 5: {
                Sleep(125);
                break;
            }
        }
    }
}

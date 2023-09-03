#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#include "game.h"
#include "color.h"

#define SNAKE_CHAR  'O'
#define FOOD_CHAR   '#'
#define BORDER_CHAR '|'

void random_food(char grid[GRID_HEIGHT][GRID_WIDTH])
{
    srand(time(NULL));

    int x, y;
    do {
        x = rand() % GRID_HEIGHT;
        y = rand() % GRID_WIDTH;
    } while (grid[x][y] != ' ');

    grid[x][y] = FOOD_CHAR;
}

void snake_init(char grid[GRID_HEIGHT][GRID_WIDTH], Coord snake_body[], int *snake_length)
{
    srand(time(NULL));

    int middle_x = GRID_HEIGHT / 2;
    int middle_y = GRID_WIDTH / 2;

    int x, y;
    do {
        x = middle_x + rand() % 3 - 1;
        y = middle_y + rand() % 3 - 1;
    } while (grid[x][y] != ' ');

    snake_body[0].x = x;
    snake_body[0].y = y;
    *snake_length = 1;

    grid[x][y] = SNAKE_CHAR;

    random_food(grid);
}

int get_level(int *snake_length)
{
    if (*snake_length < 5) {
        return 1;
    } else if (snake_length < 10) {
        return 2;
    } else if (snake_length < 15) {
        return 3;
    } else if (snake_length < 20) {
        return 4;
    } else if (snake_length < 25) {
        return 5;
    }

    return 0;
}

void show_score(int *snake_length)
{
    set_console_color(COLOR_DEFAULT);
    printf("Votre score: ");
    set_console_color(COLOR_YELLOW);
    printf("%d", *snake_length);
    set_console_color(COLOR_DEFAULT);
    printf("\nRemplissage: ");
    set_console_color(COLOR_YELLOW);
    printf("%.2f%%", ((double)*snake_length / (GRID_WIDTH * GRID_HEIGHT)) * 100.0);
    set_console_color(COLOR_DEFAULT);
    printf("\nNiveau: ");
    set_console_color(COLOR_YELLOW);
    printf("%d", get_level(snake_length));
}

void loose_menu(int *snake_length)
{
    printf("Vous avez perdu !\nLa taille de votre serpent etait de : %d cellules", *snake_length);
    getch();
    exit(0);
}

void snake_move(char grid[GRID_HEIGHT][GRID_WIDTH], char direction, Coord snake_body[], int *snake_length)
{
    Coord snake_head = snake_body[0];
    Coord new_head;

    switch (direction) {
        case 't':
            new_head.x = snake_head.x - 1;
            new_head.y = snake_head.y;
            break;
        case 'b':
            new_head.x = snake_head.x + 1;
            new_head.y = snake_head.y;
            break;
        case 'l':
            new_head.x = snake_head.x;
            new_head.y = snake_head.y - 1;
            break;
        case 'r':
            new_head.x = snake_head.x;
            new_head.y = snake_head.y + 1;
            break;
        default:
            return;
    }

    if (grid[new_head.x][new_head.y] == BORDER_CHAR) {
        loose_menu(snake_length);
        return;
    }

    for (int i = 0; i < *snake_length; i++) {
        if (snake_body[i].x == new_head.x && snake_body[i].y == new_head.y) {
            loose_menu(snake_length);
            return;
        }
    }

    if (grid[new_head.x][new_head.y] == FOOD_CHAR) {
        (*snake_length)++;
        random_food(grid);
    }
    else {
        grid[snake_body[*snake_length - 1].x][snake_body[*snake_length - 1].y] = ' ';
    }

    grid[new_head.x][new_head.y] = SNAKE_CHAR;

    for (int i = *snake_length - 1; i > 0; i--) {
        snake_body[i] = snake_body[i - 1];
    }
    snake_body[0] = new_head;
}

void init_grid(char grid[GRID_HEIGHT][GRID_WIDTH], Coord snake_body[], int *snake_length)
{
    for (int x = 0; x < GRID_HEIGHT; x++) {
        for (int y = 0; y < GRID_WIDTH; y++) {
            grid[x][y] = ' ';
        }
    }

    for (int x = 0; x < GRID_HEIGHT; x++) {
        grid[x][0] = BORDER_CHAR;
        grid[x][GRID_WIDTH - 1] = BORDER_CHAR;
    }
    for (int y = 0; y < GRID_WIDTH; y++) {
        grid[0][y] = BORDER_CHAR;
        grid[GRID_HEIGHT - 1][y] = BORDER_CHAR;
    }

    snake_init(grid, snake_body, snake_length);
}

void show_grid(char grid[GRID_HEIGHT][GRID_WIDTH])
{
    for (int i = 0; i < GRID_HEIGHT; i++) {
        for (int j = 0; j < GRID_WIDTH; j++) {
            switch (grid[i][j]) {
                case SNAKE_CHAR: {
                    set_console_color(COLOR_GREEN);
                    break;
                }
                case FOOD_CHAR: {
                    set_console_color(COLOR_MAGENTA);
                    break;
                }
                case BORDER_CHAR: {
                   set_console_color(COLOR_RED);
                   break;
                }
            }

            printf("%c", grid[i][j]);
        }
        printf("\n");
    }
}
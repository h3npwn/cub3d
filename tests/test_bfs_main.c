#include "../headers/cub3d.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    t_map map;
    char **grid;
    char **new_grid;
    int width = 3;
    int height = 3;

    map.width = width;
    map.height = height;

    /* original map grid (no padding)
       use '1' for walls and ' ' for open space */
    grid = malloc(sizeof(char *) * (height + 1));
    grid[0] = strdup("111");
    grid[1] = strdup("1 1");
    grid[2] = strdup("111");
    grid[3] = NULL;
    map.grid = grid;

    /* create copy like copy_map would (adds padding rows/cols) */
    new_grid = malloc(sizeof(char *) * (height + 3));
    new_grid[height + 2] = NULL;

    new_grid[0] = malloc(width + 2);
    memset(new_grid[0], ' ', width + 2);
    new_grid[0][width + 1] = 0;

    for (int i = 0; i < height; i++)
    {
        new_grid[i + 1] = malloc(width + 2);
        memset(new_grid[i + 1], ' ', width + 2);
        new_grid[i + 1][width + 1] = 0;
        memcpy(new_grid[i + 1] + 1, grid[i], strlen(grid[i]));
    }

    new_grid[height + 1] = malloc(width + 2);
    memset(new_grid[height + 1], ' ', width + 2);
    new_grid[height + 1][width + 1] = 0;

    printf("Running bfs test (expect printed copy after bfs)\n");
    bfs(map, new_grid);

    /* free memory */
    for (int i = 0; i < height; i++)
        free(grid[i]);
    free(grid);
    for (int i = 0; i < height + 2; i++)
        free(new_grid[i]);
    free(new_grid);

    return 0;
}

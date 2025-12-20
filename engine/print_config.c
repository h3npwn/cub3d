#include <stdio.h>
#include "../headers/cub3d.h"

static void print_rgb(const char *name, t_rgb c)
{
	printf("%s: r=%d g=%d b=%d value=0x%06x\n", name, c.r, c.g, c.b, c.value);
}

void print_config(t_config *cfg)
{
	int i;

	if (!cfg)
	{
		printf("t_config: (null)\n");
		return;
	}
	printf("=== t_config ===\n");
	printf("filename: %s\n", cfg->filename ? cfg->filename : "(null)");
	printf("north: %s\n", cfg->north ? cfg->north : "(null)");
	printf("south: %s\n", cfg->south ? cfg->south : "(null)");
	printf("west:  %s\n", cfg->west ? cfg->west : "(null)");
	printf("east:  %s\n", cfg->east ? cfg->east : "(null)");
	print_rgb("floor", cfg->floor);
	print_rgb("ceiling", cfg->ceiling);
	printf("map: width=%d height=%d\n", cfg->map.width, cfg->map.height);
	if (cfg->map.grid)
	{
		for (i = 0; i < cfg->map.height; ++i)
		{
			printf("%3d: %s\n", i, cfg->map.grid[i] ? cfg->map.grid[i] : "(null)");
		}
	}
	else
		printf("map.grid: (null)\n");

	printf("player.pos:   %f, %f\n", cfg->player.pos[X], cfg->player.pos[Y]);
	printf("player.dir_view: %f, %f\n", cfg->player.dir_view[X], cfg->player.dir_view[Y]);
	printf("player.plane: %f, %f\n", cfg->player.plane[X], cfg->player.plane[Y]);
	printf("player.dir: %c\n", cfg->player.dir ? cfg->player.dir : '?');
	printf("=== end ===\n");
}

#include "../includes/cub3d.h"
#include <stdio.h>

void print_config(t_cub3d *cfg)
{
	printf("Configuration:\n");
	printf("North Texture Path: %s\n", cfg->north_path);
	printf("South Texture Path: %s\n", cfg->south_path);
	printf("East Texture Path: %s\n", cfg->east_path);
	printf("West Texture Path: %s\n", cfg->west_path);
	// printf("ciel Color set to => Hex: 0x%06X\n",((void *)cfg->f_color));
	// printf("Floor Color: => Hex: 0x%06X\n",((void *)cfg->c_color));
	printf("player Initial Direction: %c\n", cfg->initial_dir);
	printf("POSITION => X: %.2f, Y: %.2f\n", cfg->player.posx, cfg->player.posy);
	printf("DIRECTION VECTOR => dir_x: %.2f, dir_y: %.2f\n", cfg->player.dir_x, cfg->player.dir_y);
	printf("PLANE VECTOR => plane_x: %.2f, plane_y: %.2f\n", cfg->player.plane_x, cfg->player.plane_y);
}

#include "../includes/cub3d.h"
#include <stdio.h>


void print_config(t_cub3d *cfg)
{
	printf("Configuration:\n");
	printf("North Texture Path: %s\n", cfg->north_path);
	printf("South Texture Path: %s\n", cfg->south_path);
	printf("East Texture Path: %s\n", cfg->east_path);
	printf("West Texture Path: %s\n", cfg->west_path);
	printf("ciel Color set to => Hex: 0x%06X\n",((void *)cfg->f_color));
	printf("Floor Color: => Hex: 0x%06X\n",((void *)cfg->c_color));
}

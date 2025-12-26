#include "includes/cub3d.h"
#include "includes/types.h"
#include "libft/libft.h"


void init_game(char **argv, t_cub3d *cub3d)
{
    ft_memset(cub3d, 0, sizeof(t_cub3d));
    cub3d->map_path = argv[1];
    ft_init_map(cub3d);
	set_directions(cub3d);
    //exit(1);
}

int	main(int argc, char **argv)
{
    t_cub3d	cub3d;

    if (argc != 2)
        exit_failure(ERR_ARGC, 1);
    init_game(argv, &cub3d);
    return (0);
}
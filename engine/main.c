
#include "../headers/cub3d.h"

int	main(int ac, char **av)
{
	t_config	*config;

	if (ac != 2)
		exit_failure(0, 1);
	config = init(av);
	ft_config(config);
	heap_manager(0, 'f', 0);
}

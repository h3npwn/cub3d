
#include "../../headers/cub3d.h"

void exit_failure(int code, int isnoexit)
{
	const char errors[][50] = {
		"Error\nInvalid number of arguments.\n",
		"Error\nCannot open file OR extension invalid.\n",
		"Error\nInvalid configuration format.\n",
		"Error\nMemory allocation failed.\n",
		"Error\nInvalid map format.\n",
		"Error\nUnknown error occurred.\n"
	};
	ft_putstr_fd(errors[code], 2);
	heap_manager(0, 'f', 0);
    
	exit(isnoexit);
}
t_config* init(char **av)
{
	t_config	*config;

	config = (t_config *)heap_manager(sizeof(t_config), 'a', 0);
	if (!config)
		exit_failure(ERR_MALLOC, 1  );
	ft_memset(config, 0, sizeof(t_config));
	config->filename = av[1];

	return (config);
}
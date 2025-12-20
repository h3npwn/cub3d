# Top-level Makefile for cub3d project
.PHONY: all libft mlx engine clean fclean re

all: libft mlx engine

libft:
	$(MAKE) -C libft

mlx:
	$(MAKE) -C engine/minilibx-linux

engine:
	$(MAKE) -C engine

clean:
	$(MAKE) -C libft clean
	$(MAKE) -C engine clean
	$(MAKE) -C engine/minilibx-linux clean

fclean:
	$(MAKE) -C libft fclean
	$(MAKE) -C engine fclean
	$(MAKE) -C engine/minilibx-linux clean

re:
	$(MAKE) -C libft re
	$(MAKE) -C engine/minilibx-linux re
	$(MAKE) -C engine re

# Top-level Makefile for cub3d project
.PHONY: all libft mlx engine clean fclean re

CC = cc
CFLAGS := -Wall -Wextra -Werror

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

ENGINE_DIR = engine
GNL_DIR = gnl
MLX_DIR = $(ENGINE_DIR)/minilibx-linux
MLX_LIBS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lpthread -ldl

ENGINE_SRCS = $(ENGINE_DIR)/main.c parsing/parse.c $(ENGINE_DIR)/print_config.c $(GNL_DIR)/get_next_line.c
ENGINE_OBJS = $(ENGINE_SRCS:.c=.o)
ENGINE_BIN = cub3d

all: libft mlx engine

libft:
	$(MAKE) -C $(LIBFT_DIR)

mlx:
	SKIP_TESTS=1 $(MAKE) -C $(MLX_DIR)

engine: $(ENGINE_BIN)

$(ENGINE_BIN): $(ENGINE_OBJS) $(LIBFT)
	$(MAKE) -C $(LIBFT_DIR)
	SKIP_TESTS=1 $(MAKE) -C $(MLX_DIR)
	$(CC) $(CFLAGS) -o $@ $(ENGINE_OBJS) $(LIBFT) $(MLX_LIBS)

$(ENGINE_DIR)/%.o: $(ENGINE_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(GNL_DIR)/%.o: $(GNL_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean
	rm -f $(ENGINE_OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(ENGINE_BIN)

re: fclean all

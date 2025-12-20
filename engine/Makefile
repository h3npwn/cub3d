# Engine Makefile
NAME = cub3d

# Explicit, static source list (avoid wildcard)
SRCS := main.c parse.c get_next_line.c print_config.c
OBJS := $(SRCS:.c=.o)

LIBFT_DIR = ../libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = minilibx-linux
# Removed -lz to avoid linking on systems without zlib development package
MLX_LIBS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lpthread -ldl

CC = cc
CFLAGS := -Wall -Wextra -Werror

.PHONY: all clean fclean re libft mlx

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(MAKE) -C $(LIBFT_DIR)
	SKIP_TESTS=1 $(MAKE) -C $(MLX_DIR)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBFT) $(MLX_LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

libft:
	$(MAKE) -C $(LIBFT_DIR)

mlx:
	SKIP_TESTS=1 $(MAKE) -C $(MLX_DIR)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

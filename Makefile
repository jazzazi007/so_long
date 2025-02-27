
NAME 	= so_long

CC 		= gcc

CFLAGS 	= -Wall -Wextra -Werror

# Path to your MiniLibX library (adjust if necessary)
MLX_PATH = ./minilibx-linux
LIBMLX = -L$(MLX_PATH) -lmlx -lX11 -lXext -lm

SRCS 	=	./src/cont_map_check.c			\
		./src/exit_game.c			\
		./src/free_map.c			\
		./src/ini_mlx.c				\
		./src/key_handler.c			\
		./src/load_map.c			\
		./src/main.c				\
		./src/map_check.c			\
		./src/movement.c			\
		./src/render_map.c			\
		./get_next_line_42/get_next_line.c			\
		./get_next_line_42/get_next_line_utils.c

all: $(NAME)

OBJS	= $(SRCS:.c=.o)

LIBFT_DIR = 42_libft
Printf_DIR = ft_printf

LIBFT = $(LIBFT_DIR)/libft.a
Printf = $(Printf_DIR)/libftprintf.a

all: $(LIBFT) $(Printf) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)
$(Printf):
	$(MAKE) -C $(Printf_DIR)
$(NAME): $(OBJS) $(LIBFT) $(Printf)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBFT_DIR) -L$(Printf_DIR) -lft

%.o: %.c
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) -I$(Printf_DIR) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(Printf_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(Printf_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
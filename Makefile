NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = ./42_libft
Printf_DIR = ./ft_printf

LIBFT = $(LIBFT_DIR)/libft.a
Printf = $(Printf_DIR)/libftprintf.a
LIBMLX = -L. -lmlx -lX11 -lXext -lm

SRCS = ./src/cont_map_check.c ./src/exit_game.c ./src/free_map.c ./src/ini_mlx.c \
       ./src/key_handler.c ./src/load_map.c ./src/main.c ./src/map_check.c \
       ./src/movement.c ./src/handle_stars.c ./src/render_map.c ./src/cont_map_utils.c \
       ./get_next_line_42/get_next_line.c ./get_next_line_42/get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

all:  $(LIBFT) $(Printf) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(Printf):
	$(MAKE) -C $(Printf_DIR)

$(NAME): $(OBJS) $(LIBFT) $(Printf)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L$(LIBFT_DIR) -lft -L$(Printf_DIR) -lftprintf $(LIBMLX)

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
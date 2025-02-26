
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
		./gnl/get_next_line.c			\
		./gnl/get_next_line_utils.c

all: $(NAME)

OBJS	= $(SRCS:.c=.o)

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) $^ $(LIBMLX) -o $@
	@echo "\[\033[4;35m                                                            \n\
	  ▄████████  ▄██████▄          ▄█          ▄██████▄  ███▄▄▄▄      ▄██████▄      \n\
	 ███    ███ ███    ███        ███         ███    ███ ███▀▀▀██▄   ███    ███     \n\
	 ███    █▀  ███    ███        ███         ███    ███ ███   ███   ███    █▀      \n\
	 ███        ███    ███        ███         ███    ███ ███   ███  ▄███            \n\
	███████████ ███    ███        ███         ███    ███ ███   ███ ▀▀███ ████▄      \n\
	        ███ ███    ███        ███         ███    ███ ███   ███   ███    ███     \n\
	  ▄█    ███ ███    ███        ███▌     ▄  ███    ███ ███   ███   ███    ███     \n\
	▄████████▀   ▀██████▀  █████  ███████▄▄██  ▀██████▀   ▀█   █▀    ████████▀      \n\
                                                                       	 		\033[0m"
	@echo "                                \033[44mBy: Abood0x1"
%.o:%.c
	@$(CC) $(CFLAGS) -c $^ -o $@

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all


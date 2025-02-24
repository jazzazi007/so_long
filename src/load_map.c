

#include "../include/so_long_header.h"

void	handle_error(const char *message, int fd)
{
	perror(message);
	if (fd >= 0)
		close(fd);
	exit(1);
}

static char	*read_line(int fd, int *rows, int *max_cols)
{
	char	*line;
	int		c_len;

	line = get_next_line(fd);
	if (line != NULL)
	{
		c_len = ft_strlen(line) - 1;
		if (max_cols && c_len > *max_cols)
			*max_cols = c_len;
		if (rows)
			(*rows)++;
	}
	return (line);
}

int	get_x_y(t_GameMap *game, int fd)
{
	int		l_col;
	char	*line;

	game->rows = 0;
	game->cols = 0;
	l_col = 0;
	line = read_line(fd, &game->rows, &l_col);
	while (line != NULL)
	{
		free(line);
		line = read_line(fd, &game->rows, &l_col);
	}
	game->cols = l_col;
	return (0);
}

int	get_map(t_GameMap *game, int fd)
{
	int		row;
	char	*line;

	row = 0;
	game->map = malloc(sizeof(char *) * game->rows);
	if (!game->map)
	{
		perror("Allocation failed");
		return (1);
	}
	line = read_line(fd, &row, NULL);
	while (line != NULL)
	{
		game->map[row - 1] = line;
		line = read_line(fd, &row, NULL);
	}
	return (0);
}

int	load_first_check_map(t_GameMap *game, char *file_name)
{
	int		fd;
	char	*check_name;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		handle_error("Failed to open file", -1);
	check_name = file_name + (ft_strlen(file_name) - 4);
	if (strncmp(check_name, ".ber", 4))
		handle_error("Error!\n Wrong file extension", fd);
	if (get_x_y(game, fd) != 0)
		handle_error("Failed to get map dimensions", fd);
	close(fd);
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		handle_error("Failed to open file", -1);
	if (get_map(game, fd) != 0)
		handle_error("Failed to load map", fd);
	close(fd);
	return (0);
}

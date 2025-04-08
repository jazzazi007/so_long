/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaljazz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:28:49 by moaljazz          #+#    #+#             */
/*   Updated: 2025/04/04 15:28:50 by moaljazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_header.h"

static char	*read_line(int fd, int *rows, int *max_cols)
{
	char	*line;
	int		line_len;

	line = get_next_line(fd);
	if (!line || line[0] == '\0')
	{
		return (NULL);
	}
	if (line)
	{
		line_len = ft_strlen(line) - 1;
		if (max_cols && line_len > *max_cols)
			*max_cols = line_len;
		if (rows)
			(*rows)++;
	}
	return (line);
}

static int	validate_file_extension(const char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len < 4)
		return (0);
	return (!ft_strncmp(filename + len - 4, ".ber", 4));
}

static int	get_map_dimensions(t_GMap *game, int fd)
{
	int		current_col;
	char	*line;

	game->rows = 0;
	game->columns = 0;
	current_col = 0;
	line = read_line(fd, &game->rows, &current_col);
	if (!line || line[0] == '\0')
	{
		ft_printf("Error\nEmpty map\n");
		return (1);
	}
	while (line)
	{
		free(line);
		line = read_line(fd, &game->rows, &current_col);
	}
	game->columns = current_col;
	if (game->rows == 0 || game->columns == 0)
		return (1);
	return (0);
}

static int	load_map_data(t_GMap *game, int fd)
{
	int		row;
	char	*line;

	game->map = malloc(sizeof(char *) * game->rows);
	if (!game->map)
	{
		return (1);
	}
	row = 0;
	line = read_line(fd, &row, NULL);
	while (line)
	{
		game->map[row - 1] = line;
		line = read_line(fd, &row, NULL);
	}
	return (0);
}

int	load_first_check_map(t_GMap *game, char *file_name)
{
	int	fd;

	if (!validate_file_extension(file_name))
		handle_error("Invalid file extension (must be .ber)", -1);
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		handle_error("Failed to open map file\n", -1);
	if (get_map_dimensions(game, fd) != 0)
	{
		close(fd);
		handle_error("Failed to get map dimensions\n", -1);
	}
	close(fd);
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		handle_error("Failed to reopen map file\n", -1);
	if (load_map_data(game, fd) != 0)
	{
		close(fd);
		handle_error("Failed to load map data\n", -1);
	}
	close(fd);
	return (0);
}

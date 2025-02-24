

#include "../include/so_long_header.h"

int	validate_char(char c, t_GameMap *game, int i, int j)
{
	if (c == 'E')
	{
		game->end++;
		game->exit_x = i;
		game->exit_y = j;
	}
	else if (c == 'P')
	{
		game->start++;
		game->start_x = i;
		game->start_y = j;
	}
	else if (c == 'C')
		game->collectables++;
	else if (c == '0' || c == '1')
		return (0);
	else
	{
		perror("Entered Map failure");
		return (1);
	}
	return (0);
}

int	map_components_check(t_GameMap *game)
{
	int	i;
	int	j;

	game->start = 0;
	game->end = 0;
	game->collectables = 0;
	game->start_x = -1;
	game->start_y = -1;
	game->exit_x = -1;
	game->exit_y = -1;
	i = 0;
	while (i < game->rows)
	{
		j = 0;
		while (game->map[i][j] != '\0' && game->map[i][j] != '\n' &&
					validate_char(game->map[i][j], game, i, j) == 0)
			j++;
		i++;
	}
	if (game->start != 1 || game->end != 1 || game->collectables < 1)
	{
		perror("Invalid map components");
		return (1);
	}
	return (0);
}

int	shape_checker(t_GameMap *game)
{
	int	i;

	i = 0;
	while (game->map[0][i] != '\0' && game->map[0][i] != '\n')
		i++;
	if (i == game->rows)
	{
		perror ("Map is not rectangular");
		return (1);
	}
	return (0);
}

int	mid_rows_boarder_check(t_GameMap *game)
{
	int	i;
	int	len;

	i = 1;
	while (i < game->rows - 1)
	{
		len = game->cols;
		if (game->map[i][len - 1] == '\n')
			len -= 1;
		if (game->map[i][0] != '1' || game->map[i][len - 1] != '1')
		{
			perror("Mid Rows Faulty");
			return (1);
		}
		i++;
	}
	return (0);
}

int	top_bottom_rows_boarder_check(t_GameMap *game)
{
	int	j;

	j = 0;
	while (game->map[0][j] != '\0' && game->map[0][j] != '\n')
	{
		if (game->map[0][j] != '1')
		{
			perror("1st Row Faulty");
			return (1);
		}
		j++;
	}
	j = 0;
	while (game->map[game->rows - 1][j] != '\0' &&
				game->map[game->rows - 1][j] != '\n')
	{
		if (game->map[game->rows - 1][j] != '1')
		{
			perror("Last Row Faulty");
			return (1);
		}
		j++;
	}
	return (0);
}

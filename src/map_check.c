/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaljazz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:29:08 by moaljazz          #+#    #+#             */
/*   Updated: 2025/04/04 15:29:09 by moaljazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_header.h"

void	*safe_calloc(size_t num, size_t size, void **ptr_array, int index)
{
	void	*ptr;

	ptr = calloc(num, size);
	if (!ptr)
	{
		perror("Memory allocation failed");
		while (index >= 0)
		{
			free(ptr_array[index]);
			ptr_array[index] = NULL;
			index--;
		}
		free(ptr_array);
		ptr_array = NULL;
		exit(EXIT_FAILURE);
	}
	return (ptr);
}

int	is_valid(int x, int y, t_GMap *game, char **visited)
{
	return (x >= 0 && x < game->rows && y >= 0 && y < game->columns
		&& !visited[x][y] && game->map[x][y] != '1');
}

void	flood_fill(t_GMap *game, int x, int y, char **visited)
{
	static int	directions[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
	int			i;
	int			new_x;
	int			new_y;

	visited[x][y] = 1;
	i = 0;
	while (i < 4)
	{
		new_x = x + directions[i][0];
		new_y = y + directions[i][1];
		if (is_valid(new_x, new_y, game, visited))
		{
			flood_fill(game, new_x, new_y, visited);
		}
		i++;
	}
}

int	is_exit_reachable(t_GMap *game)
{
	char	**visited;
	int		i;
	int		reachable;

	visited = malloc(game->rows * sizeof(char *));
	if (!visited)
	{
		perror("Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < game->rows)
	{
		visited[i] = safe_calloc(game->columns, sizeof(char), (void **)visited,
				i);
		i++;
	}
	flood_fill(game, game->begin_x, game->begin_y, visited);
	reachable = visited[game->end_x][game->end_y];
	i = 0;
	while (i < game->rows)
		free(visited[i++]);
	free(visited);
	visited = NULL;
	return (reachable);
}

int	validate_map(t_GMap *game)
{
	if (shape_checker(game) != 0 || map_components_check(game) != 0)
	{
		ft_putstr_fd("Error\nInvalid Map-Shape or Components\n", 2);
		return (1);
	}
	if (mid_rows_boarder_check(game) != 0
		|| top_bottom_rows_boarder_check(game) != 0)
	{
		ft_putstr_fd("Boarder Failure", 2);
		return (1);
	}
	if (!(is_exit_reachable(game) && is_all_collectibles_reachable(game)))
	{
		ft_putstr_fd("Error\nExit or collectibles not reachable\n", 2);
		return (1);
	}
	if (validate_collectibles_position(game))
    {
        ft_putstr_fd("Error\nCollectible in unreachable position\n", 2);
        return (1);
    }
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_stars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaljazz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 19:47:32 by moaljazz          #+#    #+#             */
/*   Updated: 2025/04/06 19:47:36 by moaljazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_header.h"

int	ret_ini_mlx(t_setup *vars, t_GMap *game)
{
	vars->rck = vars->rck_down;
	free_map(game);
	return (0);
}

int	check_star_acess(t_GMap *game, int x, int y)
{
	int	access_path;

	access_path = 0;
	if (x > 0 && (game->map[x - 1][y] == '1' || game->map[x - 1][y] == 'E'))
		access_path++;
	if (x < game->rows - 1 && (game->map[x + 1][y] == '1' || game->map[x
			+ 1][y] == 'E'))
		access_path++;
	if (y > 0 && (game->map[x][y - 1] == '1' || game->map[x][y - 1] == 'E'))
		access_path++;
	if (y < game->columns - 1 && (game->map[x][y + 1] == '1' || game->map[x][y
		+ 1] == 'E'))
		access_path++;
	return (access_path);
}

int	validate_collectibles_position(t_GMap *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->rows)
	{
		j = 0;
		while (j < game->columns)
		{
			if (game->map[i][j] == 'C')
			{
				if (check_star_acess(game, i, j) == 4)
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

static int	collictables(t_GMap *game, char **visited)
{
	int	i;
	int	j;
	int	reachable_collectibles;

	reachable_collectibles = 0;
	i = 0;
	while (i < game->rows)
	{
		j = 0;
		while (j < game->columns)
		{
			if (game->map[i][j] == 'C' && visited[i][j])
				reachable_collectibles++;
			j++;
		}
		i++;
	}
	return (reachable_collectibles);
}

int	is_all_collectibles_reachable(t_GMap *game)
{
	char	**visited;
	int		i;
	int		reachable_collectibles;

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
	reachable_collectibles = collictables(game, visited);
	i = 0;
	while (i < game->rows)
		free(visited[i++]);
	free(visited);
	return (reachable_collectibles == game->collectable);
}

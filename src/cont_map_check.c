/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cont_map_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaljazz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:27:54 by moaljazz          #+#    #+#             */
/*   Updated: 2025/04/04 15:27:56 by moaljazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_header.h"

void	init_game_stats(t_GMap *game)
{
	game->start = 0;
	game->end = 0;
	game->collectable = 0;
	game->begin_x = -1;
	game->begin_y = -1;
	game->end_x = -1;
	game->end_y = -1;
}

int	process_map_element(char element, t_GMap *game, int x, int y)
{
	if (element == 'E')
	{
		game->end++;
		game->end_x = x;
		game->end_y = y;
	}
	else if (element == 'P')
	{
		game->start++;
		game->begin_x = x;
		game->begin_y = y;
	}
	else if (element == 'C')
		game->collectable++;
	else if (element == '0' || element == '1')
		return (0);
	else
	{
		ft_putstr_fd("Error\nInvalid map character\n", 2);
		return (1);
	}
	return (0);
}

int	check_border_row(char *row)
{
	int	i;

	i = 0;
	while (row[i] && row[i] != '\n')
	{
		if (row[i] != '1')
		{
			ft_putstr_fd("Error\nInvalid border\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

int	verify_side_borders(t_GMap *game)
{
	int	i;
	int	last_col;

	i = 1;
	while (i < game->rows - 1)
	{
		last_col = game->columns - 1;
		if (game->map[i][last_col] == '\n')
			last_col--;
		if (game->map[i][0] != '1' || game->map[i][last_col] != '1')
		{
			ft_putstr_fd("Error\nInvalid side borders\n", 2);
			return (1);
		}
		i++;
	}
	return (0);
}

int	map_components_check(t_GMap *game)
{
	int	i;
	int	j;

	init_game_stats(game);
	i = 0;
	while (i < game->rows)
	{
		j = 0;
		while (game->map[i][j] && game->map[i][j] != '\n')
		{
			if (process_map_element(game->map[i][j], game, i, j))
				return (1);
			j++;
		}
		i++;
	}
	if (game->start != 1 || game->end != 1 || game->collectable < 1)
	{
		ft_putstr_fd("Error\nInvalid map components count\n", 2);
		return (1);
	}
	return (0);
}

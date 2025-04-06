/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ini_mlx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaljazz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:28:29 by moaljazz          #+#    #+#             */
/*   Updated: 2025/04/04 15:28:33 by moaljazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_header.h"

static int	allocate_map_memory(t_setup *vars, t_GMap *game)
{
	int	i;

	vars->map = malloc(game->rows * sizeof(char *));
	if (!vars->map)
		return (1);
	i = 0;
	while (i < game->rows)
	{
		vars->map[i] = malloc(game->columns * sizeof(char));
		if (!vars->map[i])
		{
			while (--i >= 0)
				free(vars->map[i]);
			free(vars->map);
			return (1);
		}
		memcpy(vars->map[i], game->map[i], game->columns * sizeof(char));
		i++;
	}
	return (0);
}

static void	setup_game_parameters(t_setup *vars, t_GMap *game)
{
	vars->tile_size = 37;
	vars->map_rows = game->rows;
	vars->map_cols = game->columns;
	vars->player_x = -1;
	vars->player_y = -1;
	vars->collectibles_left = game->collectable;
	vars->move_count = 0;
	vars->last_direction = 'd';
	rck_start_position(vars);
}

static int	load_player_images(t_setup *vars)
{
	vars->rck_up = mlx_xpm_file_to_image(vars->mlx, "./pics/rocket.xpm",
			&vars->tile_size, &vars->tile_size);
	vars->rck_down = mlx_xpm_file_to_image(vars->mlx, "./pics/rocket_down.xpm",
			&vars->tile_size, &vars->tile_size);
	vars->rck_left = mlx_xpm_file_to_image(vars->mlx, "./pics/rocket_left.xpm",
			&vars->tile_size, &vars->tile_size);
	vars->rck_right = mlx_xpm_file_to_image(vars->mlx,
			"./pics/rocket_right.xpm", &vars->tile_size, &vars->tile_size);
	return (!vars->rck_up || !vars->rck_down || !vars->rck_left
		|| !vars->rck_right);
}

static int	load_map_elements(t_setup *vars)
{
	vars->hole = mlx_xpm_file_to_image(vars->mlx, "./pics/black.xpm",
			&vars->tile_size, &vars->tile_size);
	vars->map_tile = mlx_xpm_file_to_image(vars->mlx, "./pics/map.xpm",
			&vars->tile_size, &vars->tile_size);
	vars->stars = mlx_xpm_file_to_image(vars->mlx, "./pics/star.xpm",
			&vars->tile_size, &vars->tile_size);
	vars->earth = mlx_xpm_file_to_image(vars->mlx, "./pics/earth.xpm",
			&vars->tile_size, &vars->tile_size);
	vars->sun = mlx_xpm_file_to_image(vars->mlx, "./pics/sun.xpm",
			&vars->tile_size, &vars->tile_size);
	vars->spiral = mlx_xpm_file_to_image(vars->mlx, "./pics/sparkle.xpm",
			&vars->tile_size, &vars->tile_size);
	return (!vars->hole || !vars->map_tile || !vars->earth || !vars->stars
		|| !vars->sun || !vars->spiral);
}

int	initialize_mlx(t_setup *vars, t_GMap *game)
{
	vars->mlx = mlx_init();
	if (!vars->mlx)
	{
		ft_putstr_fd("Error\nFailed to initialize MiniLibX\n", 2);
		return (1);
	}
	vars->win = mlx_new_window(vars->mlx, game->columns * 37, game->rows * 37,
			"So Long");
	if (!vars->win)
	{
		ft_putstr_fd("Error\nFailed to create window\n", 2);
		return (1);
	}
	if (allocate_map_memory(vars, game))
	{
		ft_putstr_fd("Error\nMemory allocation failed\n", 2);
		return (1);
	}
	setup_game_parameters(vars, game);
	if (load_map_elements(vars) || load_player_images(vars))
	{
		ft_putstr_fd("Error\nFailed to load game assets\n", 2);
		return (1);
	}
	return (ret_ini_mlx(vars, game));
}

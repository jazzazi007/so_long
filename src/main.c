/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaljazz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:28:56 by moaljazz          #+#    #+#             */
/*   Updated: 2025/04/04 15:28:57 by moaljazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_header.h"

static int	initialization(t_GMap *game, char *map_file)
{
	if (load_first_check_map(game, map_file) != 0)
	{
		ft_putstr_fd("Error\nMap Validation Failed\n", 2);
		free_map(game);
		return (1);
	}
	if (validate_map(game) != 0)
	{
		ft_putstr_fd("Error\nMap Validation Failed\n", 2);
		free_map(game);
		return (1);
	}
	ft_putstr_fd("Map is valid.\n", 1);
	return (0);
}

static int	mlx_free(t_setup *vars)
{
	handle_exit(vars, 1);
	return (0);
}

static int	start_game(t_setup *vars, t_GMap *game)
{
	if (initialize_mlx(vars, game) != 0)
	{
		ft_putstr_fd("Error\nMap Validation Failed\n", 2);
		free_map(game);
		return (1);
	}
	render_map(vars);
	mlx_loop_hook(vars->mlx, animate_rck, vars);
	mlx_hook(vars->win, 2, 1L << 0, combined_key_handler, vars);
	mlx_hook(vars->win, 17, 1L << 17, mlx_free, vars);
	mlx_loop(vars->mlx);
	return (0);
}

int	main(int ac, char **av)
{
	t_GMap	game;
	t_setup	vars;

	if (ac != 2)
	{
		ft_putstr_fd("Error\nAdd the map path ../maps/.. or any other files\n",
			2);
		return (1);
	}
	if (initialization(&game, av[1]) != 0)
		return (1);
	if (start_game(&vars, &game) != 0)
		return (1);
	handle_exit(&vars, 1);
	free_map(&game);
	return (0);
}

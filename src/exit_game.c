/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaljazz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:28:02 by moaljazz          #+#    #+#             */
/*   Updated: 2025/04/04 15:28:05 by moaljazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_header.h"

static void	free_map_resources(t_setup *vars)
{
	int	i;

	i = 0;
	while (i < vars->map_rows)
	{
		free(vars->map[i]);
		i++;
	}
	free(vars->map);
}

void	free_images(t_setup *vars)
{
	if (vars->hole)
		mlx_destroy_image(vars->mlx, vars->hole);
	if (vars->earth)
		mlx_destroy_image(vars->mlx, vars->earth);
	if (vars->spiral)
		mlx_destroy_image(vars->mlx, vars->spiral);
	if (vars->sun)
		mlx_destroy_image(vars->mlx, vars->sun);
	if (vars->stars)
		mlx_destroy_image(vars->mlx, vars->stars);
	if (vars->rck_up)
		mlx_destroy_image(vars->mlx, vars->rck_up);
	if (vars->rck_down)
		mlx_destroy_image(vars->mlx, vars->rck_down);
	if (vars->rck_left)
		mlx_destroy_image(vars->mlx, vars->rck_left);
	if (vars->rck_right)
	{
		mlx_destroy_image(vars->mlx, vars->rck_right);
		vars->rck_right = NULL;
	}
	if (vars->map_tile)
		mlx_destroy_image(vars->mlx, vars->map_tile);
}

static void	free_mlx_resources(t_setup *vars)
{
	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	if (vars->mlx)
		mlx_destroy_display(vars->mlx);
	free(vars->mlx);
}

static void	clean_exit(t_setup *vars, int ex)
{
	free_map_resources(vars);
	free_images(vars);
	free_mlx_resources(vars);
	if (ex == 1)
	{
		exit(0);
	}
}

int	handle_exit(t_setup *vars, int ex)
{
	clean_exit(vars, ex);
	return (0);
}

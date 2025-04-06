/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaljazz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:29:15 by moaljazz          #+#    #+#             */
/*   Updated: 2025/04/04 15:29:17 by moaljazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_header.h"

void	update_door_state(t_setup *vars)
{
	if (vars->collectibles_left > 1)
		vars->current_door = vars->earth;
	else if (vars->collectibles_left == 1)
		vars->current_door = vars->sun;
	else
		vars->current_door = vars->spiral;
}

void	handle_collectibles_and_win(t_setup *vars, int new_x, int new_y,
		char target_tile)
{
	if (target_tile == 'C')
	{
		vars->map[new_y][new_x] = '0';
		vars->collectibles_left--;
	}
	if (target_tile == 'E' && vars->collectibles_left == 0)
	{
		ft_putstr_fd("You won in", 1);
		write(1, &vars->move_count, 1);
		ft_putstr_fd("moves!\n", 1);
		handle_exit(vars);
	}
	update_door_state(vars);
}

int	animate_rck(t_setup *vars)
{
	int	row;
	int	col;

	row = 0;
	mlx_put_image_to_window(vars->mlx, vars->win, vars->rck, vars->player_x
		* vars->tile_size, vars->player_y * vars->tile_size);
	if (vars->map[vars->player_y][vars->player_x] == 'C')
		handle_collectibles_and_win(vars, vars->player_x, vars->player_y, 'C');
	update_door_state(vars);
	row = 0;
	while (row++ < vars->map_rows)
	{
		col = 0;
		while (col++ < vars->map_cols)
			if (vars->map[row - 1][col - 1] == 'E')
				mlx_put_image_to_window(vars->mlx, vars->win,
					vars->current_door, (col - 1) * vars->tile_size, (row - 1)
					* vars->tile_size);
	}
	return (0);
}

void	rck_start_position(t_setup *vars)
{
	int	row;
	int	col;

	row = 0;
	while (row < vars->map_rows)
	{
		col = 0;
		while (col < vars->map_cols)
		{
			if (vars->map[row][col] == 'P')
			{
				vars->player_x = col;
				vars->player_y = row;
				return ;
			}
			col++;
		}
		row++;
	}
	vars->player_x = -1;
	vars->player_x = -1;
}

void	move_rck(t_setup *vars, int dx, int dy)
{
	int		new_x;
	int		new_y;
	char	target_tile;

	new_x = vars->player_x + dx;
	new_y = vars->player_y + dy;
	if (new_x < 0 || new_x >= vars->map_cols || new_y < 0
		|| new_y >= vars->map_rows)
		return ;
	target_tile = vars->map[new_y][new_x];
	if (target_tile == '1' || (target_tile == 'E'
			&& vars->collectibles_left > 0))
		return ;
	mlx_put_image_to_window(vars->mlx, vars->win, vars->map_tile, vars->player_x
		* vars->tile_size, vars->player_y * vars->tile_size);
	vars->move_count++;
	if (vars->map[vars->player_y][vars->player_x] != 'P')
		mlx_put_image_to_window(vars->mlx, vars->win, vars->map_tile,
			vars->player_x * vars->tile_size, vars->player_y * vars->tile_size);
	vars->player_x = new_x;
	vars->player_y = new_y;
	handle_collectibles_and_win(vars, new_x, new_y, target_tile);
	ft_putstr_fd("Moves:", 1);
	write(1, &vars->move_count, 1);
	ft_putstr_fd("\n", 1);
}

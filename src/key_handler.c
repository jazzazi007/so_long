/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaljazz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:28:41 by moaljazz          #+#    #+#             */
/*   Updated: 2025/04/04 15:28:44 by moaljazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_header.h"

int	handle_key(int keycode, t_setup *vars)
{
	if (keycode == 119 || keycode == 65362)
	{
		vars->last_direction = 'u';
		vars->rck = vars->rck_up;
		move_rck(vars, 0, -1);
	}
	else if (keycode == 97 || keycode == 65361)
	{
		vars->last_direction = 'l';
		vars->rck = vars->rck_left;
		move_rck(vars, -1, 0);
	}
	else if (keycode == 115 || keycode == 65364)
	{
		vars->last_direction = 'd';
		vars->rck = vars->rck_down;
		move_rck(vars, 0, 1);
	}
	else if (keycode == 100 || keycode == 65363)
	{
		vars->last_direction = 'r';
		vars->rck = vars->rck_right;
		move_rck(vars, 1, 0);
	}
	return (0);
}

int	combined_key_handler(int keycode, t_setup *vars)
{
	if (keycode == 65307)
		return (handle_exit(vars));
	return (handle_key(keycode, vars));
}

void	handle_error(char *message, int fd)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(message, 2);
	if (fd >= 0)
		close(fd);
	exit(1);
}

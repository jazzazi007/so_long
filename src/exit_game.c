

#include "../include/so_long_header.h"

static void	free_map_resources(t_vars *vars)
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

static void	free_images(t_vars *vars)
{
	if (vars->wall)
		mlx_destroy_image(vars->mlx, vars->wall);
	if (vars->door_closed)
		mlx_destroy_image(vars->mlx, vars->door_closed);
	if (vars->door_open)
		mlx_destroy_image(vars->mlx, vars->door_open);
	if (vars->door_semi_open)
		mlx_destroy_image(vars->mlx, vars->door_semi_open);
	if (vars->skeleton)
		mlx_destroy_image(vars->mlx, vars->skeleton);
	if (vars->orc_up)
		mlx_destroy_image(vars->mlx, vars->orc_up);
	if (vars->orc_down)
		mlx_destroy_image(vars->mlx, vars->orc_down);
	if (vars->orc_left)
		mlx_destroy_image(vars->mlx, vars->orc_left);
	if (vars->orc_right)
		mlx_destroy_image(vars->mlx, vars->orc_right);
	if (vars->map_tile)
		mlx_destroy_image(vars->mlx, vars->map_tile);
}

static void	free_mlx_resources(t_vars *vars)
{
	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	if (vars->mlx)
		mlx_destroy_display(vars->mlx);
	free(vars->mlx);
}

static void	clean_exit(t_vars *vars)
{
	free_map_resources(vars);
	free_images(vars);
	free_mlx_resources(vars);
	exit(0);
}

int	handle_exit(t_vars *vars)
{
	clean_exit(vars);
	return (0);
}

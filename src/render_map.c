

#include "../include/so_long_header.h"

void	load_map_tile(t_vars *vars, int row, int col)
{
	if (vars->map[row][col] == '1')
		mlx_put_image_to_window(vars->mlx, vars->win, vars->wall,
			vars->tile_size * col, vars->tile_size * row);
	else if (vars->map[row][col] == '0')
		mlx_put_image_to_window(vars->mlx, vars->win, vars->map_tile,
			vars->tile_size * col, vars->tile_size * row);
	else if (vars->map[row][col] == 'E')
		mlx_put_image_to_window(vars->mlx, vars->win, vars->door_closed,
			vars->tile_size * col, vars->tile_size * row);
	else if (vars->map[row][col] == 'C')
		mlx_put_image_to_window(vars->mlx, vars->win, vars->skeleton,
			vars->tile_size * col, vars->tile_size * row);
	else if (vars->map[row][col] == 'P')
		mlx_put_image_to_window(vars->mlx, vars->win, vars->orc_down,
			vars->tile_size * col, vars->tile_size * row);
}

void	render_map(t_vars *vars)
{
	int	row;
	int	col;

	row = 0;
	while (row < vars->map_rows)
	{
		col = 0;
		while (col < vars->map_cols)
		{
			load_map_tile(vars, row, col);
			col++;
		}
		row++;
	}
}

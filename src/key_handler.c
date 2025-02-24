

#include "../include/so_long_header.h"

int	handle_key(int keycode, t_vars *vars)
{
	if (keycode == 119 || keycode == 65362)
	{
		vars->last_direction = 'u';
		vars->orc = vars->orc_up;
		move_orc(vars, 0, -1);
	}
	else if (keycode == 97 || keycode == 65361)
	{
		vars->last_direction = 'l';
		vars->orc = vars->orc_left;
		move_orc(vars, -1, 0);
	}
	else if (keycode == 115 || keycode == 65364)
	{
		vars->last_direction = 'd';
		vars->orc = vars->orc_down;
		move_orc(vars, 0, 1);
	}
	else if (keycode == 100 || keycode == 65363)
	{
		vars->last_direction = 'r';
		vars->orc = vars->orc_right;
		move_orc(vars, 1, 0);
	}
	return (0);
}

int	combined_key_handler(int keycode, t_vars *vars)
{
	if (keycode == 65307)
		return (handle_exit(vars));
	return (handle_key(keycode, vars));
}

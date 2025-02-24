

#include "../include/so_long_header.h"

void	copy_map(t_vars *vars, t_GameMap *game)
{
	int	i;

	i = 0;
	vars->map = malloc(game->rows * sizeof(char *));
	if (!vars->map)
	{
		perror("Failed to allocate memory for vars->map");
		exit(1);
	}
	while (i < game->rows)
	{
		vars->map[i] = malloc(game->cols * sizeof(char));
		if (!vars->map[i])
		{
			perror("Failed to allocate memory for vars->map row");
			exit(1);
		}
		memcpy(vars->map[i], game->map[i], game->cols * sizeof(char));
		i++;
	}
}

void	initialize_all(t_vars *vars, t_GameMap *game)
{
	copy_map(vars, game);
	vars->tile_size = 37;
	vars->map_rows = game->rows;
	vars->map_cols = game->cols;
	vars->player_x = -1;
	vars->player_y = -1;
	orc_start_position(vars);
	vars->collectibles_left = game->collectables;
	printf("%d\n\n\n\n\n",vars->collectibles_left);
	vars->move_count = 0;
	vars->last_direction = 'd';
}

void	initialize_images(t_vars *vars)
{
	vars->wall = mlx_xpm_file_to_image(vars->mlx,
			"./pics/w/wall.xpm", &vars->tile_size, &vars->tile_size);
	vars->map_tile = mlx_xpm_file_to_image(vars->mlx,
			"./pics/m/map.xpm", &vars->tile_size, &vars->tile_size);
	vars->door_closed = mlx_xpm_file_to_image(vars->mlx,
			"./pics/e/c_d.xpm", &vars->tile_size, &vars->tile_size);
	vars->door_semi_open = mlx_xpm_file_to_image(vars->mlx,
			"./pics/e/s_o.xpm", &vars->tile_size, &vars->tile_size);
	vars->door_open = mlx_xpm_file_to_image(vars->mlx,
			"./pics/e/o_d.xpm", &vars->tile_size, &vars->tile_size);
	vars->orc_up = mlx_xpm_file_to_image(vars->mlx,
			"./pics/s/u_1.xpm", &vars->tile_size, &vars->tile_size);
	vars->orc_down = mlx_xpm_file_to_image(vars->mlx,
			"./pics/s/d_1.xpm", &vars->tile_size, &vars->tile_size);
	vars->orc_left = mlx_xpm_file_to_image(vars->mlx,
			"./pics/s/l_1.xpm", &vars->tile_size, &vars->tile_size);
	vars->orc_right = mlx_xpm_file_to_image(vars->mlx,
			"./pics/s/r_1.xpm", &vars->tile_size, &vars->tile_size);
	vars->skeleton = mlx_xpm_file_to_image(vars->mlx,
			"./pics/c/skel_1.xpm", &vars->tile_size, &vars->tile_size);
}

int	initialize_mlx(t_vars *vars, t_GameMap *game)
{
	vars->mlx = mlx_init();
	if (!vars->mlx)
	{
		perror("Failed to initialize MiniLibX");
		return (1);
	}
	vars->win = mlx_new_window(vars->mlx,
			game->cols * 37, game->rows * 37, "My Game");
	if (!vars->win)
	{
		perror("Failed to create window");
		return (1);
	}
	initialize_all(vars, game);
	initialize_images(vars);
	if (!vars->wall || !vars->map_tile || !vars->door_closed || !vars->skeleton
		|| !vars->door_semi_open || !vars->door_open ||!vars->orc_up
		|| !vars->orc_down || !vars->orc_left || !vars->orc_right)
	{
		perror("Failed to load images");
		return (1);
	}
	vars->orc = vars->orc_down;
	free_map(game);
	return (0);
}

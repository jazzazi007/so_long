

#include "../include/so_long_header.h"

static int	initialize_game(t_GameMap *game, char *map_file)
{
	if (load_first_check_map(game, map_file) != 0)
	{
		perror("Map Validation Failed");
		free_map(game);
		return (1);
	}
	if (validate_map(game) != 0)
	{
		perror("Map Validation Failed");
		free_map(game);
		return (1);
	}
	printf("Map is valid.\n");
	return (0);
}

static int	start_game(t_vars *vars, t_GameMap *game)
{
	if (initialize_mlx(vars, game) != 0)
	{
		perror("Map Validation Failed");
		free_map(game);
		return (1);
	}
	render_map(vars);
	mlx_loop_hook(vars->mlx, animate_orc, vars);
	mlx_hook(vars->win, 2, 1L << 0, combined_key_handler, vars);
	mlx_hook(vars->win, 17, 1L << 17, handle_exit, vars);
	mlx_loop(vars->mlx);
	return (0);
}

int	main(int argc, char **argv)
{
	t_GameMap	game;
	t_vars		vars;

	if (argc != 2)
	{
		perror("PLEASE ADD THE MAP NAME ONLY :(");
		return (1);
	}
	if (initialize_game(&game, argv[1]) != 0)
	{
		return (1);
	}
	if (start_game(&vars, &game) != 0)
	{
		return (1);
	}
	handle_exit(&vars);
	free_map(&game);
	return (0);
}

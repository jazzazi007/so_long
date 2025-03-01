#include "../include/so_long_header.h"

static int allocate_map_memory(t_setup *vars, t_GMap *game)
{
    int i;

    vars->map = malloc(game->rows * sizeof(char *));
    if (!vars->map)
        return (1);

    for (i = 0; i < game->rows; i++)
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
    }
    return (0);
}

static void setup_game_parameters(t_setup *vars, t_GMap *game)
{
    vars->tile_size = 37;
    vars->map_rows = game->rows;
    vars->map_cols = game->columns;
    vars->player_x = -1;
    vars->player_y = -1;
    vars->collectibles_left = game->collectable;
    vars->move_count = 0;
    vars->last_direction = 'd';
    orc_start_position(vars);
}

static int load_player_images(t_setup *vars)
{
    vars->orc_up = mlx_xpm_file_to_image(vars->mlx,
            "./pics/s/u_1.xpm", &vars->tile_size, &vars->tile_size);
    vars->orc_down = mlx_xpm_file_to_image(vars->mlx,
            "./pics/s/d_1.xpm", &vars->tile_size, &vars->tile_size);
    vars->orc_left = mlx_xpm_file_to_image(vars->mlx,
            "./pics/s/l_1.xpm", &vars->tile_size, &vars->tile_size);
    vars->orc_right = mlx_xpm_file_to_image(vars->mlx,
            "./pics/s/r_1.xpm", &vars->tile_size, &vars->tile_size);

    return (!vars->orc_up || !vars->orc_down || 
            !vars->orc_left || !vars->orc_right);
}

static int load_map_elements(t_setup *vars)
{
    vars->wall = mlx_xpm_file_to_image(vars->mlx,
            "./pics/w/wall.xpm", &vars->tile_size, &vars->tile_size);
    vars->map_tile = mlx_xpm_file_to_image(vars->mlx,
            "./pics/m/map.xpm", &vars->tile_size, &vars->tile_size);
    vars->skeleton = mlx_xpm_file_to_image(vars->mlx,
            "./pics/c/skel_1.xpm", &vars->tile_size, &vars->tile_size);
    vars->door_closed = mlx_xpm_file_to_image(vars->mlx,
            "./pics/e/c_d.xpm", &vars->tile_size, &vars->tile_size);
    vars->door_semi_open = mlx_xpm_file_to_image(vars->mlx,
            "./pics/e/s_o.xpm", &vars->tile_size, &vars->tile_size);
    vars->door_open = mlx_xpm_file_to_image(vars->mlx,
            "./pics/e/o_d.xpm", &vars->tile_size, &vars->tile_size);

    return (!vars->wall || !vars->map_tile || !vars->door_closed || 
            !vars->skeleton || !vars->door_semi_open || !vars->door_open);
}

int initialize_mlx(t_setup *vars, t_GMap *game)
{
    vars->mlx = mlx_init();
    if (!vars->mlx)
    {
        ft_putstr_fd("Error\nFailed to initialize MiniLibX\n", 2);
        return (1);
    }

    vars->win = mlx_new_window(vars->mlx,
            game->columns * 37, game->rows * 37, "So Long");
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

    vars->orc = vars->orc_down;
    free_map(game);
    return (0);
}

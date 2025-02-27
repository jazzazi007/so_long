

#ifndef SO_LONG_HEADER_H
# define SO_LONG_HEADER_H

# include <stdarg.h>
# include <unistd.h>
# include <stdint.h>
# include <stdio.h>
# include <limits.h>
# include "../get_next_line_42/get_next_line.h"
# include "../minilibx-linux/mlx.h"
# include <string.h>

typedef struct s_GameMap
{
	char	**map;
	int		rows;
	int		cols;
	int		start_x;
	int		start_y;
	int		collectables;
	int		start;
	int		end;
	int		exit_x;
	int		exit_y;
}	t_GameMap;

typedef struct s_vars
{
	void	*mlx;
	void	*win;
	void	*wall;
	void	*orc;
	void	*orc_up;
	void	*orc_down;
	void	*orc_left;
	void	*orc_right;
	void	*skeleton;
	void	*door_closed;
	void	*door_semi_open;
	void	*door_open;
	void	*current_door;
	void	*map_tile;
	int		tile_size;
	char	**map;
	int		map_rows;
	int		map_cols;
	int		player_x;
	int		player_y;
	int		move_count;
	int		collectibles_left;
	char	last_direction;
}	t_vars;

int		validate_char(char c, t_GameMap *game, int i, int j);
int		map_components_check(t_GameMap *game);
int		shape_checker(t_GameMap *game);
int		mid_rows_boarder_check(t_GameMap *game);
int		top_bottom_rows_boarder_check(t_GameMap *game);
int		validate_map(t_GameMap *game);
int		get_x_y(t_GameMap *game, int fd);
int		get_map(t_GameMap *game, int fd);
int		handle_exit(t_vars *vars);
int		combined_key_handler(int keycode, t_vars *vars);
int		animate_orc(t_vars *vars);
int		initialize_mlx(t_vars *vars, t_GameMap *game);
int		load_first_check_map(t_GameMap *game, char *file_name);
void	load_map_tile(t_vars *vars, int row, int col);
void	render_map(t_vars *vars);
void	update_door_state(t_vars *vars);
void	free_map(t_GameMap *game);
void	move_orc(t_vars *vars, int dx, int dy);
void	orc_start_position(t_vars *vars);

#endif



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

typedef struct s_GMap
{
	char	**map;
	int		rows;
	int		columns;
	int		begin_x;
	int		begin_y;
	int		collectable;
	int		start;
	int		end;
	int		end_x;
	int		end_y;
}	t_GMap;

typedef struct s_setup
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
}	t_setup;

int		validate_char(char c, t_GMap *game, int i, int j);
int		map_components_check(t_GMap *game);
int		shape_checker(t_GMap *game);
int		mid_rows_boarder_check(t_GMap *game);
int		top_bottom_rows_boarder_check(t_GMap *game);
int		validate_map(t_GMap *game);
int		get_x_y(t_GMap *game, int fd);
int		get_map(t_GMap *game, int fd);
int		handle_exit(t_setup *vars);
int		combined_key_handler(int keycode, t_setup *vars);
int		animate_orc(t_setup *vars);
int		initialize_mlx(t_setup *vars, t_GMap *game);
int		load_first_check_map(t_GMap *game, char *file_name);
void	load_map_tile(t_setup *vars, int row, int col);
void	render_map(t_setup *vars);
void	update_door_state(t_setup *vars);
void	free_map(t_GMap *game);
void	move_orc(t_setup *vars, int dx, int dy);
void	orc_start_position(t_setup *vars);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_header.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaljazz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 15:27:05 by moaljazz          #+#    #+#             */
/*   Updated: 2025/04/04 15:27:11 by moaljazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_HEADER_H
# define SO_LONG_HEADER_H

# include "../42_libft/libft.h"
# include "../ft_printf/ft_printf.h"
# include "../get_next_line_42/get_next_line.h"
# include "../minilibx-linux/mlx.h"
# include <limits.h>
# include <stdarg.h>
# include <stdint.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>

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
}			t_GMap;

typedef struct s_setup
{
	void	*mlx;
	void	*win;
	void	*hole;
	void	*rck;
	void	*rck_up;
	void	*rck_down;
	void	*rck_left;
	void	*rck_right;
	void	*stars;
	void	*earth;
	void	*sun;
	void	*spiral;
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
}			t_setup;

int			validate_char(char c, t_GMap *game, int i, int j);
int			map_components_check(t_GMap *game);
int			shape_checker(t_GMap *game);
int			mid_rows_boarder_check(t_GMap *game);
int			top_bottom_rows_boarder_check(t_GMap *game);
int			validate_map(t_GMap *game);
int			get_x_y(t_GMap *game, int fd);
int			get_map(t_GMap *game, int fd);
int			handle_exit(t_setup *vars);
int			combined_key_handler(int keycode, t_setup *vars);
int			animate_rck(t_setup *vars);
int			initialize_mlx(t_setup *vars, t_GMap *game);
int			load_first_check_map(t_GMap *game, char *file_name);
void		load_map_tile(t_setup *vars, int row, int col);
void		render_map(t_setup *vars);
void		update_door_state(t_setup *vars);
void		free_map(t_GMap *game);
void		move_rck(t_setup *vars, int dx, int dy);
void		rck_start_position(t_setup *vars);
void		init_game_stats(t_GMap *game);
int			process_map_element(char element, t_GMap *game, int x, int y);
int			check_border_row(char *row);
int			verify_side_borders(t_GMap *game);
int			map_components_check(t_GMap *game);
void		handle_error(char *message, int fd);
int			is_all_collectibles_reachable(t_GMap *game);
void		*safe_calloc(size_t num, size_t size, void **ptr_array, int index);
void		flood_fill(t_GMap *game, int x, int y, char **visited);
int			ret_ini_mlx(t_setup *vars, t_GMap *game);

#endif

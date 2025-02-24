

#include "../include/so_long_header.h"

void	free_map(t_GameMap *game)
{
	int	i;

	if (!game || !game->map)
		return ;
	i = 0;
	while (i < game->rows)
	{
		free(game->map[i]);
		i++;
	}
	free(game->map);
	game->map = NULL;
	game->rows = 0;
	game->cols = 0;
	game->start_x = 0;
	game->start_y = 0;
	game->collectables = 0;
	game->start = 0;
	game->end = 0;
	game->exit_x = 0;
	game->exit_y = 0;
}

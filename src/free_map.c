

#include "../include/so_long_header.h"

void free_game(t_GMap *game)
{
	game->map = NULL;
	game->rows = 0;
	game->columns = 0;
	game->begin_x = 0;
	game->begin_y = 0;
	game->collectable = 0;
	game->start = 0;
	game->end = 0;
	game->end_x = 0;
	game->end_y = 0;
}
void	free_map(t_GMap *game)
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
	free_game(game);
}

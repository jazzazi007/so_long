#include "../include/so_long_header.h"

static void init_game_stats(t_GMap *game)
{
    game->start = 0;
    game->end = 0;
    game->collectable = 0;
    game->begin_x = -1;
    game->begin_y = -1;
    game->end_x = -1;
    game->end_y = -1;
}

static int process_map_element(char element, t_GMap *game, int x, int y)
{
    switch (element)
    {
        case 'E':
            game->end++;
            game->end_x = x;
            game->end_y = y;
            break;
        case 'P':
            game->start++;
            game->begin_x = x;
            game->begin_y = y;
            break;
        case 'C':
            game->collectable++;
            break;
        case '0':
        case '1':
            return (0);
        default:
            ft_putstr_fd("Error\nInvalid map character\n", 2);
            return (1);
    }
    return (0);
}

static int check_border_row(char *row, int is_first)
{
    int i;

    i = 0;
    while (row[i] && row[i] != '\n')
    {
        if (row[i] != '1')
        {
            ft_putstr_fd("Error\nInvalid border\n", 2);
            return (1);
        }
        i++;
    }
    return (0);
}

static int verify_side_borders(t_GMap *game)
{
    int i;
    int last_col;

    for (i = 1; i < game->rows - 1; i++)
    {
        last_col = game->columns - 1;
        if (game->map[i][last_col] == '\n')
            last_col--;
            
        if (game->map[i][0] != '1' || game->map[i][last_col] != '1')
        {
            ft_putstr_fd("Error\nInvalid side borders\n", 2);
            return (1);
        }
    }
    return (0);
}

int map_components_check(t_GMap *game)
{
    int i, j;

    init_game_stats(game);
    for (i = 0; i < game->rows; i++)
    {
        for (j = 0; game->map[i][j] && game->map[i][j] != '\n'; j++)
        {
            if (process_map_element(game->map[i][j], game, i, j))
                return (1);
        }
    }

    if (game->start != 1 || game->end != 1 || game->collectable < 1)
    {
        ft_putstr_fd("Error\nInvalid map components count\n", 2);
        return (1);
    }
    return (0);
}

int shape_checker(t_GMap *game)
{
    int first_row_len;

    first_row_len = 0;
    while (game->map[0][first_row_len] && game->map[0][first_row_len] != '\n')
        first_row_len++;

    if (first_row_len == game->rows)
    {
        ft_putstr_fd("Error\nMap is not rectangular\n", 2);
        return (1);
    }
    return (0);
}

int mid_rows_boarder_check(t_GMap *game)
{
    return verify_side_borders(game);
}

int top_bottom_rows_boarder_check(t_GMap *game)
{
    if (check_border_row(game->map[0], 1))
        return (1);
    if (check_border_row(game->map[game->rows - 1], 0))
        return (1);
    return (0);
}

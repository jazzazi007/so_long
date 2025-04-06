/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cont_map_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaljazz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 18:47:07 by moaljazz          #+#    #+#             */
/*   Updated: 2025/04/06 18:47:09 by moaljazz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long_header.h"

int shape_checker(t_GMap *game)
{
    int i;
    int first_row_len;
    int current_row_len;

    first_row_len = 0;
    while (game->map[0][first_row_len] && game->map[0][first_row_len] != '\n')
        first_row_len++;
    game->columns = first_row_len;
    i = 1;
    while (i < game->rows)
    {
        current_row_len = 0;
        while (game->map[i][current_row_len] && game->map[i][current_row_len] != '\n')
            current_row_len++;
        if (current_row_len != first_row_len)
        {
            ft_putstr_fd("Error\nRow differs from others", 2);
            return (1);
        }
        i++;
    }
    return (0);
}

int	mid_rows_boarder_check(t_GMap *game)
{
	return (verify_side_borders(game));
}

int	top_bottom_rows_boarder_check(t_GMap *game)
{
	if (check_border_row(game->map[0]))
		return (1);
	if (check_border_row(game->map[game->rows - 1]))
		return (1);
	return (0);
}

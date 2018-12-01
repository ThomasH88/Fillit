/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 22:09:52 by tholzheu          #+#    #+#             */
/*   Updated: 2018/10/20 16:25:29 by tholzheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

static void		unplace(t_llist_node *node, t_grid *grid)
{
	size_t		x;
	size_t		y;
	t_grid		*piece;

	piece = (t_grid *)node->data;
	y = 0;
	while (y < grid->size)
	{
		x = 0;
		while (x < grid->size)
		{
			if (grid->data[y][x] == 'A' + node->index)
				grid->data[y][x] = '.';
			x++;
		}
		y++;
	}
}

static int		placeable(t_llist_node *node, t_grid *grid,
							int ygrid, int xgrid)
{
	size_t		x;
	size_t		y;
	size_t		count;
	t_grid		*piece;

	piece = (t_grid *)node->data;
	y = 0;
	count = 0;
	while (ygrid + y < grid->size && y < piece->size)
	{
		x = 0;
		while (xgrid + x < grid->size && x < piece->size)
		{
			if (piece->data[y][x] == '#')
				if (grid->data[y + ygrid][x + xgrid] == '.' && ++count)
					grid->data[y + ygrid][x + xgrid] = 'A' + node->index;
			x++;
		}
		y++;
	}
	return (count == 4);
}

int				fillit(t_llist_node *pieces, t_grid *grid)
{
	size_t		x;
	size_t		y;

	if (pieces == NULL)
		return (1);
	y = 0;
	while (y < grid->size)
	{
		x = 0;
		while (x < grid->size)
		{
			if (placeable(pieces, grid, y, x))
				if (fillit(pieces->next, grid) == 1)
					return (1);
			unplace(pieces, grid);
			x++;
		}
		y++;
	}
	return (-1);
}

void			resolve(t_llist *pieces, t_grid *grid)
{
	size_t		grid_size;

	grid_size = 2;
	while ((grid_size * grid_size) < (pieces->len * 4))
		grid_size++;
	grid = grid_new(grid_size, 1);
	while (fillit(pieces->start, grid) == -1)
	{
		grid_free(grid);
		grid_size++;
		grid = grid_new(grid_size, 1);
	}
	write_grid(grid);
	grid_free(grid);
}

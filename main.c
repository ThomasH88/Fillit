/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 16:02:44 by tkobb             #+#    #+#             */
/*   Updated: 2018/10/22 19:36:04 by tholzheu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <fcntl.h>
#include <unistd.h>

int		usage(void)
{
	write(1, "usage: ./fillit <file>\n", 23);
	return (0);
}

int		error(void)
{
	write(1, "error\n", 6);
	return (0);
}

void	free_piece(void *v_piece)
{
	grid_free(((t_grid*)v_piece));
}

int		main(int ac, char **av)
{
	t_llist	*pieces;
	t_grid	*grid;
	int		fd;

	pieces = NULL;
	grid = NULL;
	if (ac != 2)
		return (usage());
	if ((fd = open(av[1], O_RDONLY)) == -1)
		return (error());
	if ((read_pieces(fd, &pieces)) == -1)
		return (error());
	resolve(pieces, grid);
	close(fd);
	llist_del(&pieces, free_piece);
	return (0);
}

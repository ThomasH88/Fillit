/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pieces.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/11 16:17:38 by tkobb             #+#    #+#             */
/*   Updated: 2018/10/22 19:26:13 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "get_next_line.h"

static int	read_piece(int fd, t_llist **list)
{
	size_t		i;
	size_t		len;
	char		*line;
	t_grid		*piece;

	i = 0;
	MALLOC_CHECK(piece = grid_new(4, 0));
	while (i < piece->size)
	{
		if (get_next_line(fd, &line) != 1)
			return (-1);
		len = ft_strlen(line);
		if (len != piece->size)
			return (-1);
		piece->data[i++] = line;
	}
	if (i != piece->size)
		return (-1);
	if (standardize_piece(piece) == -1)
		return (-1);
	llist_push(list, (void*)piece);
	return (1);
}

int			read_pieces(int fd, t_llist **pieces)
{
	int		status;
	char	*line;

	while ((status = read_piece(fd, pieces)) == 1)
	{
		if (get_next_line(fd, &line) < 1)
			break ;
		free(line);
	}
	if (status == -1)
		return (-1);
	if ((*pieces)->len <= 1 || (*pieces)->len >= 26)
		return (-1);
	return (1);
}

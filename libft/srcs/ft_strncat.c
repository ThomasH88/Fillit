/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strncat.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkobb <tkobb@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/14 12:08:25 by tkobb             #+#    #+#             */
/*   Updated: 2018/09/14 13:11:01 by tkobb            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *d, const char *s, size_t len)
{
	char	*t;

	t = d + ft_strlen(d);
	while (*s && len--)
		*t++ = *s++;
	*t = '\0';
	return ((char*)d);
}

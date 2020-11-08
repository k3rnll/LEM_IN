/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarkita <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 18:19:09 by tmarkita          #+#    #+#             */
/*   Updated: 2019/09/21 18:05:45 by tmarkita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	int		*ptr;
	size_t	i;

	if (!(ptr = (int *)malloc(size * sizeof(int))))
		return (NULL);
	i = 0;
	while (i < size)
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
}

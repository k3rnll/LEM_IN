/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarkita <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 14:02:55 by tmarkita          #+#    #+#             */
/*   Updated: 2019/09/20 14:03:18 by tmarkita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *hay, const char *needle)
{
	size_t	i;
	size_t	l;

	if (*needle == '\0')
		return ((char *)hay);
	i = 0;
	while (hay[i] != '\0')
	{
		l = 0;
		while (needle[l] == hay[i + l])
		{
			if (needle[l + 1] == '\0')
				return ((char *)hay + i);
			l++;
		}
		i++;
	}
	return (NULL);
}

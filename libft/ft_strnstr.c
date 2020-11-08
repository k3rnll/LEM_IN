/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarkita <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 14:01:35 by tmarkita          #+#    #+#             */
/*   Updated: 2019/09/20 17:39:46 by tmarkita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hay, const char *needle, size_t len)
{
	size_t	l;
	size_t	i;

	if (*needle == '\0')
		return ((char *)hay);
	i = 0;
	l = ft_strlen(needle);
	while (*hay && i < len)
	{
		if (i + l > len)
			return (NULL);
		if (*hay == *needle)
		{
			if (ft_strncmp(hay, needle, l) == 0)
				return ((char *)hay);
		}
		hay++;
		i++;
	}
	return (NULL);
}

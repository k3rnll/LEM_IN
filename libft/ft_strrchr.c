/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarkita <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 14:02:02 by tmarkita          #+#    #+#             */
/*   Updated: 2019/09/20 14:02:05 by tmarkita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	char	*tmp;

	tmp = 0;
	str = (char *)s;
	if ((char)c == '\0')
	{
		while (*str != '\0')
			str++;
		return (str);
	}
	else
	{
		while (*str != '\0')
		{
			if ((char)c == *str)
				tmp = str;
			str++;
		}
		if (tmp != 0)
			return (tmp);
	}
	return (NULL);
}

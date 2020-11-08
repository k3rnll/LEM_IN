/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarkita <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 13:30:59 by tmarkita          #+#    #+#             */
/*   Updated: 2019/09/20 13:31:03 by tmarkita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;

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
				return (str);
			str++;
		}
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarkita <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 19:49:47 by tmarkita          #+#    #+#             */
/*   Updated: 2019/09/20 19:55:41 by tmarkita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len;
	size_t	i;
	char	*str;

	if (s)
	{
		len = ft_strlen(s);
		if (!(str = ft_strnew(len)))
			return (NULL);
		i = 0;
		while (*s != '\0')
		{
			str[i] = f(i, *s);
			s++;
			i++;
		}
		return (str);
	}
	return (NULL);
}

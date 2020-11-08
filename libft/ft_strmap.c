/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarkita <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 19:23:16 by tmarkita          #+#    #+#             */
/*   Updated: 2019/09/20 19:48:52 by tmarkita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
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
			str[i] = f(*s);
			s++;
			i++;
		}
		return (str);
	}
	return (NULL);
}

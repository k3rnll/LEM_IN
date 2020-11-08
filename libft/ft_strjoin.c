/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarkita <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 20:30:41 by tmarkita          #+#    #+#             */
/*   Updated: 2019/09/20 21:03:56 by tmarkita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	size_t	lens1;
	char	*str;

	if (s1 && s2)
	{
		lens1 = ft_strlen(s1);
		len = lens1 + ft_strlen(s2);
		if (!(str = ft_strnew(len)))
			return (NULL);
		str = ft_strcpy(str, s1);
		str = str + lens1;
		str = ft_strcpy(str, s2);
		return (str - lens1);
	}
	return (NULL);
}

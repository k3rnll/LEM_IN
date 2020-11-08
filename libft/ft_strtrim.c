/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarkita <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 21:07:07 by tmarkita          #+#    #+#             */
/*   Updated: 2019/09/21 02:05:21 by tmarkita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_fisspace(const char *s)
{
	size_t	f;

	f = 0;
	while (s[f] != '\0')
	{
		if (s[f] != ' ' && s[f] != '\n' && s[f] != '\t')
			return (f);
		f++;
	}
	return (f);
}

static size_t	ft_bisspace(const char *s)
{
	size_t	b;
	size_t	len;

	len = ft_strlen(s) - 1;
	b = 0;
	while (len > 0)
	{
		if (s[len] != ' ' && s[len] != '\n' && s[len] != '\t')
			return (b);
		len--;
		b++;
	}
	return (b);
}

char			*ft_strtrim(char const *s)
{
	char	*str;
	size_t	f;
	size_t	b;
	size_t	len;

	if (s)
	{
		f = ft_fisspace(s);
		b = ft_bisspace(s);
		if (ft_strlen(s) == f)
			len = 0;
		else
			len = ft_strlen(s) - (f + b);
		if (!(str = ft_strnew(len)))
			return (NULL);
		str = ft_strsub(s, f, len);
		return (str);
	}
	return (NULL);
}

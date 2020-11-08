/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarkita <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 02:12:18 by tmarkita          #+#    #+#             */
/*   Updated: 2019/09/21 17:34:08 by tmarkita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strlenc(const char *s, size_t k, char c)
{
	size_t		i;
	size_t		count;

	count = 0;
	i = k;
	while (s[i] != c && s[i] != '\0')
	{
		i++;
		count++;
	}
	return (count);
}

static size_t	ft_wcount(const char *s, char c)
{
	size_t		i;
	size_t		word;

	i = 0;
	word = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			word++;
		i++;
	}
	return (word);
}

char			**ft_strsplit(char const *s, char c)
{
	size_t	i;
	size_t	len;
	size_t	p;
	char	**arr;

	i = 0;
	p = 0;
	if (s)
	{
		if (!(arr = (char **)malloc((ft_wcount(s, c) + 1) * sizeof(char *))))
			return (NULL);
		while (s[i])
		{
			if (s[i] != c)
			{
				len = ft_strlenc(s, i, c);
				arr[p++] = ft_strsub(s, i, len);
				i = i + len - 1;
			}
			i++;
		}
		arr[p] = 0;
		return (arr);
	}
	return (NULL);
}

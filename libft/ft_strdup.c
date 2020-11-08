/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarkita <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 13:58:43 by tmarkita          #+#    #+#             */
/*   Updated: 2019/09/20 13:59:22 by tmarkita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "errno.h"

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*cp;

	if (!(cp = (char *)malloc(ft_strlen(s1) + 1)))
	{
		errno = ENOMEM;
		return (NULL);
	}
	i = 0;
	while (s1[i] != '\0')
	{
		cp[i] = s1[i];
		i++;
	}
	cp[i] = '\0';
	return (cp);
}

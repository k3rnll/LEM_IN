/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarkita <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 18:27:12 by tmarkita          #+#    #+#             */
/*   Updated: 2019/09/21 20:12:19 by tmarkita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numlen(int n)
{
	int		len;

	len = 0;
	while (n / 10 != 0)
	{
		n = n / 10;
		len++;
	}
	len++;
	return (len);
}

char		*ft_itoa(int n)
{
	long int	tmp;
	int			len;
	char		*str;

	tmp = n;
	len = ft_numlen(n);
	if (n < 0)
	{
		tmp = tmp * -1;
		len++;
	}
	if (!(str = ft_strnew(len)))
		return (NULL);
	while (tmp / 10 != 0)
	{
		str[len - 1] = ((tmp % 10) + '0');
		tmp = tmp / 10;
		len--;
	}
	str[len - 1] = ((tmp % 10) + '0');
	if (n < 0)
		str[0] = '-';
	return (str);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarkita <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 13:26:00 by tmarkita          #+#    #+#             */
/*   Updated: 2020/11/06 18:07:48 by k3               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int				s;
	long long int	n;
	long long int	t;

	s = 1;
	n = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		s = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str != '\0' && ft_isdigit(*str))
	{
		t = n;
		n = (n * 10) + (*str - '0');
		if (n < t && s == 1)
			return (-1);
		if (n < t && s == -1)
			return (0);
		str++;
	}
	t = n * s;
	return (t);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarkita <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 20:21:48 by tmarkita          #+#    #+#             */
/*   Updated: 2019/09/21 20:48:14 by tmarkita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_prnt(long int tmp)
{
	if (tmp / 10)
		ft_prnt(tmp / 10);
	ft_putchar(tmp % 10 + '0');
}

void		ft_putnbr(int n)
{
	long int	tmp;

	tmp = n;
	if (n < 0)
	{
		ft_putchar('-');
		tmp = tmp * -1;
	}
	ft_prnt(tmp);
}

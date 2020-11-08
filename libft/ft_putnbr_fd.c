/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarkita <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 20:38:01 by tmarkita          #+#    #+#             */
/*   Updated: 2019/09/21 20:46:46 by tmarkita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ft_prnt(long int tmp, int fd)
{
	if (tmp / 10)
		ft_prnt((tmp / 10), fd);
	ft_putchar_fd((tmp % 10 + '0'), fd);
}

void			ft_putnbr_fd(int n, int fd)
{
	long int	tmp;

	tmp = n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		tmp = tmp * -1;
	}
	ft_prnt(tmp, fd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: k3 <k3@student.42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 13:55:10 by k3                #+#    #+#             */
/*   Updated: 2020/11/23 15:23:17 by k3               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"
#include "../libft/libft.h"

void	print_routes(t_lemin *lemin)
{
	int **arr;
	int	i;
	int	l;

	arr = lemin->routes;
	i = 0;
	write(1, " ======================\n ROUTES: \n [len], name1 name2 ...\n ======================\n", 82);
	while (arr[i] && i < lemin->num_rooms)
	{
		l = 0;
		write (1, "[", 1);
		ft_putnbr(route_len(lemin, arr[i]) + 1);
		write(1, "]  ", 3);
		while (l < lemin->num_rooms && arr[i][l] != 0)
		{
			write(1, lemin->rooms_names[arr[i][l]], ft_strlen(lemin->rooms_names[arr[i][l]]));
			write(1, " ", 1);
			l++;
		}
		write(1, "\n", 1);
		i++;
	}
}
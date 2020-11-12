/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flow.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarkita <tmarkita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 13:07:12 by k3                #+#    #+#             */
/*   Updated: 2020/11/12 16:56:34 by k3               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"
#include "../libft/libft.h"

int 	go_ant(t_lemin *lemin, int ant, int route, int step)
{
	int len;
	int i;

	i = 0;
	while (lemin->routes[route][i] != lemin->num_rooms - 1)
		i++;
	len = i;
	if (step <= len)
	{
		write(1, "L", 1);
		ft_putnbr(ant);
		write(1, "-", 1);
		ft_putstr(lemin->rooms_names[lemin->routes[route][step]]);
		write(1, " ", 1);
//		printf("L%d-%s ", ant, lemin->rooms_names[lemin->routes[route][step]]);
		return (1);
	}
	return (0);
}

int 	flow_cycle(t_lemin *lemin, int ant, int step)
{
	int 	i;

	i = 0;
	while (i < lemin->num_rooms)
	{
		if (go_ant(lemin, 1, 0, i))
			write(1, "\n", 1);
		i++;
	}
}

int 	flow_ants(t_lemin *lemin)
{
	flow_cycle(lemin, 1, 0);
}

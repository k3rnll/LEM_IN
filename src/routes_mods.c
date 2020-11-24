/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routes_mods.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarkita <tmarkita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 20:54:12 by tmarkita          #+#    #+#             */
/*   Updated: 2020/11/24 10:38:29 by k3               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"

void	clean_dead_link(t_lemin *lemin, int y)
{
	int	i;

	i = 0;
	while (i < lemin->num_rooms)
	{
		if (y != lemin->num_rooms - 1 && lemin->rooms_links[i][y])
			lemin->rooms_links[i][y] = -1;
		if (lemin->rooms_links[y][i])
			lemin->rooms_links[y][i] = -1;
		i++;
	}

}

void	clean_route_in_matrix(t_lemin *lemin, int *arr)
{
	int	i;

	i = 0;
	if (arr && arr[i])
	{
		while (arr[i] != lemin->num_rooms - 1 && i < lemin->num_rooms)
		{
			clean_dead_link(lemin, arr[i]);
			i++;
		}
		clean_dead_link(lemin, arr[i]);
	}
}

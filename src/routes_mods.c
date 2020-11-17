/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routes_mods.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarkita <tmarkita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 20:54:12 by tmarkita          #+#    #+#             */
/*   Updated: 2020/11/17 20:56:29 by k3               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"
#include "../libft/libft.h"

void	clean_dead_link(t_lemin *lemin, int y)
{
	int	i;

	i = 0;
	ft_bzero(lemin->rooms_links[y], lemin->num_rooms * sizeof(int));
	while (i < lemin->num_rooms)
	{
		lemin->rooms_links[i][y] = 0;
		i++;
	}
}

void	clean_route_in_matrix(t_lemin *lemin, int *arr)
{
	int	i;

	i = 0;
	if (arr[i])
	{
		while (arr[i] != lemin->num_rooms - 1 && i < lemin->num_rooms)
		{
			clean_dead_link(lemin, arr[i]);
			i++;
		}
	}
}

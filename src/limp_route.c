/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limp_route.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarkita <tmarkita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/24 13:08:15 by tmarkita          #+#    #+#             */
/*   Updated: 2020/11/24 13:10:29 by k3               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"
#include "../libft/libft.h"

void	del_limp_route(t_lemin *lemin)
{
	lemin->num_routes--;
	free(lemin->routes[lemin->num_routes]);
	lemin->routes[lemin->num_routes] = 0;
}

int		*limp_route(t_lemin *lemin, int len)
{
	int	*arr;
	int i;

	arr = ft_memalloc(lemin->num_rooms + 1);
	i = 0;
	while (i < len - 1)
	{
		arr[i] = 1;
		i++;
	}
	arr[i] = lemin->num_rooms - 1;
	lemin->routes[lemin->num_routes] = arr;
	lemin->num_routes++;
	return (arr);
}

int		is_good_route(t_lemin *lemin, int y)
{
	limp_route(lemin, lemin->rooms_links[y][lemin->num_rooms - 1]);
	if (lemin->num_routes > routes_to_use(lemin, lemin->num_ants))
	{
		del_limp_route(lemin);
		return (0);
	}
	del_limp_route(lemin);
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarkita <tmarkita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 17:35:29 by tmarkita          #+#    #+#             */
/*   Updated: 2020/11/25 15:35:06 by k3               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"
#include "../libft/libft.h"

int		route_len(t_lemin *lemin, int *arr)
{
	int	len;

	len = 0;
	while (arr[len] != lemin->num_rooms - 1 && len < lemin->num_rooms)
		len++;
	return (len);
}

int		get_in_point(t_lemin *lemin, int y, int x)
{
	while (x < lemin->num_rooms)
	{
		if (lemin->rooms_links[y][x] > lemin->rooms_links[x][y])
			return (x);
		x++;
	}
	return (0);
}

int		*check_route(t_lemin *lemin, int y)
{
	int	*arr;
	int	i;
	int	x;

	x = lemin->num_rooms - 1;
	if (!(arr = ft_memalloc(lemin->num_rooms + 1)))
		put_error("ERROR");
	i = 0;
	if (y == 0)
		lemin->rooms_links[y][lemin->num_rooms - 1] = 0;
	else
		i = lemin->rooms_links[y][lemin->num_rooms - 1] - 1;
	arr[i--] = x;
	while (i >= 0)
	{
		arr[i] = y;
		y = get_in_point(lemin, y, 0);
		if (y == 0 && i > 0)
			y = get_in_point(lemin, arr[i + 1], arr[i] + 1);
		else
			i--;
	}
	clean_route_in_matrix(lemin, arr);
	reset_bfs(lemin);
	return (arr);
}

void	find_routes(t_lemin *lemin)
{
	int	y;
	int len;

	if (!(lemin->routes = ft_memalloc(lemin->num_rooms * 2)))
		put_error("ERROR");
	lemin->min_route_len = lemin->num_rooms;
	y = 0;
	while (y < lemin->num_rooms)
	{
		if ((y == 0 && lemin->rooms_links[y][lemin->num_rooms - 1] > 0) ||
			lemin->rooms_links[y][lemin->num_rooms - 1] > 1)
		{
			if (!is_good_route(lemin, y))
				break ;
			if ((lemin->routes[lemin->num_routes] = check_route(lemin, y)))
			{
				len = route_len(lemin, lemin->routes[lemin->num_routes]);
				lemin->min_route_len = len < lemin->min_route_len ?
					len : lemin->min_route_len;
				lemin->num_routes += 1;
			}
			y = 0;
		}
		y++;
	}
}

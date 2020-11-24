/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarkita <tmarkita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 17:35:29 by tmarkita          #+#    #+#             */
/*   Updated: 2020/11/24 10:51:14 by k3               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"
#include "../libft/libft.h"

int		route_len(t_lemin *lemin, int *arr)
{
	int	len;

	len = 0;
	while (arr && arr[len] != lemin->num_rooms - 1 && len < lemin->num_rooms)
		len++;
	return (len);
}

int		get_in_point(t_lemin *lemin, int y, int x)
{
	while (x < lemin->num_rooms)
	{
		if (lemin->rooms_links[y][x] > 0 && lemin->rooms_links[x][y] > 0 &&
				lemin->rooms_links[y][x] > lemin->rooms_links[x][y])
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

void 	del_limp_route(t_lemin *lemin)
{
	lemin->num_routes--;
	free(lemin->routes[lemin->num_routes]);
	lemin->routes[lemin->num_routes] = 0;
}

int 	*limp_route(t_lemin *lemin, int len)
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

void	find_routes(t_lemin *lemin)
{
	int	*route;
	int	y;

	lemin->min_route_len = lemin->num_rooms;
	y = 0;
	while (y < lemin->num_rooms)
	{
		if ((y == 0 && lemin->rooms_links[y][lemin->num_rooms - 1] > 0) ||
		(lemin->rooms_links[y][lemin->num_rooms - 1] > 1 &&
		lemin->rooms_links[y][lemin->num_rooms - 1] < 110))
		{
			limp_route(lemin, lemin->rooms_links[y][lemin->num_rooms - 1]);
			if (lemin->num_routes > routes_to_use(lemin, lemin->num_ants))
			{
				del_limp_route(lemin);
				break;
			}
			del_limp_route(lemin);
			if ((route = check_route(lemin, y)))
			{
				lemin->min_route_len =
						route_len(lemin, route) < lemin->min_route_len ?
						route_len(lemin, route) : lemin->min_route_len;
				lemin->routes[lemin->num_routes] = route;
				lemin->num_routes += 1;
			}
			y = 0;
		}
		y++;
	}
}

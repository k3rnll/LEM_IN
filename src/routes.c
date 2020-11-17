/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarkita <tmarkita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 17:35:29 by tmarkita          #+#    #+#             */
/*   Updated: 2020/11/17 19:47:29 by tmarkita         ###   ########.fr       */
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
	if (!(arr = ft_memalloc(lemin->num_rooms * sizeof(int))))
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
	int	*route;
	int	y;

	if (!(lemin->routes = ft_memalloc(lemin->num_rooms * sizeof(int*))))
		put_error("ERROR");
	lemin->min_route_len = lemin->num_rooms;
	y = 0;
	while (y < lemin->num_rooms)
	{
		if ((y == 0 && lemin->rooms_links[y][lemin->num_rooms - 1] > 0) ||
		lemin->rooms_links[y][lemin->num_rooms - 1] > 1)
		{
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

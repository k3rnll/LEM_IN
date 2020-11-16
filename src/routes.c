/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarkita <tmarkita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 17:35:29 by k3                #+#    #+#             */
/*   Updated: 2020/11/16 12:57:46 by k3               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"
#include "../libft/libft.h"

#include <stdio.h>

int		route_len(t_lemin *lemin, int *arr)
{
	int	len;

	len = 0;
	while (arr[len] != lemin->num_rooms - 1 && len < lemin->num_rooms)
		len++;
	return (len);
}

void	print_route(t_lemin *lemin, int **arr)
{
	int	i;
	int	l;

	i = 0;
	while (arr[i] && i < lemin->num_rooms)
	{
		l = 0;
		printf("[%d] ", route_len(lemin, arr[i]));
		while (l < lemin->num_rooms && arr[i][l] != 0)
		{
			printf("%s ", lemin->rooms_names[arr[i][l]]);
			l++;
		}
		printf("\n");
		i++;
	}
	printf("\n");
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

int		get_in_point(t_lemin *lemin, int y)
{
	int	x;

	x = 0;
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
	arr = ft_memalloc(lemin->num_rooms * sizeof(int));
	i = lemin->rooms_links[y][lemin->num_rooms - 1] - 1;
	arr[i] = x;
	i--;
	while (i >= 0)
	{
		arr[i] = y;
		y = get_in_point(lemin, y);
		i--;
	}
	if (*arr)
	{
		clean_route_in_matrix(lemin, arr);
		return (arr);
	}
	free(arr);
	return (NULL);
}

void	find_min_bfs(t_lemin *lemin)
{
	int	y;
	int	bfs;

	lemin->min_route_len = lemin->num_rooms;
	y = 0;
	while (y < lemin->num_rooms)
	{
		bfs = lemin->rooms_links[y][lemin->num_rooms - 1];
		if (bfs < lemin->min_route_len && bfs > 0)
			lemin->min_route_len = bfs;
		y++;
	}
}

int		find_routes(t_lemin *lemin)
{
	int	*route;
	int	l;
	int	y;

	lemin->num_routes = 0;
	lemin->routes = ft_memalloc(lemin->num_rooms * sizeof(int*));
	y = 1;
	l = 0;
	while (y < lemin->num_rooms)
	{
		find_min_bfs(lemin);
		if (lemin->rooms_links[y][lemin->num_rooms - 1] == lemin->min_route_len)
		{
			if ((route = check_route(lemin, y)))
			{
				lemin->routes[l++] = route;
				lemin->num_routes += 1;
				y = 0;
			}
		}
		y++;
	}
	if (*(lemin->routes))
		print_route(lemin, lemin->routes);
}

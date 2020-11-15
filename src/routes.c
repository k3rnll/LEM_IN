/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarkita <tmarkita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 17:35:29 by k3                #+#    #+#             */
/*   Updated: 2020/11/15 12:30:22 by k3               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"
#include "../libft/libft.h"

#include <stdio.h>

int 	route_len(t_lemin *lemin, int *arr)
{
	int len;

	len = 0;
	while (arr[len] != lemin->num_rooms - 1 && len < lemin->num_rooms)
		len++;
	return (len);
}

void	print_one_route(t_lemin *lemin, int *arr)
{
	int l;

		l = 0;
		printf ("[%d] ", route_len(lemin, arr));
		while (l < lemin->num_rooms && arr[l] != 0)
		{
			printf("%s ", lemin->rooms_names[arr[l]]);
			l++;
			if (arr[l] == lemin->num_rooms - 1)
			{
				printf("%s ", lemin->rooms_names[arr[l]]);
				break;
			}
		}
		printf("\n");

}

void	print_route(t_lemin *lemin, int **arr)
{
	int i;
	int l;

	i = 0;
	while (arr[i] &&  i < lemin->num_rooms)
	{
		l = 0;
		printf ("[%d] ", route_len(lemin, arr[i]));
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

int 	find_double_in_route(t_lemin *lemin, int *arr, int x)
{
	int i;
	int l;

	i = 0;
	if (x == lemin->num_rooms - 1)
		return (0);
/*
	while (lemin->routes[i] &&  i < lemin->num_rooms)
	{
		l = 0;
		while (l < lemin->num_rooms && lemin->routes[i][l] != 0)
		{
			if (x == lemin->routes[i][l])
				return (1);
			l++;
		}
		i++;
	}
*/
	i = 0;
	while (arr[i] && i < lemin->num_rooms)
	{
		if (x == arr[i])
			return (1);
		i++;
	}
	return (0);
}

int 	in_line(t_lemin *lemin, int x, int y)
{

	if (x > 0 && lemin->rooms_links[y][x])
			return (1);
	else
		return (0);
}

void 	fill_route(int *arr, int pos, int x)
{
	int tmp;

	tmp = arr[x];
	while (x > pos)
	{
		arr[x] = tmp;
		x--;
	}
}

void 	clean_dead_link(t_lemin *lemin, int y)
{
	int 	i;

	i = 0;
	ft_bzero(lemin->rooms_links[y], lemin->num_rooms * sizeof(int));
	while (i < lemin->num_rooms)
	{
		lemin->rooms_links[i][y] = 0;
		i++;
	}
}

void 	clean_route_in_matrix(t_lemin *lemin, int *arr)
{
	int 	i;
	int 	y;

	i = 0;
	y = 0;
	if (arr[i])
	{
		while (arr[i] != lemin->num_rooms - 1 && i < lemin->num_rooms)
		{
			clean_dead_link(lemin, arr[i]);
//			lemin->rooms_links[y][arr[i]] = 0;
//			lemin->rooms_links[arr[i]][y] = 0;
//			y = arr[i];
			i++;
		}
	}
}

int 	get_in_point(t_lemin *lemin, int y)
{
	int x;

	x = 0;
	while (x < lemin->num_rooms)
	{
		if (lemin->rooms_links[y][x] > lemin->rooms_links[x][y])
			return (x);
		x++;
	}
	return (0);
}

int 	*check_route(t_lemin *lemin, int y)
{
	int *arr;
	int i;
	int x;

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
//	if (*arr && (arr = rebase_route(lemin, arr)))
		return(arr);
	free(arr);
	return (NULL);
}

int 	find_routes(t_lemin *lemin)
{
	int *route;
	int l;
	int y;

	lemin->num_routes = 0;
	lemin->routes = ft_memalloc(lemin->num_rooms * sizeof(int*));
	lemin->max_route_len = lemin->num_rooms;
	y = 1;
	l = 0;
	while (y < lemin->num_rooms)
	{
		if (lemin->rooms_links[y][lemin->num_rooms - 1])
		{
			if ((route = check_route(lemin, y)))
			{
				lemin->routes[l++] = route;
				lemin->num_routes += 1;
			}
		}
		y++;
	}
	if (*(lemin->routes))
		print_route(lemin, lemin->routes);
//	else
//		printf("\nno route found\n");
}

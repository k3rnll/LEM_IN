/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarkita <tmarkita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 17:35:29 by k3                #+#    #+#             */
/*   Updated: 2020/11/12 18:06:49 by k3               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"
#include "../libft/libft.h"

#include <stdio.h>

int 	route_len(int *arr)
{
	int len;

	len = 0;
	while (arr[len] != 0)
		len++;
	return (len);
}

void	print_route(t_lemin *lemin, int **arr)
{
	int i;
	int l;

	i = 0;
	while (arr[i] &&  i < lemin->num_rooms)
	{
		l = 0;
		printf ("[%d] ", route_len(arr[i]));
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
	while (lemin->routes[i] &&  i < lemin->num_rooms)
	{
		l = 0;
		while (l < lemin->num_rooms)
		{
			if (x == lemin->routes[i][l])
				return (1);
			l++;
		}
		i++;
	}
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

int 	*rebase_route(t_lemin *lemin, int *arr)
{
	int *route;
	int pos;
	int i;

	route = ft_memalloc(lemin->num_rooms * sizeof(int));
	ft_bzero(route, lemin->num_rooms * sizeof(int));
	pos = 0;
	while (pos < lemin->num_rooms && arr[pos] != 0)
	{
		i = pos;
		while (i < lemin->num_rooms && arr[i] != 0)
		{
			if (i > 0 && lemin->rooms_links[arr[pos]][arr[i]])
				fill_route(arr, pos, i);
			i++;
		}
		pos++;
	}
	i = 0;
	while (arr[i] != arr[i + 1])
		i++;
	ft_memcpy(route, arr, (i + 1) * sizeof(int));
	return (route);
}

int 	*check_route(t_lemin *lemin, int x)
{
	int *arr;
	int i;
	int y;

	y = 0;
	if (lemin->rooms_links[y][x] != 1)
		return (NULL);
	arr = ft_memalloc(lemin->num_rooms * sizeof(int));
	i = 0;
	while (x < lemin->num_rooms)
	{
		if (x != y && !find_double_in_route(lemin, arr, x) && lemin->rooms_links[y][x] == 1)
		{
			arr[i++] = x;
			y = x;
			if (x == lemin->num_rooms - 1)
				break;
			x = 1;
		}
		else if (x == lemin->num_rooms - 1)
		{
			i -= 1;
			x = arr[i];
			y = arr[i - 1];
			arr[i] = 0;
			x++;
		}
		else
			x++;
	}
//	if (*arr)
	if (*arr && (arr = rebase_route(lemin, arr)))
		return(arr);
	free(arr);
	return (NULL);
}

int 	find_routes(t_lemin *lemin)
{
	int *route;
	int l;
	int i;

	lemin->num_routes = 0;
	lemin->routes = ft_memalloc(lemin->num_rooms * sizeof(int*));
	i = 1;
	l = 0;
	while (i < lemin->num_rooms)
	{
		if ((route = check_route(lemin, i)))
		{
			lemin->routes[l++] = route;
			lemin->num_routes += 1;
		}
		i++;
	}
	if (*(lemin->routes))
		print_route(lemin, lemin->routes);
//	else
//		printf("\nno route found\n");
}

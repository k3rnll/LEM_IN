/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarkita <tmarkita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 17:35:29 by k3                #+#    #+#             */
/*   Updated: 2020/11/11 20:24:03 by k3               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"
#include "../libft/libft.h"

#include <stdio.h>

void	print_route(t_lemin *lemin, int **arr)
{
	int i;
	int l;

	i = 0;
	printf("\n");
	while (arr[i] &&  i < lemin->num_rooms)
	{
		l = 0;
		while (l < lemin->num_rooms)
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
	int 	i;

	i = 0;
	while (i < lemin->num_rooms)
	{
		if (x == arr[i])
			return (1);
		i++;
	}
	return (0);
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
	if (i && lemin->rooms_names[arr[i - 1]] == lemin->end_room_name)
		return(arr);
	free(arr);
	return (NULL);
}

int 	find_routes(t_lemin *lemin)
{
	int **routes_arr;
	int *route;
	int l;
	int i;

	routes_arr = ft_memalloc(lemin->num_rooms * sizeof(int*));
	i = 1;
	l = 0;
	while (i < lemin->num_rooms)
	{
		if ((route = check_route(lemin, i)))
			routes_arr[l++] = route;
		i++;
	}
	if (*routes_arr)
		print_route(lemin, routes_arr);
	else
		printf("\nno route found\n");
}

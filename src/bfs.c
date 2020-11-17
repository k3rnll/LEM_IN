/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarkita <tmarkita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 16:49:00 by k3                #+#    #+#             */
/*   Updated: 2020/11/17 12:46:53 by k3               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"
#include "../libft/libft.h"

void	reset_bfs(t_lemin *lemin)
{
	int x;
	int y;

	y = 0;
	while (y < lemin->num_rooms)
	{
		x = 0;
		while (x < lemin->num_rooms)
		{
			if (lemin->rooms_links[y][x])
				lemin->rooms_links[y][x] = 1;
			x++;
		}
		y++;
	}
	bfs(lemin);
}

void	shift_ocrd(t_lemin *lemin, int *ocrd)
{
	int		i;

	i = 0;
	while (i < 2 * lemin->num_rooms)
	{
		ocrd[i] = ocrd[i + 1];
		i++;
	}
}

int		ocrd_add(t_lemin *lemin, int *ocrd, int y, int step)
{
	int		x;
	int		len;

	x = 0;
	len = 0;
	while (*ocrd != 0)
		ocrd++;
	while (x < lemin->num_rooms)
	{
		if (lemin->rooms_links[y][x] == 1)
		{
			lemin->rooms_links[y][x] = step;
			if (x > 0 && x < lemin->num_rooms - 1)
			{
				*ocrd = x;
				ocrd++;
				len++;
			}
			if (x == lemin->num_rooms - 1)
				return (-1);
		}
		x++;
	}
	return (len);
}

void	bfs(t_lemin *lemin)
{
	int 	*ocrd;
	int		len;
	int 	cur;
	int 	step;
	int 	tmp;

	ocrd = ft_memalloc((2 * lemin->num_rooms) * sizeof(int));
	step = 1;
	len = ocrd_add(lemin, ocrd, 0, step);
	step++;
	cur = 0;
	while (*ocrd)
	{
		if (*ocrd != lemin->num_rooms - 1)
		{
			tmp = ocrd_add(lemin, ocrd, *ocrd, step);
			if (tmp < 0)
			{
				break;
			}
			cur += tmp;
		}
		shift_ocrd(lemin, ocrd);
		len--;
		if (len == 0)
		{
			step++;
			len = cur;
			cur = 0;
		}
		if (len == 0)
		{
			break;
		}
	}
	free(ocrd);
}

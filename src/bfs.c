/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarkita <tmarkita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 16:49:00 by k3                #+#    #+#             */
/*   Updated: 2020/11/15 12:14:18 by k3               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"
#include "../libft/libft.h"
#include <stdio.h>

int 	path_len(t_lemin *lemin, int y, int x)
{
	int i;
	int len;
	int point;

	point = x;
	len = 0;
	while (point != lemin->num_rooms - 1)
	{
		i = 0;
		while (i < lemin->num_rooms)
		{
			if (lemin->rooms_links[point][i] < lemin->rooms_links[i][point])
			{
				len++;
				point = i;
				break ;
			}
			if (i == lemin->num_rooms - 1 && lemin->rooms_links[point][i])
				return (len);
			if (i == lemin->num_rooms - 1)
				return (0);
			i++;
		}
	}
	return (len);
}

int 	check_in_forks(t_lemin *lemin, int y)
{
	int x;
	int len;

	x = 0;
	if (y == 0)
		return (0);
	while (x < lemin->num_rooms)
	{
		if (lemin->rooms_links[y][x] < lemin->rooms_links[x][y])
		{
			len = path_len(lemin, y, x);
			if (len != 0)
			{
				lemin->rooms_links[x][y] = 0;
				lemin->rooms_links[y][x] = 0;
			}
		}
		x++;
	}
	return (1);
}

void 	del_output_forks(t_lemin *lemin)
{
	int y;
	int i;

	y = lemin->num_rooms - 1;
	while (y)
	{
		if (y == 1519 && lemin->rooms_total_links[y * 2 + 1] > 2)
		{
			printf("room index: %d in: %d out: %d\n", y, lemin->rooms_total_links[y * 2], lemin->rooms_total_links[y * 2 + 1]);
			i = 0;
			while (i < lemin->num_rooms)
			{
				if (lemin->rooms_links[y][i] < lemin->rooms_links[i][y])
				{
					ft_putnbr(i);
					write(1, " ", 1);
				}
				i++;
			}
			check_in_forks(lemin, y);
		}
		y--;
	}
}

int 	path_has_out_forks(t_lemin *lemin, int y)
{
	int x;

	x = 0;
	if (y == 0)
		return (0);
	while (x < lemin->num_rooms)
	{
		if (lemin->rooms_links[y][x] > lemin->rooms_links[x][y])
		{
			if (lemin->rooms_total_links[x * 2 + 1] > 1)
				return (1);
			else
				path_has_out_forks(lemin, x);
		}
		x++;
	}
	return(0);
}

int 	check_out_forks(t_lemin *lemin, int y)
{
	int x;

	x = 0;
	if (y == 0)
		return (0);
	while (x < lemin->num_rooms - 1)
	{
		if (lemin->rooms_links[y][x] > lemin->rooms_links[x][y])
		{
			if ((lemin->rooms_total_links[x * 2 + 1] > 1 &&
				lemin->rooms_total_links[y * 2] > 1) ||
				(path_has_out_forks(lemin, x) && lemin->rooms_total_links[y * 2] > 1))
			{
//				lemin->rooms_total_links[x * 2 + 1] -= 1;
				lemin->rooms_total_links[y * 2] -= 1;
				lemin->rooms_links[y][x] = 0;
				lemin->rooms_links[x][y] = 0;
			}
		}
		x++;
	}
	return (1);
}

void 	del_input_forks(t_lemin *lemin)
{
	int y;

	y = 0;
	while (y < lemin->num_rooms)
	{
		if (lemin->rooms_total_links[y * 2] > 1)
		{
			check_out_forks(lemin, y);
		}
		y++;
	}
}

void 	del_cross_lines(t_lemin *lemin, int x)
{
	int y;

	y = 0;
	lemin->rooms_total_links[x * 2] = 0;
	lemin->rooms_total_links[x * 2 + 1] = 0;
	ft_bzero(lemin->rooms_links[x], lemin->num_rooms * sizeof(int));
	while (y < lemin->num_rooms)
	{
		lemin->rooms_links[y][x] = 0;
		y++;
	}
}

void 	del_deadends(t_lemin *lemin)
{
	int 	x;
	int 	y;
	int 	in;
	int 	out;

	y = 1;

	while (y < lemin->num_rooms - 1)
	{
		x = 0;
		in = 0;
		out = 0;
		while (x < lemin->num_rooms - 1)
		{
			if (lemin->rooms_links[y][x] > lemin->rooms_links[x][y])
				in += 1;
			if (lemin->rooms_links[y][x] < lemin->rooms_links[x][y])
				out += 1;
			x++;
		}
		out = lemin->rooms_links[y][x] ? out + 1 : out;
		lemin->rooms_total_links[y * 2] = in;
		lemin->rooms_total_links[(y * 2) + 1] = out;
		(!in && out) || (in && !out) ? del_cross_lines(lemin, y) : 0;
		y++;
	}
}

void 	del_mirror(t_lemin *lemin)
{
	int 	x;
	int 	y;

	x = 1;
	y = lemin->num_rooms - 1;
	while (y)
	{
		while (x < y + 1)
		{
			if (lemin->rooms_links[y][x] == lemin->rooms_links[x][y])
			{
				lemin->rooms_links[y][x] = 0;
				lemin->rooms_links[x][y] = 0;
			}
			x++;
		}
		x = 1;
		y--;
	}
}

int 	shift_ocrd(t_lemin *lemin, int *ocrd)
{
	int 	i;

	i = 0;
	while (i < 2 * lemin->num_rooms)
	{
		ocrd[i] = ocrd[i + 1];
		i++;
	}
}

int 	ocrd_add(t_lemin *lemin, int *ocrd, int y, int step)
{
	int 	x;
	int 	len;

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
		}
		x++;
	}
	return (len);
}

int 	bfs(t_lemin *lemin)
{
	int 	*ocrd;
	int		len;
	int 	cur;
	int 	step;

	ocrd = ft_memalloc((2 * lemin->num_rooms) * sizeof(int));
	step = 1;
	len = ocrd_add(lemin, ocrd, 0, step);
	step++;
	cur = 0;
	while (*ocrd)
	{
		if (*ocrd != lemin->num_rooms - 1)
			cur += ocrd_add(lemin, ocrd, *ocrd, step);
		shift_ocrd(lemin, ocrd);
		len--;
		if (len == 0)
		{
			step++;
			len = cur;
			cur = 0;
		}
		if (len == 0)
			break;
	}
}

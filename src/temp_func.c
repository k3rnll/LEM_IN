
#include "../include/temp_func.h"
#include "../libft/libft.h"
#include <stdio.h>

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
/*
void	print_data(t_lemin *lemin)
{
	int			i;

	i = 0;
	while (i < lemin->num_rooms)
	{
		printf("%s\n", *(lemin->rooms_names + i));
		i++;
	}
}

void	print_matrix(t_lemin *lemin)
{
	int			x;
	int			y;

	y = 0;
	while (y < lemin->num_rooms)
	{
		x = 0;
		while (x < lemin->num_rooms)
		{
			printf("%d ", lemin->rooms_links[y][x]);
			x++;
		}
		printf("  %s", lemin->rooms_names[y]);
		y++;
		printf("\n");
	}
	printf("\n");
}

void	print_firstline(t_lemin *lemin, int y)
{
	int			i;

	i = 0;
	while (i < lemin->num_rooms)
	{
		if (lemin->rooms_links[y][i])
			printf("%d.%s ", i, lemin->rooms_names[i]);
		i++;
	}
	printf("\n");
}

void	print_endline(t_lemin *lemin)
{
	int			i;

	i = 0;
	while (i < lemin->num_rooms)
	{
		if (lemin->rooms_links[i][lemin->num_rooms - 1])
			printf("%s: ind_%d  bfs: %d\n", lemin->rooms_names[i],
				   i, lemin->rooms_links[i][lemin->num_rooms - 1]);
		i++;
	}
	printf("\n");
}

void	print_total_links(t_lemin *lemin)
{
	int			i;

	i = 0;
	while (i < lemin->num_rooms)
	{
		if (lemin->rooms_total_links[i * 2] > 1 ||
			lemin->rooms_total_links[i * 2 + 1] > 1)
			printf("room index: %d in: %d out: %d\n", i,
				   lemin->rooms_total_links[i * 2], lemin->rooms_total_links[i * 2 + 1]);
		i++;
	}
}

void	print_one_route(t_lemin *lemin, int *arr)
{
	int l;

	l = 0;
	printf ("[%d] ", route_len(lemin, arr) + 1);
	while (l <= route_len(lemin, arr))
	{
		printf("%s ", lemin->rooms_names[arr[l]]);
		l++;
	}

	printf("\n");
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
		if (bfs < lemin->min_route_len && bfs > 1)
			lemin->min_route_len = bfs;
		y++;
	}
}

void	del_deadends(t_lemin *lemin)
{
	int		x;
	int		y;
	int		in;
	int		out;

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

void	del_mirror(t_lemin *lemin)
{
	int		x;
	int		y;

	x = 1;
	y = lemin->num_rooms - 1;
	while (y)
	{
		while (x < y + 1)
		{
			if (lemin->rooms_links[y][x] > 1 &&
				lemin->rooms_links[y][x] == lemin->rooms_links[x][y])
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

void	del_input_forks(t_lemin *lemin)
{
	int		y;

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

int		check_out_forks(t_lemin *lemin, int y)
{
	int		x;

	x = 0;
	if (y == 0)
		return (0);
	while (x < lemin->num_rooms - 1)
	{
		if (lemin->rooms_links[y][x] > lemin->rooms_links[x][y])
		{
			if ((lemin->rooms_total_links[x * 2 + 1] > 1 &&
				 lemin->rooms_total_links[y * 2] > 1) ||
				(path_has_out_forks(lemin, x) &&
				 lemin->rooms_total_links[y * 2] > 1))
			{
				lemin->rooms_total_links[y * 2] -= 1;
				lemin->rooms_links[y][x] = 0;
				lemin->rooms_links[x][y] = 0;
			}
		}
		x++;
	}
	return (1);
}

void	del_cross_lines(t_lemin *lemin, int x)
{
	int		y;

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

int		path_has_out_forks(t_lemin *lemin, int y)
{
	int		x;

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
	return (0);
}
*/
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarkita <tmarkita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 15:02:53 by tmarkita          #+#    #+#             */
/*   Updated: 2020/11/17 20:24:44 by k3               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"
#include "../libft/libft.h"

int		get_room_index(t_lemin *lemin, int l)
{
	int	i;

	i = 0;
	while (i < lemin->num_rooms)
	{
		if (ft_strequ(lemin->links_names[l], lemin->rooms_names[i]))
			return (i);
		i++;
	}
	put_error("ERROR");
	return (-1);
}

void	fill_links(t_lemin *lemin)
{
	int	i;
	int	x;
	int	y;

	i = 0;
	while (i < lemin->num_links)
	{
		x = get_room_index(lemin, (i + 1) * 2 - 2);
		y = get_room_index(lemin, (i + 1) * 2 - 1);
		lemin->rooms_links[x][y] = 1;
		lemin->rooms_links[y][x] = 1;
		i++;
	}
}

int		**new_links_massive(t_lemin *lemin)
{
	int **matrix;
	int i;

	matrix = ft_memalloc(lemin->num_rooms * sizeof(int**));
	i = 0;
	while (i < lemin->num_rooms)
	{
		matrix[i] = ft_memalloc(lemin->num_rooms * sizeof(int));
		i++;
	}
	return (matrix);
}

void	rebase_rooms_names(t_lemin *lemin)
{
	char	*tmp;
	int		i;

	i = 0;
	while (i < lemin->num_rooms)
	{
		if (lemin->rooms_names[i] == lemin->start_room_name)
		{
			tmp = lemin->rooms_names[0];
			lemin->rooms_names[0] = lemin->start_room_name;
			lemin->rooms_names[i] = tmp;
		}
		i++;
	}
	i = 0;
	while (i < lemin->num_rooms)
	{
		if (lemin->rooms_names[i] == lemin->end_room_name)
		{
			tmp = lemin->rooms_names[lemin->num_rooms - 1];
			lemin->rooms_names[lemin->num_rooms - 1] = lemin->end_room_name;
			lemin->rooms_names[i] = tmp;
		}
		i++;
	}
}

void	rooms_to_massive(t_lemin *lemin)
{
	lemin->rooms_links = new_links_massive(lemin);
	rebase_rooms_names(lemin);
	fill_links(lemin);
}

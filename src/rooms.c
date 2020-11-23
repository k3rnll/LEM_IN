/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rooms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarkita <tmarkita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 21:04:16 by tmarkita          #+#    #+#             */
/*   Updated: 2020/11/17 21:47:04 by k3               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"
#include "../libft/libft.h"

void	add_ants_number(t_lemin *lemin, char **arr, int i)
{
	if (arr[1] || lemin->ants_flag == 1 ||
		(i > 0 && (ft_strequ(lemin->first_data[i - 1], "##start") ||
					ft_strequ(lemin->first_data[i - 1], "##end"))))
		put_error("ERROR");
	lemin->num_ants = smart_atoi(arr[0]);
	lemin->ants_flag = 1;
}

void	fill_start_end(t_lemin *lemin, char *name, int i)
{
	if (i > 0)
	{
		if (ft_strequ(lemin->first_data[i - 1], "##start"))
			lemin->start_room_name = name;
		if (ft_strequ(lemin->first_data[i - 1], "##end"))
			lemin->end_room_name = name;
	}
}

void 	check_room_duplicate(t_lemin *lemin, char *room)
{
	int i;

	i = 0;
	while (i < lemin->num_rooms)
	{
		if (ft_strequ(lemin->rooms_names[i], room))
			put_error("ERROR");
		i++;
	}
}

void	add_room_name(t_lemin *lemin, char **arr)
{
	int	*xy;

	if (!(xy = ft_memalloc(4)) || arr[3])
		put_error("ERROR");
	xy[0] = smart_atoi(arr[1]);
	xy[1] = smart_atoi(arr[2]);
	check_coords(lemin, xy);
	check_room_duplicate(lemin, arr[0]);
	lemin->rooms_names[lemin->num_rooms] = arr[0];
	lemin->rooms_coords[lemin->num_rooms] = xy;
	lemin->num_rooms += 1;
	free(arr[1]);
	free(arr[2]);
}

void	check_room_names(t_lemin *lemin)
{
	int		i;
	char	**arr;

	i = 0;
	while (i < lemin->data_len)
	{
		arr = ft_strsplit(*(lemin->first_data + i), ' ');
		if (!arr || !*arr)
			put_error("ERROR");
		if (*arr[0] != '#' && arr[1] && arr[2])
		{
			add_room_name(lemin, arr);
			fill_start_end(lemin, arr[0], i);
		}
		else if (ft_isnumber(arr[0]))
		{
			add_ants_number(lemin, arr, i);
			free_strsplit(arr);
		}
		else
			free_strsplit(arr);
		i++;
		free(arr);
	}
}

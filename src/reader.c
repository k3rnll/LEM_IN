/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarkita <tmarkita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 13:54:30 by k3                #+#    #+#             */
/*   Updated: 2020/11/17 14:37:00 by k3               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../include/lem_in.h"

int 	check_commands(t_lemin *lemin)
{
	int 	i;
	int 	start;
	int 	end;

	i = 0;
	start = 0;
	end = 0;
	while (i < lemin->data_len)
	{
		start = ft_strequ(*(lemin->first_data + i), "##start") ? start + 1 : start;
		end = ft_strequ(*(lemin->first_data + i), "##end") ? end + 1 : end;
		i++;
	}
	if (i > 0 && !ft_strncmp(*(lemin->first_data + i - 1), "##", 2))
		return (0);
	return (start == 1 && end == 1 ? 1 : 0);
}

int 	add_room_name(t_lemin *lemin, char **arr)
{
	int	*xy;

	if (!(xy = ft_memalloc(2 * sizeof(int*))))
		return (0);
	xy[0] = ft_atoi(arr[1]);
	xy[1] = ft_atoi(arr[2]);
	lemin->rooms_names[lemin->num_rooms] = arr[0];
	lemin->rooms_coords[lemin->num_rooms] = xy;
	lemin->num_rooms += 1;

	return (1);
}

void 	add_link_name(t_lemin *lemin, char **arr)
{
	lemin->num_links += 1;
	lemin->links_names[lemin->num_links * 2 - 2] = arr[0];
	lemin->links_names[lemin->num_links * 2 - 1] = arr[1];
}

int 	check_link_names(t_lemin *lemin)
{
	int		i;
	char 	**arr;

	i = 0;
	while (i < lemin->data_len)
	{
		arr = ft_strsplit(*(lemin->first_data + i), '-');
		if (!arr || !*arr)
			return (0);
		if (*arr[0] != '#' && arr[1] && *arr[1] != '#')
		{
			if (arr[2] ||
				(i > 1 && (ft_strequ(lemin->first_data[i - 1], "##start") ||
						ft_strequ(lemin->first_data[i - 1], "##end"))))
				return (0);
			add_link_name(lemin, arr);
		}
		i++;
	}
	return (1);
}

void 	fill_start_end(t_lemin *lemin, char *name, int i)
{
	if (i > 0)
	{
		if (ft_strequ(lemin->first_data[i - 1], "##start"))
			lemin->start_room_name = name;
		if (ft_strequ(lemin->first_data[i - 1], "##end"))
			lemin->end_room_name = name;
	}
}

int 	check_room_names(t_lemin *lemin)
{
	int		i;
	char 	**arr;

	i = 0;
	while (i < lemin->data_len)
	{
		arr = ft_strsplit(*(lemin->first_data + i), ' ');
		if (!arr || !*arr)
			return (0);
		if (*arr[0] != '#' && arr[1] && arr[2])
		{
			if (arr[3] || !(add_room_name(lemin, arr)))
			{
				free_strsplit(arr);
				return (0);
			}
			fill_start_end(lemin, arr[0], i);
		}
		else if (ft_isnumber(arr[0]))
		{
			if (lemin->ants_flag == 1 ||
				(i > 0 && (ft_strequ(lemin->first_data[i - 1], "##start") ||
				ft_strequ(lemin->first_data[i - 1], "##end"))))
			{
				free_strsplit(arr);
				return (0);
			}
			lemin->num_ants = smart_atoi(arr[0]);
			lemin->ants_flag = 1;
		}
		i++;
		free(arr);
	}
	return (1);
}

int 	parse_data(t_lemin *lemin)
{
	if (!(lemin->rooms_names = ft_memalloc(lemin->data_len * sizeof(char*))) ||
		!(lemin->rooms_coords = ft_memalloc(lemin->data_len * sizeof(int*))) ||
		!(lemin->links_names = ft_memalloc(lemin->data_len * sizeof(int*))))
		return (0);
	if (!check_commands(lemin) ||
		!check_room_names(lemin) ||
		!check_link_names(lemin))
		return (0);
	if (lemin->num_ants < 1 ||
		!lemin->num_rooms ||
		!lemin->num_links)
		return (0);
	return (1);
}

int 	read_data(t_lemin *lemin)
{
	char 	*line;
	int 	i;

	i = 0;
	while (get_next_line(0, &line))
	{
		if (i == lemin->data_len)
			lemin->first_data = realloc_data(lemin->first_data, &lemin->data_len);
		lemin->first_data[i] = line;
		i++;
	}
	lemin->data_len = i;
	return (1);
}
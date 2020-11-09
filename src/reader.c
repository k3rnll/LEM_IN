/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarkita <tmarkita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 13:54:30 by k3                #+#    #+#             */
/*   Updated: 2020/11/08 19:35:58 by k3               ###   ########.fr       */
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
	return (start == 1 && end == 1 ? 1 : 0);
}

int 	str_w_nums(char *str)
{
	while (*str)
	{
		if (ft_isdigit(*str))
			return (1);
		str++;
	}
	return (0);
}


int 	check_room_names(t_lemin *lemin)
{
	int		i;
	char 	**arr;

	i = 0;
	while (i < lemin->data_len)
	{
		arr = ft_strsplit(*(lemin->first_data + i), ' ');
		if (arr && *arr[0] != '#' && arr[1] && arr[2] && arr[3])
			return (0);
		i++;
	}
	return (1);
}

int 	parse_data(t_lemin *lemin)
{
	if (!check_commands(lemin) || !check_room_names(lemin))
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
	return (1);
}
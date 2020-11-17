/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarkita <tmarkita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 13:54:30 by tmarkita          #+#    #+#             */
/*   Updated: 2020/11/17 22:23:16 by k3               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../include/lem_in.h"

void 	check_start_end(t_lemin *lemin)
{
	if (lemin->start_room_name == NULL ||
		lemin->end_room_name == NULL)
		put_error("ERROR");
}

void	check_commands(t_lemin *lemin)
{
	int	i;
	int	start;
	int	end;

	i = 0;
	start = 0;
	end = 0;
	while (i < lemin->data_len)
	{
		start = ft_strequ(*(lemin->first_data + i), "##start") ?
				start + 1 : start;
		end = ft_strequ(*(lemin->first_data + i), "##end") ?
				end + 1 : end;
		i++;
	}
	if (i > 0 && !ft_strncmp(*(lemin->first_data + i - 1), "##", 2))
		put_error("ERROR");
	if (start != 1 || end != 1)
		put_error("ERROR");
}

void	check_coords(t_lemin *lemin, int *xy)
{
	int i;

	i = 0;
	while (i < lemin->num_rooms)
	{
		if (lemin->rooms_coords[i][0] == xy[0] &&
			lemin->rooms_coords[i][1] == xy[1])
			put_error("ERROR");
		i++;
	}
}

void	parse_data(t_lemin *lemin)
{
	if (!(lemin->rooms_names = ft_memalloc(lemin->data_len * sizeof(char*))) ||
		!(lemin->rooms_coords = ft_memalloc(lemin->data_len * sizeof(int*))) ||
		!(lemin->links_names = ft_memalloc(lemin->data_len * sizeof(int*))))
		put_error("ERROR");
	lemin->start_room_name = NULL;
	lemin->end_room_name = NULL;
	check_commands(lemin);
	check_room_names(lemin);
	check_start_end(lemin);
	check_link_names(lemin);
	if (lemin->num_ants < 1 ||
		!lemin->num_rooms ||
		!lemin->num_links)
		put_error("ERROR");
}

int		read_data(t_lemin *lemin)
{
	char	*line;
	int		i;

	i = 0;
	while (get_next_line(0, &line))
	{
		if (i == lemin->data_len)
			lemin->first_data =
					realloc_data(lemin->first_data, &lemin->data_len);
		lemin->first_data[i] = line;
		i++;
	}
	lemin->data_len = i;
	return (1);
}

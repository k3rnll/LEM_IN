/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarkita <tmarkita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 13:54:30 by k3                #+#    #+#             */
/*   Updated: 2020/11/08 15:52:10 by k3               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../include/lem_in.h"

void 	free_first_data(char **old, int *data_len)
{
	int 	i;

	i = 0;
	while (i < *data_len)
	{
		free(*(old + i));
		i++;
	}
	free(old);
}

char 	**realloc_data(char **old, int *data_len)
{
	char 	**new;

	new = ft_memalloc((*data_len + BUFF) * 8);
	if (new)
	{
		ft_bzero(new, (*data_len + BUFF) * 8);
		ft_memcpy(new, old, *data_len * 8);
		free(old);
		*data_len += BUFF;
	}
	else
	{
		free_first_data(old, data_len);
		ft_putendl_fd("ERROR: no memory", 2);
		exit (1);
	}
	return (new);
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
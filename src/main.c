/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarkita <tmarkita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 13:44:20 by k3                #+#    #+#             */
/*   Updated: 2020/11/09 22:16:11 by k3               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../include/lem_in.h"

#include <stdio.h>

t_lemin *init_lemin(void)
{
	t_lemin		*lemin;

	lemin = ft_memalloc(sizeof(t_lemin));
	if (lemin)
	{
		if (!(lemin->first_data = ft_memalloc(BUFF * sizeof(char*))) ||
			!(lemin->rooms_names = ft_memalloc(BUFF * sizeof(char*))) ||
			!(lemin->rooms_coords = ft_memalloc(BUFF * sizeof(int*))) ||
			!(lemin->links_names = ft_memalloc(BUFF * sizeof(int*))))
		{
			free(lemin);
			return (NULL);
		}
		lemin->data_len = BUFF;
		lemin->num_ants = 0;
		lemin->num_rooms = 0;
		lemin->num_links = 0;
	}
	return (lemin);
}

void 	print_data(t_lemin *lemin)
{
	int i;

	i = 0;
	while (i < lemin->data_len)
	{
		printf("%s\n", *(lemin->first_data + i));
		i++;
	}
}

int		main(int ac, char **av)
{
	t_lemin		*lemin;

	lemin = init_lemin();
	read_data(lemin);
	if (!parse_data(lemin))
		ft_putendl_fd("not valid input", 2);
	else
		print_data(lemin);

	exit (0);
}

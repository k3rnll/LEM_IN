/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarkita <tmarkita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 13:44:20 by tmarkita          #+#    #+#             */
/*   Updated: 2020/11/23 13:29:02 by k3               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../include/lem_in.h"

void		put_error(char *str)
{
	ft_putendl_fd(str, 2);
	exit(1);
}

void		print_input_data(t_lemin *lemin)
{
	while (*(lemin->first_data))
	{
		write(1, *lemin->first_data, ft_strlen(*lemin->first_data));
		write(1, "\n", 1);
		(lemin->first_data)++;
	}
	write(1, "\n", 1);
}

t_lemin		*init_lemin(void)
{
	t_lemin		*lemin;

	lemin = ft_memalloc(sizeof(t_lemin));
	if (lemin)
	{
		if (!(lemin->first_data = ft_memalloc(BUFF * sizeof(char*))))
		{
			free(lemin);
			return (NULL);
		}
		lemin->data_len = BUFF;
		lemin->num_ants = 0;
		lemin->ants_flag = 0;
		lemin->num_rooms = 0;
		lemin->num_links = 0;
		lemin->num_routes = 0;
	}
	return (lemin);
}

int			main(int ac, char **av)
{
	t_lemin		*lemin;

	if (ac > 1 || !av)
		put_error("ERROR");
	lemin = init_lemin();
	read_data(lemin);
	parse_data(lemin);
	rooms_to_massive(lemin);
	bfs(lemin);
	find_routes(lemin);
	flow_ants(lemin);
	exit(0);
}

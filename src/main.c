/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarkita <tmarkita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 13:44:20 by tmarkita          #+#    #+#             */
/*   Updated: 2020/11/23 15:21:15 by k3               ###   ########.fr       */
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
		lemin->p_routes = 0;
		lemin->p_data = 1;

	}
	return (lemin);
}

void 		parse_flags(t_lemin *lemin, int ac, char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (av[i] && ft_strequ("-r", av[i]))
			lemin->p_routes = 1;
		else if (av[i] && ft_strequ("-d", av[i]))
			lemin->p_data = 0;
		else
			put_error(
				" ================================\n"
				" USAGE: ./lem-in < map\n\n FLAGS: -r show routes\n"
				"        -d do not show input data\n"
				" ================================");
		i++;
	}
}

int			main(int ac, char **av)
{
	t_lemin		*lemin;

	lemin = init_lemin();
	parse_flags(lemin, ac, av);
	read_data(lemin);
	parse_data(lemin);
	rooms_to_massive(lemin);
	bfs(lemin);
	find_routes(lemin);
	flow_ants(lemin);
	lemin->p_routes ? print_routes(lemin) : 0;
	exit(0);
}

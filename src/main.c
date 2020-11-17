/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarkita <tmarkita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 13:44:20 by k3                #+#    #+#             */
/*   Updated: 2020/11/17 12:46:53 by k3               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../include/lem_in.h"

void			put_error(char *str)
{
	ft_putendl(str);
	exit(1);
}

t_lemin			*init_lemin(void)
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
	}
	return (lemin);
}

int				main(int ac, char **av)
{
	t_lemin		*lemin;

	lemin = init_lemin();
	read_data(lemin);
	if (!parse_data(lemin))
		put_error("not valid input");
	rooms_to_massive(lemin);
	bfs(lemin);
	find_routes(lemin);
	if (lemin->num_routes > 0)
		flow_ants(lemin);
	else
		(put_error("ERROR\n"));
	exit (0);
}

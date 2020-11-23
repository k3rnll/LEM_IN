/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouise <clouise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 17:35:29 by clouise           #+#    #+#             */
/*   Updated: 2020/11/23 17:55:08 by k3               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"
#include "../libft/libft.h"

void	print_ant(t_lemin *lemin, t_ant *ant)
{
	if (ant->step != 0)
	{
		if (lemin->routes[ant->route_index][ant->curr_room] ==
			lemin->num_rooms - 1)
			ant->step = 0;
		write(1, "L", 1);
		ft_putnbr(ant->ant_num);
		write(1, "-", 1);
		write(1, lemin->rooms_names[lemin->routes
			[ant->route_index][ant->curr_room]], ft_strlen(lemin->rooms_names[lemin->routes
		[ant->route_index][ant->curr_room]]));
		write(1, " ", 1);
		ant->curr_room += 1;
	}
}

void	print_ants(t_lemin *lemin, t_ant *ant, int i)
{
	t_ant	*head;

	head = ant;
	while (i && head)
	{
		print_ant(lemin, head);
		head = head->next;
		i--;
	}
}

int		all_is_printed(t_ant **ant_groups, int total_use)
{
	int		i;

	i = 0;
	while (i < total_use)
	{
		if (ant_groups[i]->last->step)
			return (0);
		i++;
	}
	return (1);
}

void	print_ant_groups(t_lemin *lemin, t_ant **ant_groups, int total)
{
	int	i;
	int use;

	i = 0;
	while (!all_is_printed(ant_groups, total))
	{
		use = 0;
		while (use < total)
		{
			if (lemin->min_route_len == 0)
				i = lemin->num_ants;
			print_ants(lemin, ant_groups[use], i + 1);
			use++;
		}
		write(1, "\n", 1);
		i = i < lemin->num_ants ? i + 1 : i;
	}
}

void	flow_ants(t_lemin *lemin)
{
	t_ant	**ant_groups;
	int		total_use;
	int		ants;
	int		i;

	if (lemin->num_routes == 0)
		put_error("ERROR");
	lemin->p_data ? print_input_data(lemin) : 0;
	total_use = routes_to_use(lemin, lemin->num_ants);
	ant_groups = ft_memalloc((total_use + 1) * 2);
	ants = 0;
	i = 0;
	while (i < total_use)
	{
		ants++;
		ant_groups[i] = new_ant(ants, i);
		i++;
	}
	fill_ant_groups(lemin, ant_groups, ants);
	print_ant_groups(lemin, ant_groups, total_use);
	free_ants(ant_groups);
}

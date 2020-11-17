/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouise <clouise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 17:35:29 by k3                #+#    #+#             */
/*   Updated: 2020/11/17 20:49:28 by k3               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"
#include "../libft/libft.h"

t_ant	*new_ant(int num, int ind)
{
	t_ant	*ant;

	if (!(ant = ft_memalloc(sizeof(t_ant))))
		put_error("no mem for ant");
	ant->ant_num = num;
	ant->step = 1;
	ant->route_index = ind;
	ant->curr_room = 0;
	ant->next = NULL;
	ant->last = ant;
	return (ant);
}

void	add_ant(t_ant *ant, int num, int ind)
{
	t_ant	*head;

	head = ant;
	while (ant->next)
		ant = ant->next;
	ant->next = new_ant(num, ind);
	head->last = ant->next;
}

void	print_ant(t_lemin *lemin, t_ant *ant)
{
	if (ant->step != 0)
	{
		if (lemin->routes[ant->route_index][ant->curr_room] ==
			lemin->num_rooms - 1)
			ant->step = 0;
		ft_putchar(' ');
		ft_putchar('L');
		ft_putnbr(ant->ant_num);
		ft_putchar('-');
		ft_putstr(lemin->rooms_names[lemin->routes
			[ant->route_index][ant->curr_room]]);
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

void	free_ants(t_ant **ant_groups)
{
	t_ant	*arr;
	t_ant	*tmp;
	t_ant	**tmp2;

	tmp2 = ant_groups;
	while (*ant_groups)
	{
		arr = *ant_groups;
		while (arr && arr->next)
		{
			tmp = arr->next;
			free(arr);
			arr = tmp;
		}
		free(arr);
		ant_groups++;
	}
	free(tmp2);
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

void	fill_ant_groups(t_lemin *lemin, t_ant **ant_groups, int ants)
{
	int i;
	int use;

	while (ants < lemin->num_ants)
	{
		use = routes_to_use(lemin, lemin->num_ants - ants);
		i = 0;
		while (i < use)
		{
			ants++;
			add_ant(ant_groups[i], ants, i);
			i++;
		}
	}
}

void	flow_ants(t_lemin *lemin)
{
	t_ant	**ant_groups;
	int		use;
	int		total_use;
	int		ants;
	int		i;

	total_use = routes_to_use(lemin, lemin->num_ants);
	ant_groups = ft_memalloc(total_use * sizeof(int*));
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

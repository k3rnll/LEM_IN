/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ants.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarkita <tmarkita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 20:58:00 by tmarkita          #+#    #+#             */
/*   Updated: 2020/11/25 15:35:06 by k3               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"
#include "../libft/libft.h"

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

t_ant	*new_ant(int num, int ind)
{
	t_ant	*ant;

	if (!(ant = malloc(sizeof(t_ant))))
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

void	fill_ant_groups(t_lemin *lemin, t_ant **ant_groups, int ants)
{
	int i;
	int use;

	while (ants < lemin->num_ants)
	{
		use = routes_to_use(lemin, lemin->num_ants - ants);
		i = 0;
		while (i < use && ants < lemin->num_ants)
		{
			ants++;
			add_ant(ant_groups[i], ants, i);
			i++;
		}
	}
}

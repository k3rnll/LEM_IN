/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clouise <clouise@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 17:35:29 by k3                #+#    #+#             */
/*   Updated: 2020/11/16 10:52:03 by k3               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"
#include "../libft/libft.h"
#include <stdio.h>

t_ant *new_ant(int i)
{
    t_ant *ant;

    if (!(ant = (ft_memalloc(sizeof(t_ant)))))
        put_error("no mem for ant");
	ant->ant_num = i;
	ant->step = 1;
	ant->route_index = 0;
	ant->curr_room = 0;
	ant->next = NULL;
    return (ant);
}

void	add_ant(t_ant *ant)
{
	int	i;

	i = 2;
	while (ant->next)
	{
		ant = ant->next;
		i++;
	}
	ant->next = new_ant(i);
}


static int      intlen(int *arr)
{
    int i;

    i = 0;
    while(arr[i] != 0)
        i++;
    return(i);
}

void    print_ant(t_lemin *lemin, t_ant *ant)
{
	if (ant->step != 0 )
	{
		if (lemin->routes[ant->route_index][ant->curr_room] == lemin->num_rooms - 1)
			ant->step = 0;
		ft_putchar(' ');
		ft_putchar('L');
		ft_putnbr(ant->ant_num);
		ft_putchar('-');
		ft_putstr(lemin->rooms_names[lemin->routes[ant->route_index][ant->curr_room]]);
//		ft_putchar('-');
//		ft_putnbr(lemin->routes[ant->route_index][ant->curr_room]);
		ant->curr_room +=1;
	}
}
void 	print_ants(t_lemin *lemin, t_ant *ant, int i)
{
	t_ant 	*head;

	head = ant;
	while (i && head)
	{
		print_ant(lemin, head);
		head = head->next;
		i--;
	}
	write(1, "\n", 1);
}


void    flow_ants(t_lemin *lemin)
{
    t_ant	*ant;
    int 	i;
    int 	l;

    ant = new_ant(1);
    i = 0;
    while (i < lemin->num_ants)
	{
		add_ant(ant);
		i++;
	}
	i = 0;
    while (i < lemin->num_ants + intlen(lemin->routes[0]))
    {
    	print_ants(lemin, ant, i + 1);
		i++;
    }
}

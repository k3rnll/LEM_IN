/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarkita <tmarkita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 13:44:20 by k3                #+#    #+#             */
/*   Updated: 2020/11/12 16:56:04 by k3               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../include/lem_in.h"

void 	put_error(char *str)
{
	ft_putendl(str);
	exit(1);
}

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
		lemin->ants_flag = 0;
		lemin->num_rooms = 0;
		lemin->num_links = 0;
	}
	return (lemin);
}

/*
void 	print_data(t_lemin *lemin)
{
	int i;

	i = 0;
	while (i < lemin->num_rooms)
	{
		printf("%s\n", *(lemin->rooms_names + i));
		i++;
	}
}

void 	print_matrix(t_lemin *lemin)
{
	int x;
	int y;
	y = 0;
	while (y < lemin->num_rooms)
	{
		x = 0;
		while (x < lemin->num_rooms)
		{
			printf("%d ", lemin->rooms_links[y][x]);
			x++;
		}
		printf("  %s", lemin->rooms_names[y]);
		y++;
		printf("\n");
	}
}
*/
int		main(int ac, char **av)
{
	t_lemin		*lemin;

	lemin = init_lemin();
	read_data(lemin);

	if (!parse_data(lemin))
		put_error("not valid input");
//	else
//		print_data(lemin);
	rooms_to_massive(lemin);
//	print_matrix(lemin);
	find_routes(lemin);
//	flow_ants(lemin);

	exit (0);
}

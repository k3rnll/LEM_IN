/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarkita <tmarkita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 13:44:20 by tmarkita          #+#    #+#             */
/*   Updated: 2020/11/24 10:58:07 by k3               ###   ########.fr       */
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
	int i;

	i = 0;
	while (i < lemin->data_len)
	{
		write(1, lemin->first_data[i], ft_strlen(lemin->first_data[i]));
		write(1, "\n", 1);
		i++;
	}
	write(1, "\n", 1);
}

t_lemin		*init_lemin(void)
{
	t_lemin		*lemin;

	lemin = malloc(sizeof(t_lemin));
	if (lemin)
	{
		if (!(lemin->first_data = malloc(BUFF * sizeof(char*))))
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
	while (av[i] && ac)
	{
		if (av[i] && ft_strequ("-r", av[i]) && !lemin->p_routes)
			lemin->p_routes = 1;
		else if (av[i] && ft_strequ("-d", av[i]) && lemin->p_data)
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

int 		*find_short_route(t_lemin *lemin)
{
	int i;
	int len;
	int *arr;
	int k;

	i = 0;
	k = 0;
	len = lemin->num_rooms;
	while (i < lemin->num_routes)
	{
		if (route_len(lemin, lemin->routes[i]) > 0 &&
			route_len(lemin, lemin->routes[i]) < len)
		{
			len = route_len(lemin, lemin->routes[i]);
			k = i;
			arr = lemin->routes[i];
		}
		i++;
	}
	lemin->routes[k] = 0;
	return (arr);
}

void 		sort_routes(t_lemin *lemin)
{
	int **routes;
	int i;

	routes = ft_memalloc((lemin->num_routes + 1) * 2);
	i = 0;
	while (i < lemin->num_routes)
	{
		routes[i] = find_short_route(lemin);
		i++;
	}
	free(lemin->routes);
	lemin->routes = routes;
}

int 		biggest_len(t_lemin *lemin, int *arr)
{
	int i;
	int len;
	int	tmp;

	i = 0;
	len = 0;
	while (arr[i])
	{
		tmp = route_len(lemin, lemin->routes[i]) + arr[i];
		if (tmp > len)
			len = tmp;
		i++;
	}
	free(arr);
	return (len);
}

int 		group_steps(t_lemin *lemin)
{
	int i;
	int ants;
	int use;
	int	*lens;

	lens = ft_memalloc(lemin->num_routes * sizeof(int));
	ants = routes_to_use(lemin, lemin->num_ants);
	while (ants < lemin->num_ants)
	{
		use = routes_to_use(lemin, ants);
		i = 0;
		while (i < use)
		{
			lens[i]++;
			ants++;
			i++;
		}
	}
	return (biggest_len(lemin, lens));
}

void 		get_start_points(t_lemin *lemin)
{
	int i;
	int len;
	int id;

	len = lemin->num_rooms;
	id = 0;
	if (!(lemin->routes_groups = ft_memalloc((lemin->bfs_prec + 1) * 2)))
		put_error("ERROR");
	get_start_routes(lemin);
	i = 0;
	while (lemin->start_routes[i])
	{
		if (!(lemin->routes = ft_memalloc(lemin->num_rooms * 2)))
			put_error("ERROR");
		lemin->routes[0] = lemin->start_routes[i];
		clean_route_in_matrix(lemin, lemin->start_routes[i]);
		reset_bfs(lemin);
		bfs(lemin);
		lemin->num_routes = 1;
		find_routes(lemin);
		sort_routes(lemin);
		if (group_steps(lemin) < len)
		{
			len = group_steps(lemin);
			id = i;
		}
		lemin->routes_groups[i] = lemin->routes;
		i++;
		lemin->start_routes[i] ? restore_matrix(lemin) : 0;
	}
	lemin->routes = lemin->routes_groups[id];
	lemin->num_routes = 0;
	while (lemin->routes[lemin->num_routes])
		lemin->num_routes++;
}

int			main(int ac, char **av)
{
	t_lemin		*lemin;

	lemin = init_lemin();
	parse_flags(lemin, ac, av);
	read_data(lemin);
	parse_data(lemin);
	rooms_to_massive(lemin);
	lemin->bfs_prec = 6;
	bfs(lemin);
	lemin->bfs_prec = 6;
	get_start_points(lemin);
	flow_ants(lemin);
	lemin->p_routes ? print_routes(lemin) : 0;
	exit(0);
}

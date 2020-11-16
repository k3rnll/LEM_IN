#include "../include/lem_in.h"

int 	route_len_sum(t_lemin *lemin, int x)
{
	int i;
	int sum;

	if (x == 1)
		return (0);
	i = x - 1;
	sum = 0;
	while (i)
	{
		sum += route_len(lemin, lemin->routes[x - 1]) - route_len(lemin, lemin->routes[i - 1]);
		i--;
	}
	return (sum);
}

int 	routes_to_use(t_lemin *lemin, int ants)
{
	int i;

	if (lemin->num_routes == 1)
		return (1);
	i = 1;
	while (i < lemin->num_routes && ants)
	{
		if (ants < route_len_sum(lemin, i))
			return (i - 1);
		ants--;
		i++;
	}
	return (i);
}
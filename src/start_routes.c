#include "../include/lem_in.h"
#include "../libft/libft.h"

int		*shadow_route(t_lemin *lemin, int y)
{
	int	*arr;
	int	i;
	int	x;

	x = lemin->num_rooms - 1;
	if (!(arr = ft_memalloc(lemin->num_rooms + 1)))
		put_error("ERROR");
	i = 0;
	if (y == 0)
		lemin->rooms_links[y][lemin->num_rooms - 1] = 0;
	else
		i = lemin->rooms_links[y][lemin->num_rooms - 1] - 1;
	arr[i--] = x;
	while (i >= 0)
	{
		arr[i] = y;
		y = get_in_point(lemin, y, 0);
		if (y == 0 && i > 0)
			y = get_in_point(lemin, arr[i + 1], arr[i] + 1);
		else
			i--;
	}
	return (arr);
}

void	get_start_routes(t_lemin *lemin)
{
	int	y;

	if (!(lemin->start_routes = ft_memalloc((lemin->bfs_prec + 1) * 2)))
		put_error("ERROR");
	y = 0;
	while (y < lemin->num_rooms)
	{
		if ((y == 0 && lemin->rooms_links[y][lemin->num_rooms - 1] > 0) ||
			lemin->rooms_links[y][lemin->num_rooms - 1] > 1)
		{
			lemin->start_routes[lemin->num_routes] = shadow_route(lemin, y);
			lemin->num_routes += 1;
		}
		y++;
	}
}
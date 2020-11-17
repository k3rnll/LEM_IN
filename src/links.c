/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   links.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarkita <tmarkita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 21:02:34 by tmarkita          #+#    #+#             */
/*   Updated: 2020/11/17 21:07:15 by k3               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/lem_in.h"
#include "../libft/libft.h"

void	add_link_name(t_lemin *lemin, char **arr)
{
	lemin->num_links += 1;
	lemin->links_names[lemin->num_links * 2 - 2] = arr[0];
	lemin->links_names[lemin->num_links * 2 - 1] = arr[1];
}

int		check_link_names(t_lemin *lemin)
{
	int		i;
	char	**arr;

	i = 0;
	while (i < lemin->data_len)
	{
		arr = ft_strsplit(*(lemin->first_data + i), '-');
		if (!arr || !*arr)
			return (0);
		if (*arr[0] != '#' && arr[1] && *arr[1] != '#')
		{
			if (arr[2] ||
				(i > 1 && (ft_strequ(lemin->first_data[i - 1], "##start") ||
						ft_strequ(lemin->first_data[i - 1], "##end"))))
				put_error("ERROR");
			add_link_name(lemin, arr);
		}
		else
			free_strsplit(arr);
		i++;
		free(arr);
	}
	return (1);
}

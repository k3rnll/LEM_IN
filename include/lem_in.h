/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarkita <tmarkita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 13:51:08 by k3                #+#    #+#             */
/*   Updated: 2020/11/08 19:07:06 by k3               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef LEM_IN_H
# define LEM_IN_H

# define BUFF		1

typedef struct		s_lemin
{
	char			**first_data;
	int				data_len;
	int				num_ants;
	int				num_rooms;
	char			**rooms_names;
	char 			**links_names;
	int 			**rooms_coords;
	int				**rooms_links;
	int				**routes;

	int				something;
}					t_lemin;

int					read_data(t_lemin *lemin);
int					parse_data(t_lemin *lemin);
char				**realloc_data(char **old, int *data_len);
void				free_strsplit(char **arr);


#endif

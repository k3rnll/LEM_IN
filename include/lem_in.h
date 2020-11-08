/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarkita <tmarkita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 13:51:08 by k3                #+#    #+#             */
/*   Updated: 2020/11/08 15:10:27 by k3               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef LEM_IN_H
# define LEM_IN_H

# define BUFF		1

typedef struct		s_lemin
{
	char 			**first_data;
	int 			data_len;
	int 			num_ants;
	int 			num_rooms;
	char 			**rooms_names;
	int 			**rooms_links;
	int 			**routes;

	int 			something;
}					t_lemin;

int 				read_data(t_lemin *lemin);

#endif

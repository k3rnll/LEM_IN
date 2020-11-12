/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarkita <tmarkita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 13:51:08 by k3                #+#    #+#             */
/*   Updated: 2020/11/12 13:10:52 by k3               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef LEM_IN_H
# define LEM_IN_H

# define BUFF		160000

typedef struct		s_lemin
{
	char			**first_data;
	int				data_len;
	int 			ants_flag;
	int				num_ants;
	int				num_rooms;
	int 			num_links;
	int 			num_routes;
	char 			*start_room_name;
	char 			*end_room_name;
	char			**rooms_names;
	char 			**links_names;
	int 			**rooms_coords;
	int				**rooms_links;
	int				**routes;

	int				something;
}					t_lemin;

void				put_error(char *str);
int					read_data(t_lemin *lemin);
int					parse_data(t_lemin *lemin);
char				**realloc_data(char **old, int *data_len);
int					smart_atoi(char *str);
int					ft_isnumber(char *str);
void				free_strsplit(char **arr);

int 				rooms_to_massive(t_lemin *lemin);
int 				find_routes(t_lemin *lemin);
int 				flow_ants(t_lemin *lemin);


#endif

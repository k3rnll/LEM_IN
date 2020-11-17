/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarkita <tmarkita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 13:51:08 by k3                #+#    #+#             */
/*   Updated: 2020/11/17 14:37:46 by k3               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef LEM_IN_H
# define LEM_IN_H

# define BUFF		1

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
	int 			*rooms_total_links;
	int				**routes;
	int 			min_route_len;
}					t_lemin;

typedef struct      s_ant
{
	int             ant_num;
	int             route_index;
	int             curr_room;
	int             step;
	struct s_ant  	*next;
	struct s_ant  	*last;
}                   t_ant;

void				put_error(char *str);
int					read_data(t_lemin *lemin);
int					parse_data(t_lemin *lemin);
char				**realloc_data(char **old, int *data_len);
int					smart_atoi(char *str);
int					ft_isnumber(char *str);
int 				route_len(t_lemin *lemin, int *arr);
int 				rooms_to_massive(t_lemin *lemin);
void 				bfs(t_lemin *lemin);
void				reset_bfs(t_lemin *lemin);
int 				find_routes(t_lemin *lemin);
void 				flow_ants(t_lemin *lemin);
int 				routes_to_use(t_lemin *lemin, int ants);
void 				free_strsplit(char **arr);

#endif

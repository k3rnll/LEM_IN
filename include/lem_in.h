/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarkita <tmarkita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 13:51:08 by tmarkita          #+#    #+#             */
/*   Updated: 2020/11/23 20:36:58 by k3               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# define BUFF		1

typedef struct		s_lemin
{
	char			**first_data;
	int				data_len;
	int				ants_flag;
	int				num_ants;
	int				num_rooms;
	int				num_links;
	int				num_routes;
	char			*start_room_name;
	char			*end_room_name;
	char			**rooms_names;
	char			**links_names;
	int				**rooms_coords;
	int				**rooms_links;
	int				**routes;
	int				min_route_len;
	int 			p_routes;
	int 			p_data;
	int 			**start_routes;
	int 			bfs_prec;
	int 			***routes_groups;
	int 			founded;
}					t_lemin;

typedef struct		s_ant
{
	int				ant_num;
	int				route_index;
	int				curr_room;
	int				step;
	struct s_ant	*next;
	struct s_ant	*last;
}					t_ant;

void				put_error(char *str);
void				print_input_data(t_lemin *lemin);
int					read_data(t_lemin *lemin);
void				parse_data(t_lemin *lemin);
void				check_room_names(t_lemin *lemin);
void				check_coords(t_lemin *lemin, int *xy);
int					check_link_names(t_lemin *lemin);
void				realloc_data(t_lemin *lemin);
int					smart_atoi(char *str);
int					ft_isnumber(char *str);
int					route_len(t_lemin *lemin, int *arr);
void				rooms_to_massive(t_lemin *lemin);
void				bfs(t_lemin *lemin);
void				reset_bfs(t_lemin *lemin);
void				find_routes(t_lemin *lemin);
void				clean_route_in_matrix(t_lemin *lemin, int *arr);
void				flow_ants(t_lemin *lemin);
int					routes_to_use(t_lemin *lemin, int ants);
void				free_strsplit(char **arr);
t_ant				*new_ant(int num, int ind);
void				add_ant(t_ant *ant, int num, int ind);
void				free_ants(t_ant **ant_groups);
void				fill_ant_groups(t_lemin *lemin,
						t_ant **ant_groups, int ants);
void				print_routes(t_lemin *lemin);
int 				*limp_route(t_lemin *lemin, int len);
void 				del_limp_route(t_lemin *lemin);
int					get_in_point(t_lemin *lemin, int y, int x);
void				get_start_routes(t_lemin *lemin);
void				clean_route_in_matrix(t_lemin *lemin, int *arr);
void				restore_matrix(t_lemin *lemin);

#endif

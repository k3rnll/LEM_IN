# ifndef LEM_IN_TEMP_FUNC_H
# define LEM_IN_TEMP_FUNC_H

# include "lem_in.h"

/// TEMP FUNCTIONS BLOCK
void 				del_mirror(t_lemin *lemin);
void 				del_deadends(t_lemin *lemin);
void 				del_input_forks(t_lemin *lemin);

void 				print_matrix(t_lemin *lemin);
void				print_firstline(t_lemin *lemin, int y);
void 				print_endline(t_lemin *lemin);
void				print_one_route(t_lemin *lemin, int *arr);
void				print_route(t_lemin *lemin, int **arr);
void				print_total_links(t_lemin *lemin);
void				print_data(t_lemin *lemin);
void				find_min_bfs(t_lemin *lemin);
void				del_cross_lines(t_lemin *lemin, int x);
int					check_out_forks(t_lemin *lemin, int y);
int					path_has_out_forks(t_lemin *lemin, int y);
/// END TEMP FUNCTIONS BLOCK


#endif //LEM_IN_TEMP_FUNC_H

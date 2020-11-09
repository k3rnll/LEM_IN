/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarkita <tmarkita@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 16:24:53 by k3                #+#    #+#             */
/*   Updated: 2020/11/08 17:50:44 by k3               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "../include/lem_in.h"

void 	free_strsplit(char **arr)
{
	int	i;

	i  = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void 	free_first_data(char **old, int *data_len)
{
	int 	i;

	i = 0;
	while (i < *data_len)
	{
		free(*(old + i));
		i++;
	}
	free(old);
}

char 	**realloc_data(char **old, int *data_len)
{
	char 	**new;

	new = ft_memalloc((*data_len + BUFF) * 8);
	if (new)
	{
		ft_bzero(new, (*data_len + BUFF) * 8);
		ft_memcpy(new, old, *data_len * 8);
		free(old);
		*data_len += BUFF;
	}
	else
	{
		free_first_data(old, data_len);
		ft_putendl_fd("ERROR: no memory", 2);
		exit (1);
	}
	return (new);
}
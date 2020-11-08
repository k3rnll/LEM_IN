/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarkita <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/22 14:49:40 by tmarkita          #+#    #+#             */
/*   Updated: 2019/09/22 15:50:09 by tmarkita         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*tmp;

	tmp = (t_list *)malloc(sizeof(t_list));
	if (tmp)
	{
		if (content != NULL)
		{
			tmp->content = (void *)malloc(content_size * sizeof(size_t));
			ft_memcpy(tmp->content, content, content_size);
		}
		else
		{
			tmp->content = NULL;
			content_size = 0;
		}
		tmp->content_size = content_size;
		tmp->next = NULL;
	}
	return (tmp);
}

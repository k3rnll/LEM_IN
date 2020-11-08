/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmarkita <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 09:40:15 by tmarkita          #+#    #+#             */
/*   Updated: 2020/10/30 19:55:04 by k3               ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	new_line(void **content, char **line)
{
	char	*tmp;
	size_t	i;

	i = 0;
	tmp = (char*)*content;
	if (tmp && *tmp != '\0')
	{
		if (ft_strchr((char*)*content, '\n'))
		{
			while (tmp[i] != '\n')
				i++;
			*line = ft_strsub((char*)*content, 0, i);
			tmp = ft_strsub((char*)*content, i + 1, ft_strlen(tmp) - i);
			ft_strdel((char**)content);
			*content = tmp;
			return (1);
		}
	}
	return (0);
}

static int	find_list(t_list **head, t_list **list, const int *fd)
{
	t_list	*tmp;

	tmp = *head;
	while (tmp)
	{
		if (tmp->content_size == (size_t)*fd)
		{
			*list = tmp;
			if (!tmp->content)
				return (0);
			return (1);
		}
		tmp = tmp->next;
	}
	tmp = ft_lstnew(0, 0);
	tmp->content_size = *fd;
	ft_lstadd(head, tmp);
	*list = *head;
	return (0);
}

static int	last_line(t_list **list, char **line)
{
	size_t	i;
	char	*c;

	c = (*list)->content;
	if (!c || *c == '\0')
		return (0);
	i = ft_strlen((*list)->content);
	*line = ft_strsub((*list)->content, 0, i);
	ft_strdel((char **)&((*list)->content));
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	static t_list	*head;
	t_list			*list;
	char			buf[16];
	int				ret;
	char			*tmp;

	if (fd < 0 || !line)
		return (-1);
	find_list(&head, &list, &fd);
	if (new_line(&(list)->content, line))
		return (1);
	while ((ret = read(fd, buf, 16)) > 0)
	{
		*line = ft_strsub(buf, 0, ret);
		tmp = list->content;
		if (!(list->content = ft_strjoin(tmp, *line)))
			list->content = ft_strsub(buf, 0, ret);
		ft_strdel(line);
		ft_strdel(&tmp);
		if (new_line(&(list)->content, line))
			return (1);
	}
	if (ret < 0)
		return (-1);
	return (last_line(&list, line));
}

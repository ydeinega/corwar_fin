/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 17:41:17 by ydeineha          #+#    #+#             */
/*   Updated: 2017/12/19 17:41:21 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		get_next_line(const int fd, char **line)
{
	static t_list	*head = NULL;
	char			**str;

	str = head ? ft_bufstr(head, fd) : NULL;
	if (fd < 0 || !line || BUFF_SIZE < 1)
		return (-1);
	if (line && *line)
		*line = NULL;
	if (str && ft_copy_bn(line, str) == 1)
		return (1);
	return (reading(fd, line, str, &head));
}

int		reading(const int fd, char **line, char **str, t_list **head)
{
	char	*buf;
	int		ret;
	char	*tmp;

	buf = ft_strnew(BUFF_SIZE);
	while (buf && (ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		if (ft_copy_bn(line, &buf) == 1)
		{
			if (*head)
			{
				!str ? ft_lstadd(head, ft_lst_create(buf, fd)) : 0;
				str ? tmp = *str : 0;
				str ? *str = buf : 0;
				str ? ft_strdel(&tmp) : 0;
			}
			else
				*head = ft_lst_create(buf, fd);
			return (1);
		}
	}
	buf ? ft_strdel(&buf) : 0;
	if (ret < 0)
		return (-1);
	return ((!(*line) || ft_strcmp(*line, "\0") == 0) && ret == 0 ? 0 : 1);
}

int		ft_copy_bn(char **line, char **buf)
{
	int		i;
	char	*tmp;
	char	*tmp_fin;
	char	*ret;
	char	*remainder;

	i = 0;
	tmp = *buf;
	while (tmp[i] != '\n' && tmp[i] != '\0')
		i++;
	tmp = ft_strsub(*buf, 0, i);
	ret = ft_strchr(*buf, '\n');
	remainder = ret ? ft_strdup(&ret[1]) : ft_strnew(BUFF_SIZE);
	ft_strdel(buf);
	*buf = remainder;
	if (*line)
	{
		tmp_fin = ft_strjoin(*line, tmp);
		ft_strdel(line);
		ft_strdel(&tmp);
		*line = tmp_fin;
	}
	else
		*line = tmp;
	return (ret ? 1 : 0);
}

char	**ft_bufstr(t_list *head, int fd)
{
	t_list	*tmp;

	tmp = head;
	while (tmp)
	{
		if (tmp->content_size == (size_t)fd)
			return ((char **)&tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}

t_list	*ft_lst_create(char *buf, int fd)
{
	t_list	*ptr;

	ptr = buf ? (t_list *)malloc(sizeof(t_list)) : NULL;
	if (ptr)
	{
		ptr->next = NULL;
		ptr->content = buf;
		ptr->content_size = (size_t)fd;
	}
	return (ptr);
}

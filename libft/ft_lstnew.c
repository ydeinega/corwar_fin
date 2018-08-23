/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 14:42:14 by ydeineha          #+#    #+#             */
/*   Updated: 2017/11/14 15:06:12 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*ptr;

	ptr = NULL;
	ptr = (t_list *)malloc(sizeof(t_list));
	if (ptr != NULL)
	{
		ptr->next = NULL;
		ptr->content = ft_memalloc(content_size);
		if (ptr->content != NULL)
		{
			if (content == NULL)
			{
				ptr->content = NULL;
				ptr->content_size = 0;
			}
			else
			{
				ptr->content = ft_memcpy(ptr->content, content, content_size);
				ptr->content_size = content_size;
			}
		}
		else
			ft_memdel((void **)ptr);
	}
	return (ptr);
}

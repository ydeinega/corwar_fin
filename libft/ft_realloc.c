/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 11:38:33 by ydeineha          #+#    #+#             */
/*   Updated: 2017/11/17 11:38:38 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t ptr_size, size_t size)
{
	char	*tmp;

	tmp = NULL;
	if (!size && ptr)
		ft_memdel(&ptr);
	else
	{
		if (!ptr)
			ptr = (char *)ft_memalloc(size);
		else
		{
			tmp = (char *)ft_memalloc(size);
			if (size >= ptr_size)
				tmp = (char *)ft_memcpy(tmp, ptr, ptr_size);
			else
			{
				tmp = (char *)ft_memcpy(tmp, ptr, size);
			}
			ft_memdel(&ptr);
			ptr = tmp;
			tmp = NULL;
		}
	}
	return (ptr);
}

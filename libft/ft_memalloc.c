/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 14:44:18 by ydeineha          #+#    #+#             */
/*   Updated: 2017/11/06 15:21:30 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char	*ptr;
	size_t	i;

	ptr = NULL;
	i = 0;
	ptr = (char *)malloc(sizeof(char) * size);
	if (ptr != NULL)
	{
		while (i < size)
		{
			ptr[i] = '\0';
			i++;
		}
	}
	return (ptr);
}

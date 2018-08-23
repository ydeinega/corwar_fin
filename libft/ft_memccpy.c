/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 17:33:43 by ydeineha          #+#    #+#             */
/*   Updated: 2017/11/15 14:03:55 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	void			*ptr;
	size_t			i;
	unsigned char	ch;

	ptr = NULL;
	i = 0;
	ch = (unsigned char)c;
	while (i < n)
	{
		*((unsigned char *)(dst + i)) = *((unsigned char *)(src + i));
		if (*((unsigned char *)(src + i)) == ch)
		{
			ptr = (unsigned char *)(dst + i + 1);
			break ;
		}
		i++;
	}
	return (ptr);
}

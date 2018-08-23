/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 18:23:24 by ydeineha          #+#    #+#             */
/*   Updated: 2017/11/15 14:35:33 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	ch;
	size_t			i;

	i = 0;
	ptr = NULL;
	ch = (unsigned char)c;
	while (i < n)
	{
		if (*((unsigned char *)(s + i)) == ch)
		{
			ptr = (unsigned char *)(s + i);
			break ;
		}
		i++;
	}
	return (ptr);
}

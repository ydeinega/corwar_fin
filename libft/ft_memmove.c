/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 17:44:23 by ydeineha          #+#    #+#             */
/*   Updated: 2017/11/08 22:39:53 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if (dst > src)
	{
		if (len != 0)
		{
			len--;
			while (len > 0)
			{
				*((char *)(dst + len)) = *((char *)(src + len));
				len--;
			}
			*((char *)dst) = *((char *)src);
		}
	}
	else
	{
		ft_memcpy(dst, src, len);
	}
	return (dst);
}

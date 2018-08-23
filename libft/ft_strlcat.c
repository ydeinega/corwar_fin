/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 19:06:00 by ydeineha          #+#    #+#             */
/*   Updated: 2017/11/15 14:08:19 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t i;
	size_t j;
	size_t max;
	size_t dstlen;

	i = 0;
	j = 0;
	dstlen = ft_strlen(dst);
	if (dstsize != 0 && dstlen < dstsize)
	{
		max = dstsize - dstlen - 1;
		while (dst[i] != '\0')
			i++;
		while ((j < max) && (src[j] != '\0'))
		{
			dst[i] = src[j];
			i++;
			j++;
		}
		dst[i] = '\0';
		return (dstlen + ft_strlen(src));
	}
	else
		return (dstsize + ft_strlen(src));
}

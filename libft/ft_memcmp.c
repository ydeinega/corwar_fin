/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 18:44:46 by ydeineha          #+#    #+#             */
/*   Updated: 2017/11/15 14:05:09 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t i;

	i = 0;
	while ((i < n) &&
			(*((unsigned char *)(s1 + i)) == *((unsigned char *)(s2 + i))))
	{
		i++;
	}
	if (i == n)
		return (0);
	else
		return (*((unsigned char *)(s1 + i)) - *((unsigned char *)(s2 + i)));
}

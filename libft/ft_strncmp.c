/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 19:57:45 by ydeineha          #+#    #+#             */
/*   Updated: 2017/10/28 20:08:12 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	i = 0;
	if (!n)
		return (0);
	else
	{
		while (((unsigned char)s1[i] == (unsigned char)s2[i])
			&& (s1[i] != '\0') && (s2[i] != '\0') && (i < n))
			i++;
		if (i == n)
			return (0);
		else
			return ((int)((unsigned char)s1[i] - (unsigned char)s2[i]));
	}
}

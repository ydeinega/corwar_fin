/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 19:15:54 by ydeineha          #+#    #+#             */
/*   Updated: 2017/10/28 19:47:09 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	int i;

	i = 0;
	while (((unsigned char)s1[i] == (unsigned char)s2[i]) &&
			(s1[i] != '\0') && (s2[i] != '\0'))
	{
		i++;
	}
	return ((int)((unsigned char)s1[i] - (unsigned char)s2[i]));
}

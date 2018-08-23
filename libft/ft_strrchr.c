/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 21:24:26 by ydeineha          #+#    #+#             */
/*   Updated: 2017/10/30 21:32:05 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*last_occur;
	int		i;

	last_occur = NULL;
	i = ft_strlen(s);
	while ((i >= 0) && (s[i] != c))
	{
		i--;
	}
	if (s[i] == c)
	{
		last_occur = (char *)(s + i);
	}
	return (last_occur);
}

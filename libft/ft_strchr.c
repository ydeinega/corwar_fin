/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 21:17:02 by ydeineha          #+#    #+#             */
/*   Updated: 2017/10/30 21:31:31 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*first_occur;
	int		i;

	first_occur = NULL;
	i = 0;
	while ((s[i] != c) && (s[i] != '\0'))
	{
		i++;
	}
	if (s[i] == c)
	{
		first_occur = (char *)(s + i);
	}
	return (first_occur);
}

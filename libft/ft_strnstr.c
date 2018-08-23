/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 22:24:57 by ydeineha          #+#    #+#             */
/*   Updated: 2017/11/15 14:10:38 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*ptr;
	size_t	i;
	size_t	j;

	ptr = NULL;
	i = 0;
	j = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (big[i] != '\0')
	{
		while (big[i] == little[j] && i < len && little[j] && big[i])
		{
			i++;
			j++;
		}
		if (j == ft_strlen(little))
		{
			ptr = (char *)(big + i - j);
			break ;
		}
		i = i - j + 1;
		j = 0;
	}
	return (ptr);
}

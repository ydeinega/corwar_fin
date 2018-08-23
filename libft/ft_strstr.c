/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 21:34:55 by ydeineha          #+#    #+#             */
/*   Updated: 2017/11/15 14:11:12 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	char	*ptr;
	size_t	i;
	size_t	j;

	ptr = NULL;
	i = 0;
	j = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[i] != '\0')
	{
		while (haystack[i] == needle[j] && needle[j] && haystack[i])
		{
			i++;
			j++;
		}
		if (j == ft_strlen(needle))
		{
			ptr = (char *)(haystack + i - j);
			break ;
		}
		i = i - j + 1;
		j = 0;
	}
	return (ptr);
}

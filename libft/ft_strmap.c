/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 21:59:11 by ydeineha          #+#    #+#             */
/*   Updated: 2017/11/15 15:15:02 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*ptr;
	int		i;

	i = 0;
	ptr = NULL;
	if (s && f)
	{
		ptr = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
		if (ptr != NULL)
		{
			while (s[i] != '\0')
			{
				ptr[i] = f(s[i]);
				i++;
			}
			ptr[i] = '\0';
		}
	}
	return (ptr);
}

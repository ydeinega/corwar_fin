/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 14:28:06 by ydeineha          #+#    #+#             */
/*   Updated: 2017/11/15 16:06:02 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ptr;
	size_t	len_s1;
	size_t	len_s2;

	ptr = NULL;
	if (s1 != NULL && s2 != NULL)
	{
		len_s1 = ft_strlen(s1);
		len_s2 = ft_strlen(s2);
		ptr = ft_strnew(len_s1 + len_s2);
		if (ptr != NULL)
		{
			ft_strncpy(ptr, s1, len_s1);
			ft_strncpy(&ptr[len_s1], s2, len_s2);
		}
	}
	return (ptr);
}

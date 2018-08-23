/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 14:07:32 by ydeineha          #+#    #+#             */
/*   Updated: 2017/11/15 15:22:59 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*ptr;

	ptr = NULL;
	if (s != NULL)
	{
		ptr = ft_strnew(len);
		if (ptr != NULL)
			ptr = ft_strncpy(ptr, &s[start], len);
	}
	return (ptr);
}

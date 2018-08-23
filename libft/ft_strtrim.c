/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 14:47:23 by ydeineha          #+#    #+#             */
/*   Updated: 2017/11/15 15:27:46 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_iswspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	else
		return (0);
}

char		*ft_strtrim(char const *s)
{
	char	*ptr;
	size_t	start;
	size_t	end;

	ptr = NULL;
	start = 0;
	if (s != NULL)
	{
		end = ft_strlen(s) - 1;
		if (s[start] != '\0')
		{
			while (ft_iswspace(s[start]) == 1 && start < end)
				start++;
			while (ft_iswspace(s[end]) == 1 && end > 0)
				end--;
			if (start <= end)
				ptr = ft_strsub(s, start, end - start + 1);
			else
				ptr = ft_strnew(0);
		}
		else
			ptr = ft_strnew(0);
	}
	return (ptr);
}

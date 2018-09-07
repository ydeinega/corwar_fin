/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strljoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 21:28:44 by ydeineha          #+#    #+#             */
/*   Updated: 2018/09/05 21:28:47 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

char		*ft_strljoin(char **s1, char **s2)
{
	char	*without_leaks;

	without_leaks = NULL;
	if (!s1 && !s2)
		return (NULL);
	else if (!*s1 && *s2)
	{
		without_leaks = *s2;
		*s2 = NULL;
	}
	else if (!*s2 && *s1)
	{
		without_leaks = *s1;
		*s1 = NULL;
	}
	else
	{
		without_leaks = ft_strjoin(*s1, *s2);
		ft_strdel(s1);
		ft_strdel(s2);
	}
	return (without_leaks);
}

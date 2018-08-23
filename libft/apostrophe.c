/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apostrophe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 18:04:02 by ydeineha          #+#    #+#             */
/*   Updated: 2018/03/16 18:04:05 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	apostrophe(char **str, int n)
{
	char			*s;
	char			sep;
	struct lconv	*s_sign;

	s = *str;
	s_sign = localeconv();
	sep = *(s_sign->thousands_sep);
	if (sep != 0 && n > 0)
	{
		*str = str_ap(s, sep, n);
		ft_strdel(&s);
	}
}

int		count_sep(unsigned long long num)
{
	int n;

	n = 0;
	while (num / 1000 > 0)
	{
		n++;
		num = num / 1000;
	}
	return (n);
}

char	*str_ap(char *s, char sep, int n)
{
	char	*s_new;
	int		len;
	int		len_new;
	int		i;

	len = ft_strlen(s);
	len_new = len + n;
	i = 0;
	s_new = ft_strnew(len_new);
	if (!s_new)
		return (NULL);
	len--;
	len_new--;
	while (len_new >= 0)
	{
		if (i == 3)
			s_new[len_new] = sep;
		else
			s_new[len_new] = s[len];
		len = i == 3 ? len : len - 1;
		len_new--;
		i = i == 3 ? 0 : i + 1;
	}
	return (s_new);
}

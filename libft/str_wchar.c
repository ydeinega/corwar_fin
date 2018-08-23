/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_wchar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 20:03:34 by ydeineha          #+#    #+#             */
/*   Updated: 2018/03/22 20:03:37 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*make_str_wchr(wchar_t *w, t_size mod)
{
	char	*str;
	char	*tmp;
	int		i;

	str = ft_strnew(5);
	tmp = NULL;
	i = 0;
	if (mod.s == 'C' || mod.s == 'c')
		str = ft_unicode(*w, &str);
	else
	{
		while (w[i])
		{
			if (!str)
				str = ft_unicode(w[i], &str);
			else
			{
				tmp = ft_unicode(w[i], &tmp);
				str = ft_strjoin_leaks(&str, &tmp);
			}
			i++;
		}
	}
	return (str);
}

char	*ft_unicode(wchar_t c, char **str)
{
	char	*s;

	s = *str ? *str : ft_strnew(5);
	if (c < (1 << 7))
		s[0] = (char)c;
	else if (c < (1 << 11))
	{
		s[0] = (char)(192 | (c >> 6));
		s[1] = (char)(128 | (c & 63));
	}
	else if (c < (1 << 16))
	{
		s[0] = (char)(224 | (c >> 12));
		s[1] = (char)(128 | ((c >> 6) & 63));
		s[2] = (char)(128 | ((c & 63)));
	}
	else
	{
		s[0] = (char)(240 | (c >> 18));
		s[1] = (char)(128 | ((c >> 12) & 63));
		s[2] = (char)(128 | ((c >> 6) & 63));
		s[3] = (char)(128 | (c & 63));
	}
	return (s);
}

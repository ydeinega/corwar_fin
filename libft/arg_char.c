/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_char.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 18:05:24 by ydeineha          #+#    #+#             */
/*   Updated: 2018/03/16 18:05:27 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		arg_char(t_size mod, t_flags flag, va_list ap, va_list cp)
{
	char	*s;
	int		n;

	n = 0;
	s = conv_char(mod, flag.dol, ap, cp);
	if (!s)
		return (0);
	if (ft_strlen(s) == 0 && (mod.s == 'c' || mod.s == 'C'))
		n++;
	if (flag.prc != -1)
		(flag.prc == 0 && (mod.s == 'c' || mod.s == 'C')) ? 0 :
		precision_chr(&s, flag.prc);
	if (flag.width)
		width_num(&s, flag, mod);
	n = n + ft_strlen(s);
	write(1, s, n);
	ft_strdel(&s);
	return (n);
}

void	precision_chr(char **str, int prc)
{
	char	*s_new;
	char	*s;
	int		i;
	int		len;

	s_new = NULL;
	s = *str;
	i = 0;
	len = ft_strlen(s);
	if (prc < len)
	{
		s_new = ft_strnew(prc);
		while (i < prc)
		{
			if (((unsigned char)(s[i] & 224) == 192 && prc - i < 2) ||
				((unsigned char)(s[i] & 240) == 224 && prc - i < 3) ||
				((unsigned char)(s[i] & 248) == 240 && prc - i < 4))
				break ;
			s_new[i] = s[i];
			i++;
		}
		*str = s_new;
		ft_strdel(&s);
	}
}

char	*ft_strjoin_leaks(char **s1, char **s2)
{
	char	*str;

	str = ft_strjoin(*s1, *s2);
	ft_strdel(s1);
	ft_strdel(s2);
	return (str);
}

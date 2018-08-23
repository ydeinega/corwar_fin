/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 17:38:43 by ydeineha          #+#    #+#             */
/*   Updated: 2018/01/31 17:38:58 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_size	parse_modifiers(char *fmt, int b_type, char specifier)
{
	t_size	mod;
	int		tmp;

	mod.s = specifier;
	mod.type = b_type;
	tmp = count_char(fmt, 'h');
	mod.hh = (tmp > 0 && tmp % 2 == 0) ? 1 : 0;
	mod.h = (tmp > 0 && tmp % 2 != 0) ? 1 : 0;
	tmp = count_char(fmt, 'l');
	mod.l = (tmp > 0 && tmp % 2 != 0) ? 1 : 0;
	mod.ll = (tmp > 0 && tmp % 2 == 0) ? 1 : 0;
	mod.j = ft_strchr(fmt, 'j') ? 1 : 0;
	mod.z = ft_strchr(fmt, 'z') ? 1 : 0;
	return (mod);
}

t_flags	parse_flags(char *fmt, va_list ap, va_list cp, int n)
{
	t_flags	flag;

	flag.dol = dollar_arg(fmt);
	flag.hash = ft_strchr(fmt, '#') ? 1 : 0;
	flag.zero = zero_flag(fmt);
	flag.minus = ft_strchr(fmt, '-') ? 1 : 0;
	flag.sp = ft_strchr(fmt, ' ') ? 1 : 0;
	flag.plus = ft_strchr(fmt, '+') ? 1 : 0;
	flag.ap = ft_strchr(fmt, '\'') ? 1 : 0;
	flag.width = width_value(fmt);
	flag.prc = prc_value(fmt);
	flag.dol_w = dollar_width(fmt);
	flag.dol_prc = dollar_precision(fmt);
	star(fmt, &flag, ap, cp);
	flag.n = n;
	return (flag);
}

int		count_char(char *str, char c)
{
	int i;
	int n;

	i = 0;
	n = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			n++;
		i++;
	}
	return (n);
}

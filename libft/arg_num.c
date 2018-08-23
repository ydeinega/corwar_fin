/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_num.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 16:46:59 by ydeineha          #+#    #+#             */
/*   Updated: 2018/01/31 16:47:17 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					arg_num(t_size mod, t_flags flag, va_list ap, va_list cp)
{
	long long			num;
	unsigned long long	u_num;
	char				*str;
	int					n;

	str = NULL;
	if (mod.s == 'd' || mod.s == 'D')
	{
		num = arg_sg(mod, flag.dol, ap, cp);
		str = make_str_num(mod, flag, num);
	}
	else if (mod.s == 'o' || mod.s == 'O' || mod.s == 'u' ||
		mod.s == 'U' || mod.s == 'x' || mod.s == 'X' || mod.s == 'p')
	{
		u_num = arg_un(mod, flag.dol, ap, cp);
		str = make_str_unum(mod, flag, u_num);
	}
	if (!str)
		return (0);
	n = ft_strlen(str);
	write(1, str, n);
	ft_strdel(&str);
	return (n);
}

long long			arg_sg(t_size mod, int dollar, va_list ap, va_list cp)
{
	long long num;

	num = 0;
	if (dollar)
		num = conv_sg_dol(mod, dollar, cp);
	else
		num = conv_sg(mod, ap);
	return (num);
}

long long			conv_sg_dol(t_size mod, int dollar, va_list cp)
{
	long long	num;
	int			i;
	va_list		tmp;

	num = 0;
	i = 0;
	va_copy(tmp, cp);
	while (i < dollar)
	{
		num = conv_sg(mod, tmp);
		i++;
	}
	va_end(tmp);
	return (num);
}

long long			conv_sg(t_size mod, va_list ap)
{
	long long num;

	num = 0;
	if (mod.s == 'D')
		num = (long long)va_arg(ap, long);
	else if (mod.z)
		num = (long long)va_arg(ap, ssize_t);
	else if (mod.j)
		num = (long long)va_arg(ap, intmax_t);
	else if (mod.ll)
		num = va_arg(ap, long long);
	else if (mod.l)
		num = (long long)va_arg(ap, long);
	else if (mod.h)
		num = (long long)(short)va_arg(ap, int);
	else if (mod.hh)
		num = (long long)(signed char)va_arg(ap, int);
	else
		num = (long long)va_arg(ap, int);
	return (num);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_ptr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 18:28:28 by ydeineha          #+#    #+#             */
/*   Updated: 2018/03/16 18:28:30 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		arg_ptr(t_size mod, t_flags flag, va_list ap, va_list cp)
{
	long long	*num;

	num = NULL;
	num = arg_n(mod, flag.dol, ap, cp);
	*num = (long long)flag.n;
}

long long	*arg_n(t_size mod, int dollar, va_list ap, va_list cp)
{
	long long	*num;

	num = NULL;
	if (dollar)
		num = conv_n_dol(mod, dollar, cp);
	else
		num = conv_n(mod, ap);
	return (num);
}

long long	*conv_n_dol(t_size mod, int dollar, va_list cp)
{
	long long	*num;
	int			i;
	va_list		tmp;

	num = NULL;
	i = 0;
	va_copy(tmp, cp);
	while (i < dollar)
	{
		num = conv_n(mod, tmp);
		i++;
	}
	va_end(tmp);
	return (num);
}

long long	*conv_n(t_size mod, va_list ap)
{
	long long	*num;

	num = NULL;
	if (mod.z)
		num = (long long *)va_arg(ap, ssize_t *);
	else if (mod.j)
		num = (long long *)va_arg(ap, intmax_t *);
	else if (mod.ll)
		num = va_arg(ap, long long *);
	else if (mod.l)
		num = (long long *)va_arg(ap, long *);
	else if (mod.h)
		num = (long long *)(short *)va_arg(ap, int *);
	else if (mod.hh)
		num = (long long *)(signed char *)va_arg(ap, int *);
	else
		num = (long long *)va_arg(ap, int *);
	return (num);
}

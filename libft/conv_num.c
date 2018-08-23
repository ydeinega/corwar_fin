/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_num.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 18:40:49 by ydeineha          #+#    #+#             */
/*   Updated: 2018/03/16 18:40:51 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned long long	arg_un(t_size mod, int dollar, va_list ap, va_list cp)
{
	unsigned long long num;

	num = 0;
	if (dollar)
		num = conv_un_dol(mod, dollar, cp);
	else
		num = conv_un(mod, ap);
	return (num);
}

unsigned long long	conv_un(t_size mod, va_list ap)
{
	unsigned long long num;

	num = 0;
	if (mod.s == 'p')
		num = (unsigned long long)va_arg(ap, void *);
	else if (mod.s == 'O' || mod.s == 'U')
		num = (unsigned long long)va_arg(ap, unsigned long);
	else if (mod.z)
		num = (unsigned long long)va_arg(ap, size_t);
	else if (mod.j)
		num = (unsigned long long)va_arg(ap, uintmax_t);
	else if (mod.ll)
		num = va_arg(ap, unsigned long long);
	else if (mod.l)
		num = (unsigned long long)va_arg(ap, unsigned long);
	else if (mod.h)
		num = (unsigned long long)(unsigned short)va_arg(ap, unsigned int);
	else if (mod.hh)
		num = (unsigned long long)(unsigned char)va_arg(ap, unsigned int);
	else
		num = (unsigned long long)va_arg(ap, unsigned int);
	return (num);
}

unsigned long long	conv_un_dol(t_size mod, int dollar, va_list cp)
{
	unsigned long long	num;
	int					i;
	va_list				tmp;

	num = 0;
	i = 0;
	va_copy(tmp, cp);
	while (i < dollar)
	{
		num = conv_un(mod, tmp);
		i++;
	}
	va_end(tmp);
	return (num);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star_flag.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/04 20:01:13 by ydeineha          #+#    #+#             */
/*   Updated: 2018/02/04 20:01:16 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		star(char *fmt, t_flags *flag, va_list ap, va_list cp)
{
	int		i;
	int		tmp;

	i = 0;
	while (fmt[i])
	{
		if (fmt[i] == '*' && (i == 0 || (i > 0 && fmt[i - 1] != '.')))
		{
			tmp = star_value_width(flag->dol_w, &flag->minus, ap, cp);
			if (!width_value(&fmt[i]))
				flag->width = tmp;
		}
		if (fmt[i] == '*' && i > 0 && fmt[i - 1] == '.')
		{
			tmp = star_value_precision(flag->dol_prc, ap, cp);
			if (prc_value(&fmt[i]) == -1)
				flag->prc = tmp;
		}
		i++;
	}
	return (0);
}

int		star_value(int dollar, va_list ap, va_list cp)
{
	va_list tmp;
	int		i;
	int		value;

	va_copy(tmp, cp);
	i = 0;
	value = 0;
	if (dollar > 0)
	{
		while (i < dollar)
		{
			value = va_arg(tmp, int);
			i++;
		}
	}
	else
		value = va_arg(ap, int);
	va_end(tmp);
	return (value);
}

int		star_value_width(int dollar, int *minus, va_list ap, va_list cp)
{
	int width;

	width = star_value(dollar, ap, cp);
	if (width < 0)
	{
		*minus = 1;
		width = -width;
	}
	return (width);
}

int		star_value_precision(int dollar, va_list ap, va_list cp)
{
	int prc;

	prc = star_value(dollar, ap, cp);
	if (prc < 0)
		prc = -1;
	return (prc);
}

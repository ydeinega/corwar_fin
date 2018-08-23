/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 18:30:32 by ydeineha          #+#    #+#             */
/*   Updated: 2018/03/16 18:30:35 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*conv_char(t_size mod, int dollar, va_list ap, va_list cp)
{
	char	*s;

	s = NULL;
	if (dollar)
		s = conv_chr_dol(mod, dollar, cp);
	else
		s = conv_chr(mod, ap);
	return (s);
}

char	*conv_chr_dol(t_size mod, int dollar, va_list cp)
{
	char	*s;
	int		i;
	va_list	tmp;

	s = NULL;
	i = 0;
	va_copy(tmp, cp);
	while (i < dollar)
	{
		s = conv_chr(mod, tmp);
		i++;
	}
	va_end(tmp);
	return (s);
}

char	*conv_chr(t_size mod, va_list ap)
{
	char	*s;

	s = NULL;
	if (mod.s == 's' || mod.s == 'S')
		s = conv_chr_s(mod, ap);
	else
		s = conv_chr_c(mod, ap);
	return (s);
}

char	*conv_chr_c(t_size mod, va_list ap)
{
	char	*s;
	wchar_t	*w;
	wchar_t	c;
	int		nbyte;

	s = NULL;
	w = NULL;
	nbyte = MB_CUR_MAX;
	if ((mod.s == 'C' || (mod.s == 'c' && mod.l)) && nbyte > 1)
	{
		c = (wchar_t)va_arg(ap, wint_t);
		w = &c;
	}
	else
	{
		s = ft_strnew(1);
		s[0] = (char)va_arg(ap, int);
	}
	if (w && !s)
		s = make_str_wchr(w, mod);
	return (s);
}

char	*conv_chr_s(t_size mod, va_list ap)
{
	char	*s;
	wchar_t	*w;

	s = NULL;
	w = NULL;
	if (mod.s == 'S' || (mod.s == 's' && mod.l))
	{
		w = va_arg(ap, wchar_t *);
		s = !w ? ft_strdup("(null)") : NULL;
	}
	else if (mod.s == 's')
	{
		s = va_arg(ap, char *);
		s = !s ? ft_strdup("(null)") : ft_strdup(s);
	}
	if (w && !s)
		s = make_str_wchr(w, mod);
	return (s);
}

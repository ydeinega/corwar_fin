/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_num.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 20:59:31 by ydeineha          #+#    #+#             */
/*   Updated: 2018/03/16 20:59:32 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*make_str_num(t_size mod, t_flags flag, long long num)
{
	char	*str;
	int		sign;

	sign = num < 0 ? -1 : 1;
	str = itoa_base(u_num(num), 10);
	if (!str)
		return (NULL);
	if (flag.ap)
		apostrophe(&str, count_sep(u_num(num)));
	if (flag.prc != -1)
		precision_num(&str, flag.prc, u_num(num));
	if (flag.width && flag.zero && flag.prc == -1 && !flag.minus)
		width_num(&str, flag, mod);
	sign_num(&str, sign, flag);
	if (flag.width)
		width_num(&str, flag, mod);
	return (str);
}

char	*make_str_unum(t_size mod, t_flags flag, unsigned long long num)
{
	char	*str;

	str = NULL;
	if (mod.s == 'u' || mod.s == 'U')
		str = itoa_base(num, 10);
	if (mod.s == 'o' || mod.s == 'O')
		str = itoa_base(num, 8);
	if (mod.s == 'x' || mod.s == 'X' || mod.s == 'p')
		str = itoa_base(num, 16);
	if (!str)
		return (NULL);
	if (flag.ap && (mod.s == 'u' || mod.s == 'U'))
		apostrophe(&str, count_sep(num));
	if (flag.prc != -1)
		precision_num(&str, flag.prc, num);
	if (flag.width && flag.zero && flag.prc == -1 && !flag.minus)
		width_num(&str, flag, mod);
	if (mod.s == 'p' || ((num > 0 && (flag.hash && (mod.s == 'x'
		|| mod.s == 'X')))) || (flag.hash && (mod.s == 'o' || mod.s == 'O')))
		hash_num(&str, mod, flag);
	if (flag.width)
		width_num(&str, flag, mod);
	if (mod.s == 'X')
		make_toupper(&str);
	return (str);
}

void	make_toupper(char **str)
{
	char	*s;
	int		i;

	s = *str;
	i = 0;
	while (s[i])
	{
		s[i] = ft_toupper(s[i]);
		i++;
	}
}

void	hash_num(char **str, t_size mod, t_flags flag)
{
	char	*s;

	s = *str;
	if (mod.s == 'x' || mod.s == 'X' || mod.s == 'p')
	{
		if (flag.prc == -1 && s[0] == '0' && ft_strlen(s) > 1)
		{
			if (s[1] == '0')
				s[1] = 'x';
			else
			{
				s[0] = 'x';
				*str = ft_strjoin("0", s);
			}
		}
		else
			*str = ft_strjoin("0x", s);
	}
	if ((mod.s == 'o' || mod.s == 'O') && s[0] != '0')
		*str = ft_strjoin("0", s);
	if (ft_strequ(*str, s) == 0)
		ft_strdel(&s);
}

void	precision_num(char **str, int prc, unsigned long long num)
{
	char	*s;
	char	*s_new;
	int		len;
	int		i;

	s = *str;
	s_new = (!prc && !num) ? ft_strdup("") : NULL;
	len = ft_strlen(s);
	i = 0;
	if (prc > len)
	{
		s_new = ft_strnew(prc);
		while (i < prc - len)
		{
			s_new[i] = '0';
			i++;
		}
		s_new = ft_strcat(s_new, s);
	}
	if (s_new)
	{
		*str = s_new;
		ft_strdel(&s);
	}
}

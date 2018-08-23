/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   width_num.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 21:01:02 by ydeineha          #+#    #+#             */
/*   Updated: 2018/03/16 21:01:04 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	width_num(char **str, t_flags flag, t_size mod)
{
	char	*s;
	int		len;

	s = *str;
	len = ft_strlen(s);
	if (len == 0 && (mod.s == 'c' || mod.s == 'C'))
		len++;
	if (flag.width > len)
	{
		*str = minus_zero_num(s, len, flag, mod);
		ft_strdel(&s);
	}
}

char	*minus_zero_num(char *str, int len, t_flags flag, t_size mod)
{
	char	*s_new;

	s_new = ft_strnew(flag.width);
	if (!s_new)
		return (NULL);
	if (flag.minus && !ft_strlen(str) && (mod.s == 'c' || mod.s == 'C'))
		s_new = ft_memset(s_new, ' ', flag.width - len);
	else if (flag.minus)
	{
		ft_strcpy(s_new, str);
		ft_memset(&s_new[len], ' ', flag.width - len);
		return (s_new);
	}
	else
	{
		if ((flag.zero && flag.prc == -1 && mod.type == T_INT) ||
			(flag.zero && mod.type == T_CHR) ||
			(flag.zero && (mod.type == T_PTR || mod.type == T_OTHER)))
			s_new = ft_memset(s_new, '0', flag.width - len);
		else
			s_new = ft_memset(s_new, ' ', flag.width - len);
	}
	ft_strcpy(&s_new[flag.width - len], str);
	return (s_new);
}

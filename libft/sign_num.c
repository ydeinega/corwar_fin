/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sign_num.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 20:55:06 by ydeineha          #+#    #+#             */
/*   Updated: 2018/03/16 20:55:08 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	sign_num(char **str, int sign, t_flags flag)
{
	char	*s;

	s = *str;
	if (sign < 0)
	{
		if (s[0] == '0' && ft_isalnum(s[1]) && flag.prc == -1)
			s[0] = '-';
		else
			*str = ft_strjoin("-", s);
	}
	else if (flag.sp && !flag.plus)
	{
		if (s[0] == '0' && ft_isalnum(s[1]) && flag.prc == -1)
			s[0] = ' ';
		else
			*str = ft_strjoin(" ", s);
	}
	else if (flag.plus)
	{
		if (s[0] == '0' && ft_isalnum(s[1]) && flag.prc == -1)
			s[0] = '+';
		else
			*str = ft_strjoin("+", s);
	}
	ft_strequ(s, *str) ? 0 : ft_strdel(&s);
}

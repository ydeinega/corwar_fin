/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nonvalid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 19:44:10 by ydeineha          #+#    #+#             */
/*   Updated: 2018/03/22 19:44:13 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		nonvalid(t_flags flag, t_size mod)
{
	char	*str;
	int		n;

	str = ft_strnew(1);
	n = 0;
	if (!str)
		return (0);
	str[0] = mod.s;
	if (flag.width)
		width_num(&str, flag, mod);
	if (!str)
		return (0);
	n = ft_strlen(str);
	write(1, str, n);
	ft_strdel(&str);
	return (n);
}

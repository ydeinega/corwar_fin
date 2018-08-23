/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 18:52:22 by ydeineha          #+#    #+#             */
/*   Updated: 2017/10/31 19:12:46 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_atoi(const char *str)
{
	int				i;
	unsigned long	result;
	int				sign;

	i = 0;
	sign = 1;
	result = 0;
	while (ft_isspace(str[i]) == 1 && str[i] != '\0')
		i++;
	if (str[i] == '-' && ft_isdigit(str[i + 1]) > 0)
		sign = -1;
	if ((str[i] == '+' || str[i] == '-') && ft_isdigit(str[i + 1]) > 0)
		i++;
	while (ft_isdigit(str[i]) > 0)
	{
		result = 10 * result + str[i] - '0';
		i++;
	}
	if (result >= 9223372036854775807 && sign == 1)
		return (-1);
	else if (result > 9223372036854775807 && sign == -1)
		return (0);
	else
		return ((int)(sign * result));
}

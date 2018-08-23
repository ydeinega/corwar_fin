/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_flag.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/31 20:32:57 by ydeineha          #+#    #+#             */
/*   Updated: 2018/01/31 20:33:13 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		dollar_arg(char *fmt)
{
	int i;
	int ret;
	int start;

	i = 0;
	ret = 0;
	while (fmt[i])
	{
		if (ft_isdigit(fmt[i]) && (i == 0 || fmt[i - 1] != '*'))
		{
			start = i;
			while (ft_isdigit(fmt[i]))
				i++;
			if (fmt[i] == '$')
				ret = dollar_value(&fmt[start]);
		}
		i++;
	}
	return (ret);
}

int		dollar_width(char *fmt)
{
	int i;
	int ret;

	i = 0;
	ret = 0;
	while (fmt[i])
	{
		if (fmt[i] == '*' && (i == 0 || fmt[i - 1] != '.'))
		{
			ret = dollar_value(&fmt[i + 1]);
			break ;
		}
		i++;
	}
	return (ret);
}

int		dollar_precision(char *fmt)
{
	int i;
	int ret;

	i = 0;
	ret = 0;
	while (fmt[i])
	{
		if (fmt[i] == '*' && i > 0 && fmt[i - 1] == '.')
		{
			ret = dollar_value(&fmt[i + 1]);
			break ;
		}
		i++;
	}
	return (ret);
}

int		dollar_value(char *str)
{
	int i;
	int	ret;

	i = 0;
	ret = 0;
	if (!str)
		return (0);
	while (ft_isdigit(str[i]))
		i++;
	if (str[i] == '$')
		ret = ft_atoi(str);
	return (ret);
}

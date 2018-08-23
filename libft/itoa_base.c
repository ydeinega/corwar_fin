/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 18:52:57 by ydeineha          #+#    #+#             */
/*   Updated: 2018/03/16 18:53:00 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*itoa_base(unsigned long long num, unsigned long long base)
{
	int					n;
	unsigned long long	mod;
	char				*str;

	n = count_digits(num, base);
	str = ft_strnew(n);
	if (!str)
		return (NULL);
	n--;
	if (num == 0)
		str[0] = '0';
	while (num > 0)
	{
		mod = num % base;
		str[n] = make_char(mod);
		n--;
		num = num / base;
	}
	return (str);
}

int					count_digits(unsigned long long num,
					unsigned long long base)
{
	int n;

	n = 1;
	while (num / base > 0)
	{
		n++;
		num = num / base;
	}
	return (n);
}

char				make_char(unsigned long long num)
{
	char				ret;
	unsigned long long	i;

	i = 10;
	ret = 'a';
	if (num < 10)
		ret = num + '0';
	else
	{
		while (i < num)
		{
			ret++;
			i++;
		}
	}
	return (ret);
}

unsigned long long	u_num(long long num)
{
	if (num < 0)
		return ((unsigned long long)(-num));
	return ((unsigned long long)num);
}

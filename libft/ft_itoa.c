/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 12:38:45 by ydeineha          #+#    #+#             */
/*   Updated: 2017/11/08 13:19:41 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		count_dgts(int n)
{
	int digits;

	digits = 0;
	if (n < 0)
	{
		digits++;
		n = -n;
	}
	while ((n / 10) != 0)
	{
		digits++;
		n = n / 10;
	}
	return (digits + 1);
}

static char		*make_string(char *s, int len, int n)
{
	if (n < 0)
	{
		s[0] = '-';
		if (n == -2147483648)
		{
			s[len] = '8';
			n = n / (-10);
			len--;
		}
		else
			n = -n;
	}
	if (n == 0)
		s[len] = '0';
	else
	{
		while (n > 0)
		{
			s[len] = n % 10 + '0';
			len--;
			n = n / 10;
		}
	}
	return (s);
}

char			*ft_itoa(int n)
{
	char	*ptr;
	int		i;

	i = count_dgts(n) - 1;
	ptr = ft_strnew(count_dgts(n));
	if (ptr != NULL)
	{
		ptr = make_string(ptr, i, n);
	}
	return (ptr);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_mod.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmalyavc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 17:41:39 by rmalyavc          #+#    #+#             */
/*   Updated: 2018/01/15 14:33:20 by rmalyavc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "visu.h"

static int	define_len(intmax_t n, int base)
{
	int		counter;

	if (base < 2 || base > 16)
		return (-1);
	counter = 1;
	while (n / base != 0)
	{
		n /= base;
		counter++;
	}
	if (n < 0)
		counter++;
	return (counter);
}

static char	*ft_format(char *str, int base)
{
	int		len;
	int		i;
	char	*buffer;

	i = -1;
	if (base == 2 && (len = ft_strlen(str)))
	{
		if (len % 8 != 0)
			len = ft_strlen(str) + (8 - ft_strlen(str) % 8);
		if (!(buffer = ft_strnew(len)))
			return (NULL);
		ft_memset(buffer, '0', len - ft_strlen(str));
		ft_strcat(buffer, str);
	}
	else if (base == 16 && (len = ft_strlen(str) + 2))
	{
		if (!(buffer = ft_strnew(len)))
			return (NULL);
		ft_strcat(buffer, "0x");
		ft_strcat(buffer, str);
	}
	else
		return (str);
	ft_strdel(&str);
	return (buffer);
}

static void	fill_res(char *res, int len)
{
	int		i;

	i = -1;
	while ((ft_isdigit(res[++i]) == 0 || res[i] == '0') && i < len)
		if (res[i] != '-')
			res[i] = '0';
}

char		*ft_itoa_base_mod(intmax_t nb, int base, int flag)
{
	char			*res;
	int				len;
	char			buffer[17];

	ft_strcpy(buffer, "0123456789ABCDEF");
	if ((len = define_len(nb, base)) < flag)
		len = flag;
	if (!(res = ft_strnew(len)))
		return (NULL);
	if (nb == INTMAX_MIN && (res[--len] = buffer[nb % base * -1]))
		nb /= base;
	if (nb < 0)
	{
		res[0] = '-';
		nb = -nb;
	}
	while (nb != 0 && (res[--len] = buffer[nb % base]))
		nb /= base;
	if (res[0] == '\0')
		res[0] = '0';
	if (flag == -1)
		res = ft_format(res, base);
	else if (flag > 1)
		fill_res(res, len);
	return (res);
}

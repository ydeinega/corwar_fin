/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_hex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 17:32:52 by ydeineha          #+#    #+#             */
/*   Updated: 2018/09/07 17:32:54 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static char			*str_itoa_base(unsigned char num,
					unsigned char base, int len)
{
	int		i;
	char	*str;

	i = len;
	str = ft_strnew(len);
	while (--i >= 0)
	{
		str[i] = HEX[num % base];
		num = num / base;
	}
	return (str);
}

static unsigned int	ft_atoi_base(char *str, long long base)
{
	int				i;
	int				len;
	long long		result;

	i = 0;
	result = 0;
	len = ft_strlen(str);
	while (ft_isspace(str[i]) == 1 && str[i] != '\0')
		i++;
	while (len > i)
	{
		result = (base * result) + ((ft_strchr(HEX, str[i]) - HEX));
		i++;
	}
	if (result > 4294967295)
		return (0);
	return ((unsigned int)(result));
}

static char			*hex_line(unsigned char *line, int length)
{
	int		i;
	char	*hex;
	char	*tmp;

	i = 0;
	hex = NULL;
	tmp = NULL;
	if (line[i] == '0')
		i++;
	hex = str_itoa_base(line[i], 16, 2);
	while (++i < length)
	{
		tmp = str_itoa_base(line[i], 16, 2);
		hex = ft_strljoin(&hex, &tmp);
	}
	return (hex);
}

unsigned int		conv_hex(unsigned char *line, int length)
{
	int				i;
	char			*hex;
	unsigned int	ret;

	i = 0;
	hex = NULL;
	if (!(hex = hex_line(line, length)))
		return (0);
	ret = ft_atoi_base(hex, 16);
	ft_strdel(&hex);
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strljoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 21:28:44 by ydeineha          #+#    #+#             */
/*   Updated: 2018/09/05 21:28:47 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

char		*ft_strljoin(char **s1, char **s2)
{
	char	*without_leaks;

	without_leaks = NULL;
	if (!s1 && !s2)
		return (NULL);
	else if (!*s1 && *s2)
	{
		without_leaks = *s2;
		*s2 = NULL;
	}
	else if (!*s2 && *s1)
	{
		without_leaks = *s1;
		*s1 = NULL;
	}
	else
	{
		without_leaks = ft_strjoin(*s1, *s2);
		ft_strdel(s1);
		ft_strdel(s2);
	}
	return (without_leaks);
}

static char		*str_itoa_base(unsigned char num, unsigned char base, int len)
{
	int 	i;
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

unsigned int	ft_atoi_base(char *str, long long base)
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

char			*hex_line(unsigned char *line, int length)
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

unsigned int	conv_hex(unsigned char *line, int length)
{
	int		i;
	char	*hex;
	unsigned int	ret;

	i = 0;
	hex = NULL;
	if (!(hex = hex_line(line, length)))
		return (0);
	ret = ft_atoi_base(hex, 16);
	ft_strdel(&hex);
	return (ret);
}

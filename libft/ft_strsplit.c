/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:34:04 by ydeineha          #+#    #+#             */
/*   Updated: 2017/11/15 15:30:07 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int i;
	int	words;

	i = 0;
	words = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
		{
			words++;
		}
		i++;
	}
	return (words);
}

static int	count_letters(char const *s, char c)
{
	int	i;
	int letters;

	i = 0;
	letters = 0;
	while (s[i] != c && s[i] != '\0')
	{
		i++;
		letters++;
	}
	return (letters);
}

static void	array_del(char **s, int i)
{
	while (i >= 0)
	{
		ft_strdel(&s[i]);
		i--;
	}
}

static char	**split_words(char **dst, char const *src, char del)
{
	int		i;
	int		j;
	int		k;
	int		end;

	i = 0;
	j = 0;
	end = count_words(src, del);
	while (i < end)
	{
		while (src[j] == del)
		{
			j++;
		}
		k = count_letters(&src[j], del);
		dst[i] = ft_strsub(src, j, k);
		if (dst[i] == NULL)
		{
			array_del(&dst[i], i);
			return (NULL);
		}
		j = j + k;
		i++;
	}
	return (dst);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**ptr;
	int		end;

	ptr = NULL;
	if (s != NULL)
	{
		end = count_words(s, c);
		ptr = (char **)malloc(sizeof(char*) * (end + 1));
		if (ptr != NULL)
		{
			ptr[end] = NULL;
			ptr = split_words(ptr, s, c);
		}
	}
	return (ptr);
}

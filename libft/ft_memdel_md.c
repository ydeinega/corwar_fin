/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdel_md.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 23:06:08 by ydeineha          #+#    #+#             */
/*   Updated: 2017/11/17 23:06:11 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_memdel_md(void **ptr, size_t size)
{
	char	**tmp;
	size_t	i;

	tmp = NULL;
	i = 0;
	if (ptr)
	{
		tmp = (char **)ptr;
		while (i < size)
		{
			ft_memdel((void **)&tmp[i]);
			i++;
		}
		ft_memdel((void **)&ptr);
	}
}

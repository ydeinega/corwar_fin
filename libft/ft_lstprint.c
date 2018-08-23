/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 16:12:36 by ydeineha          #+#    #+#             */
/*   Updated: 2017/11/17 16:15:14 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstprint(t_list **alst)
{
	t_list	*head;
	size_t	i;
	char	*tmp;

	i = 0;
	head = NULL;
	if (alst)
	{
		head = *alst;
		while (head)
		{
			tmp = (char *)(head->content);
			while (i < (head->content_size - 1))
			{
				ft_putchar(tmp[i]);
				i++;
			}
			ft_putchar('\n');
			i = 0;
			head = head->next;
		}
	}
	else
		ft_putstr("null\n");
}

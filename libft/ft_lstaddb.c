/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstaddb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 14:11:00 by ydeineha          #+#    #+#             */
/*   Updated: 2017/11/17 14:11:48 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstaddb(t_list **alst, t_list *new)
{
	t_list	*head;

	head = NULL;
	if (alst && new)
	{
		head = *alst;
		while (head->next)
		{
			head = head->next;
		}
		head->next = new;
	}
}

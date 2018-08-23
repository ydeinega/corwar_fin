/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 16:19:36 by ydeineha          #+#    #+#             */
/*   Updated: 2017/11/14 16:34:59 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_lstfree(t_list *lst)
{
	t_list *head;

	head = lst;
	while (head)
	{
		free(head);
		head = head->next;
	}
}

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*head;
	t_list	*new;
	t_list	*tmp;

	head = lst;
	if (head != NULL)
	{
		new = f(head);
		head = head->next;
		tmp = new;
	}
	while (head)
	{
		tmp->next = f(head);
		head = head->next;
		if (tmp->next)
			tmp = tmp->next;
		else
		{
			ft_lstfree(new);
			return (NULL);
		}
	}
	return (new);
}

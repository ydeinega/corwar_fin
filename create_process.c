/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 21:28:10 by ydeineha          #+#    #+#             */
/*   Updated: 2018/09/05 21:28:14 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_process	*create_process(t_player *player)
{
	int			i;
	t_process	*proc;
	t_process	*tmp;

	i = 0;
	proc = NULL;
	tmp = NULL;
	while (i < g_game.players)
	{
		tmp = new_process(&player[i], NULL, player[i].start);
		tmp->col = -1;
		add_process(&proc, tmp);
		i++;
	}
	return (proc);
}

void		add_process(t_process **head, t_process *new)
{
	t_process *tmp;

	tmp = NULL;
	if (head && new)
	{
		tmp = *head;
		new->next = tmp;
		*head = new;
	}
}

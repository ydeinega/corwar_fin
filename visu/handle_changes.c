/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_changes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmalyavc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 20:31:02 by rmalyavc          #+#    #+#             */
/*   Updated: 2018/09/06 21:00:00 by rmalyavc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

static t_chlist		*chlist_create(t_change *changes)
{
	t_chlist		*elem;

	if (!(elem = (t_chlist *)malloc(sizeof(t_chlist))))
		return (NULL);
	elem->list = changes;
	elem->counter = 0;
	elem->next = NULL;
	return (elem);
}

static void			push_chlist(t_chlist *chlist)
{
	t_chlist		*curr;

	if (!(curr = g_game.chlist))
	{
		g_game.chlist = chlist;
		return ;
	}
	while (curr->next)
		curr = curr->next;
	curr->next = chlist;
}

static void			del_elem(t_chlist **elem)
{
	t_chlist		*curr;
	t_chlist		*prev;

	prev = NULL;
	if (!*elem || !(curr = g_game.chlist))
		return ;
	while (curr)
	{
		if (curr == *elem)
		{
			if (prev == NULL && ((g_game.chlist = curr->next) || 1))
			{
				curr->next = NULL;
				free(curr);
				return ;
			}
			prev->next = curr->next;
			curr->next = NULL;
			free(curr);
			return ;
		}
		curr = curr->next;
	}
	*elem = NULL;
}

static void			draw_changes(WINDOW *win, t_change **change, bool to_free)
{
	t_change		*curr;
	t_change		*prev;
	int				i;
	int				tmp;

	curr = *change;
	while ((prev = curr))
	{
		i = -1;
		tmp = -1;
		while (++i < curr->len)
		{
			tmp == -1 ? tmp = curr->pos % MEM_SIZE : true;
			write_value(curr->player, curr->value[i], tmp, win);
			tmp = (tmp + 1) % MEM_SIZE;
		}
		curr = curr->next;
		if (to_free)
		{
			free(prev->value);
			free(prev);
		}
	}
	if (to_free)
		*change = NULL;
}

void				handle_changes(void)
{
	t_chlist		*curr;
	t_chlist		*tmp;

	tmp = NULL;
	push_chlist(chlist_create(g_game.change));
	g_game.change = NULL;
	if (!(curr = g_game.chlist))
		return ;
	while (curr)
	{
		wattroff(g_game.win, A_BOLD);
		if (curr->counter == 0)
		{
			wattron(g_game.win, A_BOLD);
			draw_changes(g_game.win, &curr->list, false);
		}
		else if (curr->counter == 10 && ((tmp = curr) || 1))
			draw_changes(g_game.win, &curr->list, true);
		curr->counter++;
		curr = curr->next;
		if (tmp)
			del_elem(&tmp);
	}
}

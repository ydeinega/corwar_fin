/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verb_del.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgonor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 18:06:43 by dgonor            #+#    #+#             */
/*   Updated: 2018/07/20 18:06:46 by dgonor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "verbosity.h"

void					initialize_verb(void)
{
	g_verb.cycle = 0;
	g_verb.ctd = 0;
	g_verb.op = NULL;
	g_verb.pc = NULL;
	g_verb.death = NULL;
}

static void					verb_del_op(t_list_op **del)
{
	t_list_op	*tmp;

	tmp = NULL;
	if (del && *del)
	{
		while (*del)
		{
			(*del)->arg_num = 0;
			(*del)->opcode = 0;
			(*del)->proc_num = 0;
			if ((*del)->arg_type)
				free((*del)->arg_type);
			if ((*del)->arg)
				free((*del)->arg);
			tmp = *del;
			free(tmp);
			*del = (*del)->next;
		}
		del = NULL;
	}
}

static void					verb_del_pc(t_list_pc **del)
{
	t_list_pc	*tmp;

	tmp = NULL;
	if (del && *del)
	{
		while (*del)
		{
			(*del)->pc_prev = 0;
			(*del)->pc_new = 0;
			(*del)->move = 0;
			if ((*del)->line)
				free((*del)->line);
			tmp = *del;
			free(tmp);
			*del = (*del)->next;
		}
		del = NULL;
	}
}

static void					verb_del_death(t_list_death **del)
{
	t_list_death	*tmp;

	tmp = NULL;
	if (del && *del)
	{
		while (*del)
		{
			(*del)->proc_num = 0;
			(*del)->cycles_not_live = 0;
			tmp = *del;
			free(tmp);
			*del = (*del)->next;
		}
		del = NULL;
	}
}

void					start_verb(void)
{
	if (g_verb.op)
		verb_del_op(&g_verb.op);
	if (g_verb.pc)
		verb_del_pc(&g_verb.pc);
	if (g_verb.death)
		verb_del_death(&g_verb.death);

}

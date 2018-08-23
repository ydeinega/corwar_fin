/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verb_deths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgonor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 15:53:42 by dgonor            #+#    #+#             */
/*   Updated: 2018/07/20 15:53:45 by dgonor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "verbosity.h"

static void			lstback_deth_list(t_list_death **lst, t_list_death *add)
{
	t_list_death	*tmp;

	tmp = NULL;
	if (lst && *lst && add)
	{
		tmp = *lst;
		while (tmp->next)
		{
			tmp = tmp->next;
		}
		tmp->next = add;
	}
}

static t_list_death	*create_deth_list(int proc_num, int cycles_not_live)
{
	t_list_death	*new;

	if (!(new = (t_list_death*)malloc(sizeof(t_list_death) * 1)))
		return (NULL);
	new->proc_num = proc_num;
	new->cycles_not_live = cycles_not_live;
	new->next = NULL;
	return (new);
}

void	verb_add_death(int proc_num, int cycles_not_live)
{
//		Инфа выводится в след порядке
//		Process 29 hasn't lived for 1460 cycles (CTD 986)
//		Process 9 hasn't lived for 1026 cycles (CTD 986)
//		Process 6 hasn't lived for 1909 cycles (CTD 986)
	if (!g_verb.death)
		g_verb.death = create_deth_list(proc_num, cycles_not_live);
	else
		lstback_deth_list(&g_verb.death, create_deth_list(proc_num, cycles_not_live));

}
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
		add_process(&proc, tmp);
		i++;
	}
	return (proc);
}

static void	set_register(unsigned int *dst,
							t_player *player, t_process *proc)
{
	if (proc)
		regcpy(dst, proc->reg, REG_NUMBER);
	else
	{
		regset(dst, 0, REG_NUMBER);
		dst[0] = (unsigned int)(~(player->num) + 1);
	}
}

t_process	*new_process(t_player *player, t_process *proc, int pc)
{
	t_process	*new;

	if (!(new = (t_process *)malloc(sizeof(t_process))))
	{
		perror("malloc() in new_process() failed ");
		error(-1);
	}
	new->num = ++g_game.proc_num;
	new->player = player ? player->num : proc->player;
	new->carry = player ? 0 : proc->carry;
	new->live = 1;
	new->lives_ctd = player ? 0 : proc->lives_ctd;
	new->pc = pc;
	new->pc_change = proc ? 1 : 0;
	new->prev = -1;
	new->cycles_not_live = player ? 0 : proc->cycles_not_live;
	new->opcode = proc ? 0 : conv_hex(&g_game.board[pc], 1);
	if (player && (new->opcode >= 1 && new->opcode <= 16))
		new->cycles_to_exec = op_tab[new->opcode - 1].cycles_to_exec;
	else
		new->cycles_to_exec = 0;
	new->next = NULL;
	set_register(new->reg, player, proc);
	return (new);
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

void		regcpy(unsigned int *dst, unsigned int *src, int len)
{
	int i;

	i = -1;
	while (++i < len)
		dst[i] = src[i];
}

void		regset(unsigned int *dst, unsigned int c, int len)
{
	int i;

	i = -1;
	while (++i < len)
		dst[i] = c;
}

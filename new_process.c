/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 21:06:31 by ydeineha          #+#    #+#             */
/*   Updated: 2018/09/06 21:06:32 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	regcpy(unsigned int *dst, unsigned int *src, int len)
{
	int i;

	i = -1;
	while (++i < len)
		dst[i] = src[i];
}

static void	regset(unsigned int *dst, unsigned int c, int len)
{
	int i;

	i = -1;
	while (++i < len)
		dst[i] = c;
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
		new->cycles_to_exec = g_op_tab[new->opcode - 1].cycles_to_exec;
	else
		new->cycles_to_exec = 0;
	new->next = NULL;
	set_register(new->reg, player, proc);
	return (new);
}

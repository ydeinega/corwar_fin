/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_processes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 21:31:44 by ydeineha          #+#    #+#             */
/*   Updated: 2018/09/05 21:31:47 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

funcptr	g_command[16] =
{
	exec_live,
	exec_ld,
	exec_st,
	exec_add,
	exec_sub,
	exec_and,
	exec_or,
	exec_xor,
	exec_zjmp,
	exec_ldi,
	exec_sti,
	exec_fork,
	exec_lld,
	exec_lldi,
	exec_lfork,
	exec_aff
};

void	read_next_pc(t_process *proc, int move, int base)
{
	proc->prev = proc->pc;
	proc->pc_change = 1;
	if (proc->opcode == 9 && proc->carry)
		proc->pc = (proc->pc + ((short)move % base)) % MEM_SIZE;
	else
		proc->pc = (proc->pc + move) % base;
	if (proc->pc < 0)
		proc->pc = MEM_SIZE + proc->pc;
	if (g_game.v && !g_game.visu
		&& proc->opcode >= 1 && proc->opcode <= 16)
	{
		if (proc->opcode == 9 && !proc->carry)
			verb_print_pc(proc->prev, proc->pc, move, g_game.board);
		if (proc->opcode != 9)
			verb_print_pc(proc->prev, proc->pc, move, g_game.board);
	}
}

void	read_next_instruct(t_process *proc)
{
	unsigned int	code;

	code = conv_hex(&g_game.board[proc->pc], 1);
	if (code >= 1 && code <= 16)
	{
		proc->opcode = code;
		proc->cycles_to_exec = g_op_tab[code - 1].cycles_to_exec;
	}
	else
		proc->opcode = 0;
}

void	run_processes(void)
{
	t_process	*tmp;

	tmp = g_game.proc;
	while (tmp)
	{
		if (tmp->live)
		{
			tmp->cycles_not_live++;
			if (tmp->live && tmp->pc_change)
			{
				tmp->pc_change = 0;
				read_next_instruct(tmp);
			}
			if (tmp->opcode >= 1 && tmp->opcode <= 16)
			{
				tmp->cycles_to_exec--;
				if (tmp->cycles_to_exec == 0)
					exec_instruct(tmp);
			}
			else
				read_next_pc(tmp, 1, MEM_SIZE);
		}
		tmp = tmp->next;
	}
}

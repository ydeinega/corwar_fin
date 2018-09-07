/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruct_9_12.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 18:30:10 by ydeineha          #+#    #+#             */
/*   Updated: 2018/09/07 18:30:12 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	exec_zjmp(t_process *process, unsigned int *arg, t_arg_type *arg_type)
{
	if (process && arg && arg_type)
		return ;
}

void	exec_ldi(t_process *process, unsigned int *arg, t_arg_type *arg_type)
{
	unsigned int	res;
	int				delta;
	int				arg_1;
	int				arg_2;
	int				dst;

	res = 0;
	delta = 0;
	dst = arg[2];
	arg_1 = arg_fin(process, arg[0], arg_type[0]);
	arg_2 = arg_fin(process, arg[1], arg_type[1]);
	if (arg_type[0] == T_DIR && arg_type[1] == T_DIR)
		delta = (short)arg_1 + (short)arg_2;
	else if (arg_type[0] == T_DIR)
		delta = (short)arg_1 + arg_2;
	else if (arg_type[1] == T_DIR)
		delta = arg_1 + (short)arg_2;
	else
		delta = arg_1 + arg_2;
	res = extract_ind(process, delta, IDX_MOD);
	process->reg[dst - 1] = res;
}

void	exec_sti(t_process *process, unsigned int *arg, t_arg_type *arg_type)
{
	int				value;
	int				delta;
	int				arg_2;
	int				arg_3;

	value = arg_fin(process, arg[0], arg_type[0]);
	arg_2 = arg_fin(process, arg[1], arg_type[1]);
	arg_3 = arg_fin(process, arg[2], arg_type[2]);
	if (arg_type[1] == T_DIR && arg_type[2] == T_DIR)
		delta = (short)arg_2 + (short)arg_3;
	else if (arg_type[1] == T_DIR)
		delta = (short)arg_2 + arg_3;
	else if (arg_type[2] == T_DIR)
		delta = arg_2 + (short)arg_3;
	else
		delta = arg_2 + arg_3;
	store_value(process, value, delta, IDX_MOD);
}

void	exec_fork(t_process *process, unsigned int *arg, t_arg_type *arg_type)
{
	int			delta;
	int			pc;
	t_process	*new;

	new = NULL;
	delta = arg_fin(process, arg[0], arg_type[0]);
	pc = (process->pc + ((short)delta % IDX_MOD)) % MEM_SIZE;
	if (pc < 0)
		pc += MEM_SIZE;
	new = new_process(NULL, process, pc);
	add_process(&(g_game.proc), new);
}

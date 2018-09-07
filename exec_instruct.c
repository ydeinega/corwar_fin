/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_instruct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 19:00:54 by ydeineha          #+#    #+#             */
/*   Updated: 2018/09/07 19:00:56 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static t_arg_type	*get_arg_type(t_process *proc)
{
	t_arg_type		*arg_type;
	t_op			op;

	arg_type = NULL;
	op = g_op_tab[proc->opcode - 1];
	if (op.codage)
		arg_type = get_codage(proc, op.arg_num);
	else
	{
		arg_type = ft_strnew(op.arg_num);
		ft_memcpy(arg_type, op.arg, op.arg_num);
	}
	return (arg_type);
}

static bool			arg_valid(t_arg_type *arg_type,
					unsigned int *arg, int arg_num)
{
	int i;

	i = 0;
	while (i < arg_num)
	{
		if (arg_type[i] == T_REG &&
			(arg[i] == 0 || arg[i] > 16))
			return (0);
		i++;
	}
	return (1);
}

void				exec_instruct(t_process *proc)
{
	t_arg_type		*arg_type;
	int				move;
	unsigned int	*arg;
	t_op			op;
	int				base;

	op = g_op_tab[proc->opcode - 1];
	arg_type = get_arg_type(proc);
	arg = NULL;
	base = (proc->opcode == 9 && proc->carry) ? IDX_MOD : MEM_SIZE;
	if (!op.codage || (op.codage && codage_valid(arg_type, op.arg, op.arg_num)))
	{
		arg = extract_arg(op, proc->pc, arg_type);
		if (arg_valid(arg_type, arg, op.arg_num))
		{
			if (g_game.v && !g_game.visu && proc->opcode != 16)
				verb_print_op(proc, arg_type, arg);
			g_command[proc->opcode - 1](proc, arg, arg_type);
		}
	}
	move = get_move(proc, arg_type, arg);
	read_next_pc(proc, move, base);
	arg_type ? free(arg_type) : 0;
	arg ? free(arg) : 0;
}

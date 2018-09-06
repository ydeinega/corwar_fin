/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_arg.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 21:28:22 by ydeineha          #+#    #+#             */
/*   Updated: 2018/09/05 21:28:24 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int		get_length(t_arg_type arg_type, t_op op)
{
	int	length;

	length = 0;
	if (arg_type == T_REG)
		length = 1;
	else if (arg_type == T_DIR)
		length = op.label;
	else if (arg_type == T_IND)
		length = IND_SIZE;
	return (length);
}

unsigned int	*extract_arg(t_op op, int pc, t_arg_type *arg_type)
{
	int				i;
	int				length;
	int				pc_copy;
	unsigned int	*arg;

	i = 0;
	length = 0;
	pc_copy = pc;
	pc = op.codage ? (pc + 2) % MEM_SIZE : (pc + 1) % MEM_SIZE;
	if (!(arg = (unsigned int *)malloc(sizeof(unsigned int) * op.arg_num)))
	{
		perror("malloc() in extract_arg() failed ");
		error(-1);
	}
	while (i < op.arg_num)
	{
		length = arg_type ? get_length(arg_type[i], op) : op.label;
		arg[i] = read_from_board(pc, length);
		i++;
		pc = (pc + length) % MEM_SIZE;
	}
	return (arg);
}

unsigned int	arg_fin(t_process *process, unsigned int arg,
						t_arg_type arg_type)
{
	unsigned int	res;
	unsigned int	base;

	res = 0;
	base = IDX_MOD;
	if (arg_type == T_REG)
		res = process->reg[arg - 1];
	else if (arg_type == T_DIR)
		res = arg;
	else if (arg_type == T_IND)
	{
		if (process->opcode == 13)
			base = 0;
		res = extract_ind(process, (short)arg, (short)base);
	}
	return (res);
}

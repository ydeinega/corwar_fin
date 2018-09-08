/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verb_prt_op_arg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 12:28:08 by ydeineha          #+#    #+#             */
/*   Updated: 2018/09/08 12:28:10 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "verbosity.h"

static void		verb_prt_op_comm_sti(t_process *proc, unsigned int *arg,
									t_arg_type *arg_type)
{
	int		delta;
	int		new_pc;
	int		i;

	i = 0;
	delta = 0;
	ft_printf("\n%8| -> store to ");
	while (++i < 3)
	{
		if (arg_type[i] == T_REG || arg_type[i] == T_IND)
		{
			ft_printf("%i", (int)arg_fin(proc, arg[i], arg_type[i]));
			delta += arg_fin(proc, arg[i], arg_type[i]);
		}
		else if (arg_type[i] == T_DIR)
		{
			ft_printf("%hi", (short)arg[i]);
			delta += (short)arg[i];
		}
		if (i == 1)
			ft_printf(" + ");
	}
	new_pc = proc->pc + (delta % IDX_MOD);
	ft_printf(" = %i (with pc and mod %i)", delta, new_pc);
}

static void		verb_prt_op_comm_ldi(t_process *proc, unsigned int *arg,
									t_arg_type *arg_type)
{
	int		delta;
	int		new_pc;
	int		i;

	i = -1;
	delta = 0;
	ft_printf("\n%8| -> load from ");
	while (++i < 2)
	{
		if (arg_type[i] == T_REG)
		{
			ft_printf("%i", (int)(arg_fin(proc, arg[i], arg_type[i])));
			delta += arg_fin(proc, arg[i], arg_type[i]);
		}
		else
		{
			ft_printf("%hi", (short)arg[i]);
			delta += (short)arg[i];
		}
		if (i == 0)
			ft_printf(" + ");
	}
	new_pc = proc->pc + (delta % IDX_MOD);
	ft_printf(" = %i (with pc and mod %i)", delta, new_pc);
}

static void		verb_prt_reg(t_process *proc, t_arg_type *arg_type,
								unsigned int *arg, int i)
{
	t_op	op;

	op = g_op_tab[proc->opcode - 1];
	if (op.arg[i] == T_REG)
	{
		ft_printf("r");
		ft_printf("%i", arg[i]);
	}
	else
	{
		if (proc->opcode == 3)
			ft_printf("%i", arg[i]);
		else
			ft_printf("%i", (int)(arg_fin(proc, arg[i], arg_type[i])));
	}
}

static void		verb_prt_dir_ind(t_process *proc, t_arg_type *arg_type,
								unsigned int *arg, int i)
{
	t_op	op;

	op = g_op_tab[proc->opcode - 1];
	if (arg_type[i] == T_IND)
	{
		if (proc->opcode == 2 || (proc->opcode >= 6 &&
			proc->opcode <= 11))
			ft_printf("%i", (int)arg_fin(proc, arg[i], arg_type[i]));
		else
			ft_printf("%hi", (short)arg[i]);
	}
	else if (arg_type[i] == T_DIR && op.label == 2)
		ft_printf("%hi", (short)arg[i]);
	else
		ft_printf("%i", arg[i]);
}

void			verb_prt_op_arg(t_process *proc, t_arg_type *arg_type,
								unsigned int *arg)
{
	t_op	op;
	int		i;

	i = -1;
	op = g_op_tab[proc->opcode - 1];
	while (++i < op.arg_num)
	{
		ft_printf(" ");
		if (arg_type[i] == T_REG)
			verb_prt_reg(proc, arg_type, arg, i);
		else
			verb_prt_dir_ind(proc, arg_type, arg, i);
	}
	if (proc->opcode == 11)
		verb_prt_op_comm_sti(proc, arg, arg_type);
	if (proc->opcode == 10)
		verb_prt_op_comm_ldi(proc, arg, arg_type);
}

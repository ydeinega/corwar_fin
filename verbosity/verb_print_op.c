/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verb_print_op.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/08 12:05:41 by ydeineha          #+#    #+#             */
/*   Updated: 2018/09/08 12:05:44 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "verbosity.h"

void			verb_print_op(t_process *proc, t_arg_type *arg_type,
							unsigned int *arg)
{
	t_op	op;
	int		width;
	int		len;

	len = count_digits(proc->num, 10);
	width = len < 5 ? 4 : len;
	op = g_op_tab[proc->opcode - 1];
	if ((4 & g_game.number_v) > 0)
	{
		ft_printf("P%*i | %s", (width + 1), proc->num, op.op);
		verb_prt_op_arg(proc, arg_type, arg);
		if (op.opcode == 9 && proc->carry == 1)
			ft_printf(" OK");
		else if (op.opcode == 9 && proc->carry == 0)
			ft_printf(" FAILED");
		if (op.opcode == 12)
			ft_printf(" (%d)",
			((short)arg_fin(proc, arg[0], arg_type[0]) % IDX_MOD) + proc->pc);
		if (op.opcode == 15)
			ft_printf(" (%d)",
			((short)arg_fin(proc, arg[0], arg_type[0]) + proc->pc));
		ft_printf("\n");
	}
	if ((1 & g_game.number_v) > 0 && proc->opcode == 1)
		verb_print_lives((int)(*arg));
}

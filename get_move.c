/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 17:41:43 by ydeineha          #+#    #+#             */
/*   Updated: 2018/09/07 17:41:45 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			get_move(t_process *proc, t_arg_type *arg_type, unsigned int *arg)
{
	t_op	op;
	int		move;
	int		i;
	int		arg_num;

	i = 0;
	op = g_op_tab[proc->opcode - 1];
	move = op.codage ? 2 : 1;
	arg_num = op.arg_num;
	if (proc->opcode == 9 && proc->carry)
		return ((int)(*arg));
	if (arg_type)
	{
		while (i < arg_num)
		{
			if (arg_type[i] == T_REG)
				move++;
			else if (arg_type[i] == T_DIR)
				move += g_op_tab[proc->opcode - 1].label;
			else if (arg_type[i] == T_IND)
				move += IND_SIZE;
			i++;
		}
	}
	return (move);
}

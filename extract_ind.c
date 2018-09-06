/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_ind.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/06 18:55:00 by ydeineha          #+#    #+#             */
/*   Updated: 2018/09/06 18:55:03 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int		get_pc_new(t_process *process, int delta, int base)
{
	int		pc_new;

	pc_new = 0;
	if (base)
	{
		if (process->opcode != 10 && process->opcode != 14)
			pc_new = (process->pc + ((short)delta % base)) % MEM_SIZE;
		else
			pc_new = (process->pc + (delta % base)) % MEM_SIZE;
	}
	else
	{
		if (process->opcode != 10 && process->opcode != 14)
			pc_new = (process->pc + (short)delta) % MEM_SIZE;
		else
			pc_new = (process->pc + delta) % MEM_SIZE;
	}
	if (pc_new < 0)
		pc_new = MEM_SIZE + pc_new;
	return (pc_new);
}

unsigned int	extract_ind(t_process *process, int delta, int base)
{
	unsigned int	res;
	int				pc_new;

	pc_new = get_pc_new(process, delta, base);
	res = read_from_board(pc_new, 4);
	return (res);
}

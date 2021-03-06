/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruct_13_16.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/07 18:30:27 by ydeineha          #+#    #+#             */
/*   Updated: 2018/09/07 18:30:29 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void	exec_lld(t_process *process, unsigned int *arg, t_arg_type *arg_type)
{
	int		res;

	res = arg_fin(process, arg[0], arg_type[0]);
	process->reg[arg[1] - 1] = res;
	if (res == 0)
		process->carry = 1;
	else
		process->carry = 0;
}

void	exec_lldi(t_process *process, unsigned int *arg, t_arg_type *arg_type)
{
	unsigned int	res;
	int				delta;
	int				dst;
	int				arg_1;
	int				arg_2;

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
	res = extract_ind(process, delta, 0);
	process->reg[dst - 1] = res;
	if (res == 0)
		process->carry = 1;
	else
		process->carry = 0;
}

void	exec_lfork(t_process *process, unsigned int *arg, t_arg_type *arg_type)
{
	int			delta;
	int			pc;
	t_process	*new;

	new = NULL;
	delta = arg_fin(process, arg[0], arg_type[0]);
	pc = (process->pc + (short)delta) % MEM_SIZE;
	if (pc < 0)
		pc += MEM_SIZE;
	new = new_process(NULL, process, pc);
	add_process(&(g_game.proc), new);
}

void	exec_aff(t_process *process, unsigned int *arg, t_arg_type *arg_type)
{
	unsigned int res;

	res = arg_fin(process, arg[0], arg_type[0]);
	res = res % 256;
	if (g_game.a && !g_game.visu)
		ft_printf("Aff: %C\n", res);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verb_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgonor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/20 21:25:43 by dgonor            #+#    #+#             */
/*   Updated: 2018/07/20 21:25:45 by dgonor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "verbosity.h"

void		verb_print_lives(int p_num)
{
//	ft_printf("6 SEGFOLT?\n");
	int 		i;
	int 		num_players;
	t_player	*player;

	i = -1;
	num_players = g_game.players;
	player = g_game.player;
	while (++i < num_players)
	{
		if (player[i].num == -p_num)
			ft_printf("Player %i (%s) is said to be alive\n", i + 1, player[i].name);
	}
}

void		verb_print_ctd(int ctd)
{
	if ((2 & g_game.number_v) > 0)
		ft_printf("Cycle to die is now %i\n", ctd);
}

void		verb_print_cycles(int cycle)
{
	if ((2 & g_game.number_v) > 0)
		ft_printf("It is now cycle %i\n", cycle);
	// if ((g_verb.ctd_change))
	// 	ft_printf("Cycle to die is now %i\n", g_verb.ctd);
}

static void		verb_prt_op_comm_sti(t_process *proc, unsigned int *arg, t_arg_type *arg_type)//проработать ШОРТ
{
	       // | -> store to 391 + 1 = 392 (with pc and mod 392)
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
			ft_printf("%u", arg_fin(proc, arg[i], arg_type[i]));//кастила раньше в инт
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
	// new_pc = (proc->pc + (delta % IDX_MOD)) % MEM_SIZE;
	// if (new_pc < 0)
	// 	new_pc = MEM_SIZE - new_pc;
	ft_printf(" = %i (with pc and mod %i)", delta, new_pc);
}

static void		verb_prt_op_comm_ldi(t_process *proc, unsigned int *arg, t_arg_type *arg_type)
{
	       // -> load from -38 + 0 = -38 (with pc and mod 395)
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
	new_pc = proc->pc + delta;
	// new_pc = (proc->pc + delta) % MEM_SIZE;
	// if (new_pc < 0)
	// 	new_pc = MEM_SIZE + new_pc;
	ft_printf(" = %i (with pc and mod %i)", delta, new_pc);
}

void				verb_prt_op_arg(t_process *proc, t_arg_type *arg_type, unsigned int *arg)
{
	t_op 			op;
	int 			i;

	i = -1;
	op = op_tab[proc->opcode - 1];	
	while (++i < op.arg_num)
	{
		ft_printf(" ");
		if (arg_type[i] == T_REG)
		{
			if (op.arg[i] == T_REG)
			{
				ft_printf("r");
				ft_printf("%i", arg[i]);
			}
			else
			{
				if (proc->opcode == 3)//maybe also other opcodes behave like this????
					ft_printf("%i", arg[i]);
				else
					ft_printf("%i", (int)(arg_fin(proc, arg[i], arg_type[i]))); // fix arg_fin becouse of it return unsign. int
			}
		}
		else
		{
			if (arg_type[i] == T_IND)
			{
				if (proc->opcode == 2 || (proc->opcode >= 6 && proc->opcode <= 11))
					ft_printf("%u", arg_fin(proc, arg[i], arg_type[i]));//for ld, and (or xor ldi)
				else
					ft_printf("%hi", (short)arg[i]);
			}
			else if (arg_type[i] == T_DIR && op.label == 2)
				ft_printf("%hi", (short)arg[i]);
			else
				ft_printf("%i", arg[i]);
		}
	}
	// unsigned int		delta;// del
	// unsigned int		new_pc;

	// ft_printf("\n");
	// delta = arg[1] + arg[2];
	// new_pc = (proc->pc + delta) % IDX_MOD;
	// ft_printf("%i", new_pc); // del

	if (proc->opcode == 11)
		verb_prt_op_comm_sti(proc, arg, arg_type);
	if (proc->opcode == 10)
		verb_prt_op_comm_ldi(proc, arg, arg_type);
}

void		verb_print_op(t_process *proc, t_arg_type *arg_type, unsigned int *arg)
{
	t_op 		op;
	int			width;
	int			len;
	// int 		i;

	// i = -1;
	len = count_digits(proc->num, 10);
	width = len < 5 ? 4 : len;
	op = op_tab[proc->opcode - 1];
	if ((4 & g_game.number_v) > 0)
	{
		
		ft_printf("P%*i | ", (width + 1), proc->num);
		ft_printf("%s", op.op);
		// while (++i < op.arg_num)
		// {
		// 	ft_printf(" ");
		// 	if (arg_type[i] == T_REG)
		// 	{
		// 		if (op.arg[i] == T_REG)
		// 		{
		// 			ft_printf("r");
		// 			ft_printf("%i", arg[i]);
		// 		}
		// 		else
		// 			ft_printf("%i", arg_fin(proc, arg[i], arg_type[i]));
		// 	}
		// 	else
		// 		ft_printf("%i", arg[i]);	
		// }
		verb_prt_op_arg(proc, arg_type, arg); // norm comment
		if (op.opcode == 9 && proc->carry == 1)
			ft_printf(" OK");
		else if (op.opcode == 9 && proc->carry == 0)
			ft_printf(" FAILED");
		if (op.opcode == 12)
			ft_printf(" (%d)", ((short)arg_fin(proc, arg[0], arg_type[0]) % IDX_MOD) + proc->pc);//убрала деление на мемсайз
		if (op.opcode == 15)
			ft_printf(" (%d)", ((short)arg_fin(proc, arg[0], arg_type[0]) + proc->pc));//убрала деление на мемсайз  
		ft_printf("\n");
	}
	if ((1 & g_game.number_v) > 0 && proc->opcode == 1)
		verb_print_lives((int)(*arg));
}

void		verb_print_death(int proc_num, int cycles_not_live)
{
	if ((8 & g_game.number_v) > 0)
	{
		ft_printf("Process %i ", proc_num);
		ft_printf("hasn't lived for %i cycles ", cycles_not_live);
		ft_printf("(CTD %i)\n", g_game.ctd);
	}
}

void		verb_print_pc(int pc_prev, int pc_new, int move, unsigned char *board)//don't need pc_new here
{
	int 	i;
	int		new;

	i = -1;
	new = pc_new;
	new = pc_prev + move;
	if ((16 & g_game.number_v) > 0)
	{
		ft_printf("ADV %i ", move);
		pc_prev == 0 ? ft_printf("(0x0000 -> "): ft_printf("(%#.4x -> ", pc_prev);
		if (new == 0)
			ft_printf("0x0000) ");
		else if (new < 0)
			ft_printf("%#.4x) ", MEM_SIZE + new);
		else
			ft_printf("%#.4x) ", new);
		//pc_new == 0 ? ft_printf("0x0000) ") : ft_printf("%#.4x) ", pc_new);
		while (++i < move)
			ft_printf("%.2x ", board[(pc_prev + i) % MEM_SIZE]);
		ft_printf("\n");
	}
}

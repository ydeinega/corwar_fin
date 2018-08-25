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

static void	read_next_pc(t_process *proc, int move, int base)
{
	proc->prev = proc->pc;
	proc->pc_change = 1;
	if (proc->opcode == 9 && proc->carry)
		proc->pc = (proc->pc + ((short)move % base)) % MEM_SIZE;
	else
		proc->pc = (proc->pc + move) % base;
	if (proc->pc < 0)//if INDEX is < 0
		proc->pc = MEM_SIZE - proc->pc;
	if (g_game.v && proc->opcode >= 1 &&
		proc->opcode <= 16 && proc->opcode != 9)//comment
		verb_print_pc(proc->prev, proc->pc, move, g_game.board);
}

void	read_next_instruct(t_process *proc)
{
	unsigned int	code;

	code = conv_hex(&g_game.board[proc->pc], 1);
	if (code >= 1 && code <= 16)
	{
		proc->opcode = code;
		proc->cycles_to_exec = op_tab[code - 1].cycles_to_exec;//здесь нужно смотреть в табличке
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
	tmp = g_game.proc;
	while (tmp)
	{
		if (tmp->live && tmp->pc_change)
		{
			tmp->pc_change = 0;
			read_next_instruct(tmp);
		}
		tmp = tmp->next;
	}
}

// void	run_processes(void)
// {
// 	t_process	*tmp;

// 	tmp = g_game.proc;
// 	while (tmp)
// 	{
// 		if (tmp->live)
// 		{
// 			if (tmp->opcode >= 1 && tmp->opcode <= 16)
// 			{
// 				tmp->cycles_to_exec--;
// 				if (tmp->cycles_to_exec == 0 && tmp->opcode == 1)
// 				{
// 					tmp->lives_ctd++;
// 					tmp->cycles_not_live = 0;
// 				}
// 				else
// 					tmp->cycles_not_live++;
// 				tmp->cycles_to_exec == 0 ? exec_instruct(tmp) : 0;
// 			}
// 			else
// 			{
// 				tmp->cycles_not_live++;
// 				read_next_pc(tmp, 1, MEM_SIZE);
// 			}
// 		}
// 		tmp = tmp->next;
// 	}
// 	tmp = g_game.proc;
// 	while (tmp)
// 	{
// 		if (tmp->live && tmp->pc_change)
// 		{
// 			tmp->pc_change = 0;
// 			read_next_instruct(tmp);
// 		}
// 		tmp = tmp->next;
// 	}
// }

// void	run_processes(void)
// {
// 	t_process	*tmp;

// 	tmp = g_game.proc;
// 	while (tmp)
// 	{
// 		if (tmp->live)
// 		{
// 			if (tmp->opcode >= 1 && tmp->opcode <= 16)
// 			{
// 				tmp->cycles_to_exec--;
// 				if (tmp->cycles_to_exec == 0)
// 					exec_instruct(tmp);
// 				else
// 					tmp->cycles_not_live++;
// 			}
// 			else
// 			{
// 				tmp->cycles_not_live++;
// 				read_next_instruct(tmp, 1, MEM_SIZE);
// 			}
// 		}
// 		tmp = tmp->next;
// 	}
// }

static t_arg_type	*get_arg_type(t_process *proc)
{
	t_arg_type		*arg_type;
	t_op			op;

	arg_type = NULL;
	op = op_tab[proc->opcode - 1];
	if (op.codage)
		arg_type = get_codage(proc, op.arg_num);
	else
	{
		arg_type = ft_strnew(op.arg_num);
		ft_memcpy(arg_type, op.arg, op.arg_num);
	}
	return (arg_type);
}

void	exec_instruct(t_process *proc)
{
	t_arg_type		*arg_type;
	int				move;
	unsigned int	*arg;
	t_op			op;
	int				base;

	op = op_tab[proc->opcode - 1];
	arg_type = get_arg_type(proc);
	arg = NULL;
	base = (proc->opcode == 9 && proc->carry) ? IDX_MOD : MEM_SIZE;
	if (!op.codage || (op.codage && codage_valid(arg_type, op.arg, op.arg_num)))
	{
		arg = extract_arg(op, proc->pc, arg_type);
		if (arg_valid(arg_type, arg, op.arg_num))
		{
			if (g_game.v)//comment
				verb_print_op(proc, arg_type, arg);
			g_command[proc->opcode - 1](proc, arg, arg_type);
		}
	}
	// if (proc->opcode == 1)
	// {
	// 	proc->lives_ctd++;
	// 	proc->cycles_not_live = 0;
	// }
	// else
	// 	proc->cycles_not_live++;
	move = get_move(proc, arg_type, arg);
	read_next_pc(proc, move, base);
	arg_type ? free(arg_type) : 0;
	arg ? free(arg) : 0;
}

bool	arg_valid(t_arg_type *arg_type, unsigned int *arg, int arg_num)
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

// void	read_next_instruct(t_process *proc, int move, int base)
// {
// 	unsigned int	code;

// 	proc->prev = proc->pc;
// 	if (proc->opcode == 9 && proc->carry)
// 		proc->pc = (proc->pc + ((short)move % base)) % MEM_SIZE;
// 	else
// 		proc->pc = (proc->pc + move) % base;
// 	if (proc->pc < 0)//if INDEX is < 0
// 		proc->pc = MEM_SIZE - proc->pc;
// 	code = conv_hex(&g_game.board[proc->pc], 1);
// 	if (g_game.v && proc->opcode >= 1 &&
// 		proc->opcode <= 16 && proc->opcode != 9)//comment
// 	{
// 		ft_printf("proc->num = %d takes opcode %d\n", proc->num, code);
// 		verb_print_pc(proc->prev, proc->pc, move, g_game.board);
// 	}
// 	if (code >= 1 && code <= 16)
// 	{
// 		proc->opcode = code;
// 		proc->cycles_to_exec = op_tab[code - 1].cycles_to_exec;//здесь нужно смотреть в табличке
// 	}
// 	else
// 		proc->opcode = 0;
// }

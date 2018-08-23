#include "corewar.h"

t_arg_type	*get_codage(t_process *process, int arg_num)
{
	t_arg_type		*arg_type;
	int				codage_pc;
	unsigned int	codage;
	int				i;
	int				shift;

	i = 0;
	shift = 6;
	codage_pc = (process->pc + 1) % MEM_SIZE;
	codage = conv_hex(&g_game.board[codage_pc], 1);
	arg_type = ft_strnew(arg_num);
	while (i < arg_num)
	{
		arg_type[i] = (codage >> shift) & 3;
		if (arg_type[i] == REG_CODE)
			arg_type[i] = T_REG;
		else if (arg_type[i] == DIR_CODE)
			arg_type[i] = T_DIR;
		else if (arg_type[i] == IND_CODE)
			arg_type[i] = T_IND;
		shift -= 2;
		i++;
	}
	//print_codage(codage, arg_type, arg_num);//
	return (arg_type);
}

bool	codage_valid(t_arg_type *arg_type, t_arg_type *ref, int arg_num)
{
	int i;
	int check;

	i = 0;
	check = 0;
	while (i < arg_num)
	{
		if ((arg_type[i] & ref[i]) > 0)//это побитовое и
			check++;
		i++;
	}
	return (check == arg_num ? 1 : 0);
}

int		get_move(t_process *proc, t_arg_type *arg_type, unsigned int *arg)
{
	t_op op;
	int move;
	int i;

	i = 0;
	op = op_tab[proc->opcode - 1];
	move = op.codage ? 2 : 1;
	if (proc->opcode == 9 && proc->carry)
		return ((int)(*arg));
	if (arg_type)
	{
		while (arg_type[i])
		{
			if (arg_type[i] == T_REG)
				move++;
			else if (arg_type[i] == T_DIR)
				move += op_tab[proc->opcode - 1].label;
			else if (arg_type[i] == T_IND)
				move += IND_SIZE; 
			i++;
		}
	}
	return (move);
}

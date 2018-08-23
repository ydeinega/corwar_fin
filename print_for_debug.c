#include "corewar.h"

void		print_proc(t_process *proc)//del
{
	t_process	*tmp;
	int 		i;

	tmp = proc;
	i = -1;
	while (tmp)
	{
		ft_printf("num = %i\n", tmp->num);
		ft_printf("player = %i\n", tmp->player);
		ft_printf("live = %i\n", tmp->live);
		ft_printf("lives_ctd = %i\n", tmp->lives_ctd);
		ft_printf("carry = %i\n", tmp->carry);
		ft_printf("pc = %i\n", tmp->pc);
		ft_printf("cycles_not_live = %i\n", tmp->cycles_not_live);
		ft_printf("cycles_to_exec = %i\n", tmp->cycles_to_exec);
		ft_printf("opcode = %i\n", tmp->opcode);
		while (++i < REG_NUMBER)
			ft_printf("%i ", tmp->reg[i]);
		ft_printf("\n");
		tmp = tmp->next;
		i = -1;
	}
}

void	print_champ(t_lst_champs *champ)//del
{
	unsigned int i;
	
	i = 0;
	ft_printf("name = |%s|\n", champ->name);
	ft_printf("magic = %#x\n", champ->magic);
	ft_printf("comment = |%s|\n", champ->comment);
	ft_printf("size = |%u|\n", champ->size);
	while (i < champ->size)
	{
		ft_printf("%02x ", champ->comms[i]);
		i++;
	}
	ft_printf("\n");
}

void	print_players(t_player *player)
{
	int i = 0;
	while (i < g_game.players)
	{
		ft_printf("num = %i  start = %i name = %s\n", i + 1, player[i].start, player[i].name);
		ft_printf("comment = %s\n", player[i].comment);
		i++;
	}
}

void	print_info_before_exec(t_process *tmp, int move)
{
	ft_printf("CYCLES = %d\n", g_game.cycle);
	ft_printf("Cycles_to_exec = %d\n", tmp->cycles_to_exec);
	ft_printf("INSTRUCT %d executed\n", tmp->opcode);
	ft_printf("PC before = %d\nMove = %d\n", tmp->pc, move);
}

void	print_info_after_exec(t_process *tmp)
{
	ft_printf("NEW INSTRUCT %d read\n", tmp->opcode);
	ft_printf("Cycles_to_exec = %d\n", tmp->cycles_to_exec);
	ft_printf("PC after = %d\n", tmp->pc);
}

void	print_codage(int codage, t_arg_type *arg, int arg_num)
{
	int i;

	i = 0;
	ft_printf("codage = %i\n", codage);
	while (i < arg_num)
	{
		ft_printf("arg%i = %i\n", i + 1, arg[i]);
		i++;
	}
}

void	print_arg(unsigned int *argument, int opcode)
{
	t_op op;
	int arg_num;
	int i;

	op = op_tab[opcode - 1];
	arg_num = op.arg_num;
	i = 0;
	ft_printf("Instruction %s has %d arguments. HERE THEY ARE\n", op.op, arg_num);
	while (i < arg_num)
	{
		ft_printf("%d ", argument[i]);
		i++;
	}
	ft_printf("\n");

}
#include "corewar.h"

void	exec_live(t_process *process, unsigned int *arg, t_arg_type *arg_type)
{
	int				champ_num;

	champ_num = -(*arg);
	if (!process && !arg_type)
		return ;
	if (champ_num >= 1 && champ_num <= g_game.players)
	{
		g_game.player_last_live = champ_num;
		g_game.player[champ_num - 1].lives_in_curr++;
		g_game.player[champ_num - 1].last_live = g_game.cycle;
	}
	g_game.player[process->player - 1].lives_in_curr_all++;
	process->cycles_not_live = 0;
	process->lives_ctd++;
	//Subject! Check!
}

void	exec_ld(t_process *process, unsigned int *arg, t_arg_type *arg_type)
{
	int		res;

	res = arg_fin(process, arg[0], arg_type[0]);
	process->reg[arg[1] - 1] = res;
	if (res == 0)
		process->carry = 1;
	else
		process->carry = 0;
}

void	exec_st(t_process *process, unsigned int *arg, t_arg_type *arg_type)
{
	int		res;

	res = arg_fin(process, arg[0], arg_type[0]);
	if (arg_type[1] == T_REG)
		process->reg[arg[1] - 1] = res;
	else if (arg_type[1] == T_IND)
		store_value(process, res, (short)arg[1], IDX_MOD);
}

void	exec_add(t_process *process, unsigned int *arg, t_arg_type *arg_type)
{
	int		res;

	res = arg_fin(process, arg[0], arg_type[0]) + arg_fin(process, arg[1], arg_type[1]);
	process->reg[arg[2] - 1] = res;
	if (res == 0)
		process->carry = 1;
	else
		process->carry = 0;
}

void	exec_sub(t_process *process, unsigned int *arg, t_arg_type *arg_type)
{
	int		res;

	res = arg_fin(process, arg[0], arg_type[0]) - arg_fin(process, arg[1], arg_type[1]);
	process->reg[arg[2] - 1] = res;
	if (res == 0)
		process->carry = 1;
	else
		process->carry = 0;
}

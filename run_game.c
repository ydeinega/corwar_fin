#include "corewar.h"

void	run_game(void)
{
	//здесь нужно разрулить ситуацию с флагами
	if (g_game.visu)
		draw_map(g_game.win);
	else if (g_game.v)
		initialize_verb();//comment
	while (g_game.end != true && g_game.ctd > 0)
	{
		g_game.cycle++;
		if (g_game.v)
			verb_print_cycles(g_game.cycle);
		g_game.ctd_cur++;
		run_processes();
		if (g_game.ctd_cur == g_game.ctd)
			make_check();
		if (g_game.visu)
			draw_all(g_game.win);
		// if (g_game.dump && g_game.cycle == g_game.nbr_cycles)
		// {
		// 	dump();
		// 	exit(0);
		// }
		//g_game.v && g_game.number_v ? verb_mode(g_game.number_v) : 0;//comment!!!!!!!!!!!!!!!!!
	}
	if ((!g_game.v && !g_game.dump && !g_game.visu) ||
		(g_game.v && !g_game.number_v))
		verb_mode(0);//здесь как-то назвать функцию типа принт резалт
}

void	make_check(void)
{
	bool	nbr_live;

	//ft_printf("I'm here. Let's make a check\n");
	nbr_live = check_nbr_live();
	//ft_printf("nbr_live = %i\n", nbr_live);
	g_game.end = check_deaths();
	// ft_printf("g_game.end = %i\n", g_game.end);
	// ft_printf("g_game.checks = %i\n", g_game.checks);
	if (nbr_live)
	{
		g_game.ctd -= CYCLE_DELTA;
		g_game.checks = 0;
		if (g_game.v)//Изменяю флаг, когда меняю CTD//comment
			verb_print_ctd(g_game.ctd);
	}
	else
		g_game.checks++;
	if (g_game.checks == MAX_CHECKS)
	{
		g_game.ctd -= CYCLE_DELTA; 
		g_game.checks = 0;
		if (g_game.v)//comment
			verb_print_ctd(g_game.ctd);
	}
	if (g_game.end || g_game.ctd <= 0)
		g_game.end = true;
	g_game.ctd_cur = 0;
}

bool	check_nbr_live(void)
{
	int		i;
	bool	res;

	i = 0;
	res = 0;
	while (i < g_game.players)
	{
		if (g_game.player[i].lives_in_curr >= NBR_LIVE)
			res = 1;
		g_game.player[i].lives_in_curr = 0;
		i++;
	}
	return (res);
}

bool	check_deaths(void)
{
	t_process	*proc;
	int			num_deaths;

	proc = g_game.proc;
	num_deaths = 0;
	while (proc)
	{
		if (g_game.ctd == 786 && (proc->num == 1769 || proc->num == 1762 || proc->num == 1754))
		{
			ft_printf("proc_num = %i lives_ctd = %i\n", proc->num, proc->lives_ctd);
			ft_printf("cycles_not_live = %i ctd = %i\n", proc->cycles_not_live, g_game.ctd);
		}
		if (proc->lives_ctd == 0 && proc->live && proc->cycles_not_live >= g_game.ctd)
		{
			proc->live = 0;
			num_deaths++;
			if (g_game.v)//comment
				verb_print_death(proc->num, proc->cycles_not_live);
		}
		proc->lives_ctd = 0;
		proc = proc->next;
	}
	return (num_deaths == g_game.proc_num ? 1 : 0);
}

// void	check_lives(int *zero_live, bool *nbr_live)
// {
// 	int		i;

// 	i = 0;
// 	while (i < g_game.players)
// 	{
// 		if (g_game.player[i].lives_in_curr == NBR_LIVE)
// 			*nbr_live = 1;
// 		if (g_game.player[i].lives_in_curr == 0)
// 			*zero_live += 1;
// 		g_game.player[i].lives_in_curr = 0;
// 		i++;
// 	}
// }

#include "corewar.h"

void	run_game(void)
{
	//здесь нужно разрулить ситуацию с флагами
	if (g_game.visu)
		draw_map(g_game.win);
	else if (g_game.v && g_game.number_v > 0)
		initialize_verb();//comment
	while (g_game.end != true && g_game.ctd > 0)
	{
		if (g_game.ctd_cur == g_game.ctd && make_check())
			break ;
		g_game.cycle++;
		if (g_game.v)
			verb_print_cycles(g_game.cycle);
		g_game.ctd_cur++;
		run_processes();
		if (g_game.visu) {
			draw_all(g_game.win);
			usleep(8000);
		}
		if (g_game.dump && g_game.cycle == g_game.nbr_cycles)
		{
			dump();
			exit(0);
		}
		//g_game.v && g_game.number_v ? verb_mode(g_game.number_v) : 0;//comment!!!!!!!!!!!!!!!!!
	}
	if (g_game.v)
		check_deaths();
	// if ((!g_game.v && !g_game.dump && !g_game.visu) ||
	// 	(g_game.v && !g_game.number_v))
	// 	verb_mode(0);//здесь как-то назвать функцию типа принт резалт
}

bool	make_check(void)
{
	bool	nbr_live;
	
	nbr_live = check_nbr_live();
	//del
	// ft_printf("I'm here. Let's make a check\n");
	// ft_printf("nbr_live = %i\n", nbr_live);
	//del
	g_game.end = check_deaths();
	//del
	// ft_printf("g_game.end = %i\n", g_game.end);
	// ft_printf("g_game.checks = %i\n", g_game.checks);
	//del
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
	// if (g_game.end || g_game.ctd <= 0)
	// 	g_game.end = true;
	g_game.ctd_cur = 0;
	return (g_game.end);
}

bool	check_nbr_live(void)
{
	int		i;
	bool	res;
	int		lives_total;

	i = 0;
	res = 0;
	lives_total = 0;//test
	while (i < g_game.players)
	{
		if (g_game.player[i].lives_in_curr_all >= NBR_LIVE)
			res = 1;
		//del
		//ft_printf("player %i lives_in_curr = %i\n", i + 1, g_game.player[i].lives_in_curr_all);
		//del
		lives_total += g_game.player[i].lives_in_curr_all;
		g_game.player[i].lives_in_curr = 0;
		g_game.player[i].lives_in_curr_all = 0;
		i++;
	}
	if (lives_total >= NBR_LIVE)
		res = 1;
	return (res);
}

bool	check_deaths(void)
{
	t_process	*proc;

	proc = g_game.proc;
	while (proc)
	{
		if ((proc->lives_ctd == 0 && proc->live && proc->cycles_not_live >= g_game.ctd) ||
			(g_game.ctd <= 0 && proc->live))
		{
			proc->live = 0;
			g_game.death_num++;
			if (g_game.v)//comment
				verb_print_death(proc->num, proc->cycles_not_live);
		}
		proc->lives_ctd = 0;
		proc = proc->next;
	}
	return (g_game.death_num == g_game.proc_num ? 1 : 0);
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

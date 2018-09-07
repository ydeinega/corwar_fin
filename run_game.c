/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydeineha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 21:31:30 by ydeineha          #+#    #+#             */
/*   Updated: 2018/09/05 21:31:36 by ydeineha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

// void	make_pause(void)
// {
// 	int	x;
// 	int	y;

// 	y = 2;
// 	x = 64 * 3 + 7;
// 	unset_colors(g_game.win);
// 	mvwprintw(g_game.win, y, x, "** PAUSED ** ");
// 	wrefresh(g_game.win);
// 	while (true)
// 		if (getch() == 32)
// 			break ;
// 	mvwprintw(g_game.win, y, x, "** RUNNING **");
// 	wrefresh(g_game.win);
// }

void	run_game(void)
{
	g_game.timeout = 6000;
	while (g_game.end != true && g_game.ctd > 0)
	{
		if (g_game.visu)
		{
			handle_keys();
			draw_all(g_game.win);
			usleep(g_game.timeout);
		}
		else if (g_game.dump && g_game.cycle == g_game.nbr_cycles)
		{
			dump();
			clean_all();
			exit(0);
		}
		if (g_game.ctd_cur == g_game.ctd && make_check())
			break ;
		g_game.cycle++;
		if (g_game.v && !g_game.visu)
			verb_print_cycles(g_game.cycle);
		g_game.ctd_cur++;
		run_processes();
		
	}
	if (g_game.v && !g_game.visu)
		check_deaths();
}

bool	make_check(void)
{
	bool	nbr_live;

	nbr_live = check_nbr_live();
	g_game.end = check_deaths();
	if (nbr_live)
	{
		g_game.ctd -= CYCLE_DELTA;
		g_game.checks = 0;
		if (g_game.v && !g_game.visu)
			verb_print_ctd(g_game.ctd);
	}
	else
		g_game.checks++;
	if (g_game.checks == MAX_CHECKS)
	{
		g_game.ctd -= CYCLE_DELTA;
		g_game.checks = 0;
		if (g_game.v && !g_game.visu)
			verb_print_ctd(g_game.ctd);
	}
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
	lives_total = 0;
	while (i < g_game.players)
	{
		if (g_game.player[i].lives_in_curr_all >= NBR_LIVE)
			res = 1;
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
		if ((proc->lives_ctd == 0 && proc->live
			&& proc->cycles_not_live >= g_game.ctd)
			|| (g_game.ctd <= 0 && proc->live))
		{
			proc->live = 0;
			g_game.death_num++;
			if (g_game.v && !g_game.visu)
				verb_print_death(proc->num, proc->cycles_not_live);
		}
		proc->lives_ctd = 0;
		proc = proc->next;
	}
	return (g_game.death_num == g_game.proc_num ? 1 : 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmalyavc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/28 20:26:04 by rmalyavc          #+#    #+#             */
/*   Updated: 2018/08/28 20:26:06 by rmalyavc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"
#include "../op.h"

static int			count_procs(void)
{
	t_process		*curr;
	int				i;

	i = 0;
	curr = g_game.proc;
	while (curr && (i += 1))
		curr = curr->next;
	return (i);
}

static void			player_info(WINDOW *win, int *y, int x, int nb)
{
	t_player		pl;

	pl = g_game.player[nb];
	nb++;
	mvwprintw(win, *y, (*y += 1) * 0 + x, "Player -%d : ", nb);
	wattron(win, COLOR_PAIR(nb));
	wprintw(win, "%s", pl.name);
	wattroff(win, COLOR_PAIR(nb));
	mvwprintw(win, *y, (*y += 1) * 0 + x + 2, "Last live :                 %d", pl.last_live);
	mvwprintw(win, *y, (*y += 2) * 0 + x + 2, "Lives in current period :   %d", pl.lives_in_curr);
}


void				draw_info(WINDOW *win)
{
	int				y;
	int				x;
	int				i;

	y = 1;
	x = 64 * 3 + 3;
	i = -1;
	wattroff(win, COLOR_PAIR(1));
	wattroff(win, A_REVERSE | A_BLINK);
	mvwprintw(win, y, x, "** RUNNING **");
	y += 2;
	mvwprintw(win, y, x, "Cycles/second limit : 8000");
	y += 3;
	mvwprintw(win, y, x, "Cycle : %d", g_game.cycle);
	y += 2;
	mvwprintw(win, y, x, "Processes : %d", count_procs());
	y += 2;
	while (++i < g_game.players)
		player_info(win, &y, x, i);
	draw_breakdowns(win, &y, x);
	mvwprintw(win, y, x, "CYCLE_TO_DIE : %d", g_game.ctd);
	y += 2;
	mvwprintw(win, y, x, "CYCLE_DELTA : %d", CYCLE_DELTA);
	y += 2;
	mvwprintw(win, y, x, "NBR_LIVE : %d", NBR_LIVE);
	y += 2;
	mvwprintw(win, y, x, "MAX_CHECKS : %d", MAX_CHECKS);
	// wprintw(win, "%s\n\n\n", "Cycles/second limit : 8000");
	// wprintw(win, "Cycle : %d\n\n", g_game.cycle);
	// wprintw(win, "Processes : %d\n\n", count_procs());
}
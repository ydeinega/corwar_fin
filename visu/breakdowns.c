/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   breakdowns.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmalyavc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/30 19:49:19 by rmalyavc          #+#    #+#             */
/*   Updated: 2018/08/30 19:49:22 by rmalyavc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"
#include "../op.h"


static int			get_total(void)
{
	int				res;
	int				i;

	i = -1;
	res = 0;
	while (++i <  g_game.players)
		res += g_game.player[i].lives_in_curr;
	return (res);
}

static void			curr_breakdown(WINDOW *win, int *y, int x, int total)
{
	t_player		*pl;
	int				i;
	int				j;
	int				count;
	// double			res;

	count = 0;
	i = -1;
	pl = g_game.player;
	// mvwprintw(win, *y, x + 51, " ");
	// if (g_game.ctd < 1350)
	// 	exit(0);
	while (++i < g_game.players)
	{
		if ((j = -1) && i == 0)
			mvwprintw(win, *y, (*y += 2) * 0 + x, "[");
		if (pl[i].lives_in_curr > 0)
			wattron(win, COLOR_PAIR(i + 1));
		
		// if (total > 0) {
		// 	res = (50 * (double)pl[i].lives_in_curr) / (double)total; // WHAT THE FUCK?! Need to investigate
		// 	mvwprintw(win, *y + i + 32, x, "Lives = %d total = %d Percent = %f",
		// 		pl[i].lives_in_curr, total, res);
		// 	mvwprintw(win, *y - 2, x, "");
		// }
		
		while (((total > 0 && ++j < 50 * pl[i].lives_in_curr / total) || (total == 0 && ++j < 50 / g_game.players)) && (count += 1))
			wprintw(win, "-");
		while (i == g_game.players - 1 && count++ < 50)
			wprintw(win, "-");
		wattroff(win, COLOR_PAIR(i + 1));
	}
	wprintw(win, "]");
}

void			draw_breakdowns(WINDOW *win, int *y, int x)
{
	mvwprintw(win, *y, (*y += 1) * 0 + x, "Live breakdown for current period :");
	curr_breakdown(win, y, x, get_total());
	// mvwprintw(win, *y, (*y += 2) * 0 + x, "[ TODO: ]");
	mvwprintw(win, *y, (*y += 1) * 0 + x, "Live breakdown for last period :");
	mvwprintw(win, *y, (*y += 2) * 0 + x, "[ TODO: ]");
}